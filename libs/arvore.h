/*!
 * \file
 * \brief   Biblioteca de manipulação de árvore
 * \author  Jeferson Lima
 *
 * Biblioteca de manipulação de árvore binária com o
 * intuito de manipular uma árvore de busca binária
 *
 */

#include <stdbool.h>

#ifndef ARVORE_H
#define ARVORE_H

/* Struct da Árvore */
typedef struct Arvore{
    int chave;
    struct Arvore *no_dir;
    struct Arvore *no_esq;
    struct Arvore *no_pai;
}*ArvoreInt, noArvoreInt;

/* Funções de manipulação da Árvore */
void inicializa(ArvoreInt *a);
_Bool consulta(ArvoreInt *a, int x);
_Bool insere(ArvoreInt *a, int x);
_Bool retira(ArvoreInt *a, int x);

#endif // ARVORE_H
