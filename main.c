#include <stdio.h>
#include "musica.h"
#include "lista.h"

/* Adiciona uma musica ao final da playlist */
void adiciona_musica(Lista *playlist, Musica *m) {
    if (!lista_inserir_final(playlist, m)) {
        printf("Erro ao adicionar musica.\n");
        musica_liberar(m);
    }
}

/* Adiciona uma musica em uma posicao especifica (0 = primeira).
 * Se a insercao ocorrer antes da proxima musica a tocar, ajusta *proxima
 * para que ela continue apontando para a mesma musica. */
void adiciona_musica_posicao(Lista *playlist, Musica *m, int pos, int *proxima) {
    if (!lista_inserir_posicao(playlist, pos, m)) {
        printf("Erro: posicao %d invalida para insercao.\n", pos);
        musica_liberar(m);
        return;
    }
    if (pos <= *proxima)
        (*proxima)++;
}

/* Remove a musica de uma posicao especifica, ajustando *proxima se necessario */
void remove_musica(Lista *playlist, int pos, int *proxima) {
    Musica *m = lista_remover_posicao(playlist, pos);
    if (m == NULL) {
        printf("Erro: posicao %d invalida para remocao.\n", pos);
        return;
    }
    printf("Removida: ");
    musica_imprimir(m);
    musica_liberar(m);
    if (pos < *proxima)
        (*proxima)--;
}

/* Calcula o tempo (em segundos) das musicas da posicao proxima ate o fim */
int tempo_restante(const Lista *playlist, int proxima) {
    int total = 0;
    int n = lista_tamanho(playlist);
    for (int i = proxima; i < n; i++)
        total += musica_duracao(lista_consultar_posicao(playlist, i));
    return total;
}

/* "Toca" a proxima musica e avanca a posicao */
void play(const Lista *playlist, int *proxima) {
    Musica *m = lista_consultar_posicao(playlist, *proxima);
    if (m == NULL) {
        printf("Fim da playlist: nao ha mais musicas para tocar.\n");
        return;
    }
    printf("Tocando: ");
    musica_imprimir(m);
    (*proxima)++;
}

/* Quantidade de musicas ja tocadas */
int musicas_reproduzidas(int proxima) {
    return proxima;
}

static void imprime_tempo_restante(const Lista *playlist, int proxima) {
    int t = tempo_restante(playlist, proxima);
    printf("Tempo restante: %02d:%02d\n", t / 60, t % 60);
}

int main(void) {
    Lista *playlist = lista_criar();
    int proxima = 0; /* posicao da proxima musica a ser reproduzida */

    if (playlist == NULL) {
        printf("Erro ao criar a playlist.\n");
        return 1;
    }

    /* 10 musicas criadas diretamente no codigo */
    Musica *m1  = musica_criar("Magica", "Calcinha Preta", 240);
    Musica *m2  = musica_criar("Thriller", "Michael Jackson", 357);
    Musica *m3  = musica_criar("Homem-Aranha", "Jorge Vercillo", 245);
    Musica *m4  = musica_criar("Até Que Durou", "Péricles", 215);
    Musica *m5  = musica_criar("MILLION DOLLAR BABY", "Tommy Richman", 155);
    Musica *m6  = musica_criar("The Emptiness Machine", "Linkin Park", 200);
    Musica *m7  = musica_criar("Lightbringer", "Pentakill", 230);
    Musica *m8  = musica_criar("P do Pecado", "Grupo Menos É Mais", 190);
    Musica *m9  = musica_criar("That's What I Like", "Bruno Mars", 206);
    Musica *m10 = musica_criar("Animal I Have Become", "Three Days Grace", 231);

    printf("=== Montando a playlist ===\n");
    adiciona_musica(playlist, m1);
    adiciona_musica(playlist, m2);
    adiciona_musica(playlist, m3);
    adiciona_musica(playlist, m4);
    adiciona_musica(playlist, m5);
    adiciona_musica(playlist, m6);
    adiciona_musica(playlist, m7);
    printf("Musicas na playlist: %d\n", lista_tamanho(playlist));
    imprime_tempo_restante(playlist, proxima);

    printf("\n=== Tocando 3 musicas ===\n");
    play(playlist, &proxima);
    play(playlist, &proxima);
    play(playlist, &proxima);
    printf("Musicas reproduzidas: %d\n", musicas_reproduzidas(proxima));
    imprime_tempo_restante(playlist, proxima);

    printf("\n=== Adicionando por posicao ===\n");
    adiciona_musica_posicao(playlist, m8, 1, &proxima);  /* antes da proxima: ajusta */
    adiciona_musica_posicao(playlist, m9, 6, &proxima);  /* depois da proxima */
    adiciona_musica_posicao(playlist, m10, 99, &proxima); /* invalida: libera m10 */
    printf("Musicas na playlist: %d | proxima posicao: %d\n",
           lista_tamanho(playlist), proxima);
    imprime_tempo_restante(playlist, proxima);

    printf("\n=== Removendo musicas ===\n");
    remove_musica(playlist, 0, &proxima);  /* ja tocada */
    remove_musica(playlist, 5, &proxima);  /* ainda nao tocada */
    remove_musica(playlist, 50, &proxima); /* invalida */
    printf("Musicas na playlist: %d | proxima posicao: %d\n",
           lista_tamanho(playlist), proxima);
    imprime_tempo_restante(playlist, proxima);

    printf("\n=== Tocando mais musicas ===\n");
    play(playlist, &proxima);
    play(playlist, &proxima);
    printf("Musicas reproduzidas: %d\n", musicas_reproduzidas(proxima));
    imprime_tempo_restante(playlist, proxima);

    printf("\n=== Resumo final ===\n");
    printf("Quantidade de musicas na playlist: %d\n", lista_tamanho(playlist));
    printf("Posicao da proxima musica a ser reproduzida: %d\n", proxima);

    lista_liberar(playlist);
    return 0;
}