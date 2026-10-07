#include <stdlib.h>
#include "lista.h"

typedef struct no {
    Musica *musica;
    struct no *prox;
} No;

struct lista {
    No *inicio;
    int tamanho;
};

Lista *lista_criar(void) {
    Lista *l = malloc(sizeof(Lista));
    if (l == NULL)
        return NULL;
    l->inicio = NULL;
    l->tamanho = 0;
    return l;
}

int lista_inserir_inicio(Lista *l, Musica *m) {
    return lista_inserir_posicao(l, 0, m);
}

int lista_inserir_final(Lista *l, Musica *m) {
    if (l == NULL)
        return 0;
    return lista_inserir_posicao(l, l->tamanho, m);
}

int lista_inserir_posicao(Lista *l, int pos, Musica *m) {
    if (l == NULL || m == NULL || pos < 0 || pos > l->tamanho)
        return 0;

    No *novo = malloc(sizeof(No));
    if (novo == NULL)
        return 0;
    novo->musica = m;

    if (pos == 0) {
        novo->prox = l->inicio;
        l->inicio = novo;
    } else {
        No *ant = l->inicio;
        for (int i = 0; i < pos - 1; i++)
            ant = ant->prox;
        novo->prox = ant->prox;
        ant->prox = novo;
    }
    l->tamanho++;
    return 1;
}

Musica *lista_remover_primeira(Lista *l) {
    return lista_remover_posicao(l, 0);
}

Musica *lista_remover_ultima(Lista *l) {
    if (l == NULL)
        return NULL;
    return lista_remover_posicao(l, l->tamanho - 1);
}

Musica *lista_remover_posicao(Lista *l, int pos) {
    if (l == NULL || pos < 0 || pos >= l->tamanho)
        return NULL;

    No *removido;
    if (pos == 0) {
        removido = l->inicio;
        l->inicio = removido->prox;
    } else {
        No *ant = l->inicio;
        for (int i = 0; i < pos - 1; i++)
            ant = ant->prox;
        removido = ant->prox;
        ant->prox = removido->prox;
    }

    Musica *m = removido->musica;
    free(removido);
    l->tamanho--;
    return m;
}

Musica *lista_consultar_primeira(const Lista *l) {
    return lista_consultar_posicao(l, 0);
}

Musica *lista_consultar_posicao(const Lista *l, int pos) {
    if (l == NULL || pos < 0 || pos >= l->tamanho)
        return NULL;
    No *atual = l->inicio;
    for (int i = 0; i < pos; i++)
        atual = atual->prox;
    return atual->musica;
}

int lista_tamanho(const Lista *l) {
    return l != NULL ? l->tamanho : 0;
}

void lista_liberar(Lista *l) {
    if (l == NULL)
        return;
    No *atual = l->inicio;
    while (atual != NULL) {
        No *prox = atual->prox;
        musica_liberar(atual->musica);
        free(atual);
        atual = prox;
    }
    free(l);
}
