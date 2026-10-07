#ifndef LISTA_H
#define LISTA_H

#include "musica.h"


typedef struct lista Lista;

Lista *lista_criar(void);


int lista_inserir_inicio(Lista *l, Musica *m);
int lista_inserir_final(Lista *l, Musica *m);
int lista_inserir_posicao(Lista *l, int pos, Musica *m);

 
Musica *lista_remover_primeira(Lista *l);
Musica *lista_remover_ultima(Lista *l);
Musica *lista_remover_posicao(Lista *l, int pos);


Musica *lista_consultar_primeira(const Lista *l);
Musica *lista_consultar_posicao(const Lista *l, int pos);


int lista_tamanho(const Lista *l);


void lista_liberar(Lista *l);

#endif
