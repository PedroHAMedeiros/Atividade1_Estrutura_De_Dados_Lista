#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musica.h"

struct musica {
    char *titulo;
    char *artista;
    int duracao; /* em segundos */
};

static char *copia_string(const char *s) {
    char *c = malloc(strlen(s) + 1);
    if (c != NULL)
        strcpy(c, s);
    return c;
}

Musica *musica_criar(const char *titulo, const char *artista, int duracao) {
    if (titulo == NULL || artista == NULL || duracao < 0)
        return NULL;

    Musica *m = malloc(sizeof(Musica));
    if (m == NULL)
        return NULL;

    m->titulo = copia_string(titulo);
    m->artista = copia_string(artista);
    m->duracao = duracao;

    if (m->titulo == NULL || m->artista == NULL) {
        free(m->titulo);
        free(m->artista);
        free(m);
        return NULL;
    }
    return m;
}

const char *musica_titulo(const Musica *m) {
    return m != NULL ? m->titulo : NULL;
}

const char *musica_artista(const Musica *m) {
    return m != NULL ? m->artista : NULL;
}

int musica_duracao(const Musica *m) {
    return m != NULL ? m->duracao : -1;
}

void musica_imprimir(const Musica *m) {
    if (m == NULL)
        return;
    printf("%s - %s [%02d:%02d]\n", m->titulo, m->artista,
           m->duracao / 60, m->duracao % 60);
}

void musica_liberar(Musica *m) {
    if (m == NULL)
        return;
    free(m->titulo);
    free(m->artista);
    free(m);
}
