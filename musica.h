#ifndef MUSICA_H
#define MUSICA_H

typedef struct musica Musica;


Musica *musica_criar(const char *titulo, const char *artista, int duracao);

const char *musica_titulo(const Musica *m);
const char *musica_artista(const Musica *m);
int musica_duracao(const Musica *m);

void musica_imprimir(const Musica *m);

void musica_liberar(Musica *m);

#endif
