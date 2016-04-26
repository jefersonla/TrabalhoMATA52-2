/*!
 * \file
 * \brief   Biblioteca de manipulação de árvore
 * \author  Jeferson Lima
 *
 * Biblioteca de manipulação de árvore binária com o
 * intuito de manipular uma árvore de busca binária
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"

/*!
 * \brief inicializa Inicializa a árvore
 *
 * Inicializa a árvore, fazendo a apontar para NULL
 *
 * \param a Árvore a ser inicializada
 */
void inicializa(ArvoreInt *a){
    *a = NULL;
}

/*!
 * \brief consulta Consulta a existência de uma chave
 *
 * Consulta uma chave x numa árvore passada por parâmetro
 *
 * \param a Árvore a ser consultada
 * \param x Chave a ser consultada
 * \return  Retorna a existência da chave
 */
_Bool consulta(ArvoreInt *a, int x){
    noArvoreInt *aux;
    aux = *a;
    while(aux)
        if(x > aux->chave)                              /* Procura dentre os nós o nó que seja igual ao nó x */
            aux = aux->no_dir;
        else if(x < aux->chave)
            aux = aux->no_esq;
        else
            return true;
    return false;
}

/*!
 * \brief insere    Insere um nó na árvore
 *
 * Insere um nó na árvore com uma chave x
 *
 * \param a         Árvore para inserção
 * \param x         Chave a ser adicionada
 * \return          Retorna a confirmação da inserção
 */
_Bool insere(ArvoreInt *a, int x){
    noArvoreInt *p, *aux;
    if(!(p = (ArvoreInt) malloc (sizeof(noArvoreInt)))) /* Tenta alocar na memória o nó da árvore */
        return false;
    p->no_dir = NULL;
    p->no_esq = NULL;
    p->chave = x;
    if(!(*a)){                                          /* Verifica se essa inserção é a primeira */
        p->no_pai = NULL;
        *a = p;
        return true;
    }
    aux = *a;
    while(aux)                                          /* Percorre a árvore para inserir o nó */
        if(x > aux->chave)                              /* Vê se pode adicionar no nó seguinte a direita */
            if(aux->no_dir == NULL){
                p->no_pai = aux;
                aux->no_dir = p;
                return true;
            }
            else                                        /* Ou atribui o nó seguinte também a direita */
                aux = aux->no_dir;
        else if(x < aux->chave)                         /* Mesma coisa que a anterior só que para o nó a esquerda  */
            if(aux->no_esq == NULL){
                p->no_pai = aux;
                aux->no_esq = p;
                return true;
            }
            else
                aux = aux->no_esq;
        else                                            /* Se já existe nó igual não faz nada e retorna true */
            return true;
    return false;                                       /* Evita erros de compilação e gera um erro caso algo dê errado */
}

/*!
 * \brief procuraMenorNo Procura o menor nó da subárvore a direita
 *
 * Procura o menor nó na subárvore a direita e retorna ele de forma recursiva
 *
 * \param a     Subárvore de pesquisa
 * \return      O menor nó
 */
int procuraMenorNo(noArvoreInt *a){
    return a->no_esq ? procuraMenorNo(a->no_esq) : a->chave ;
}

//! Definição auxiliar
_Bool retira(ArvoreInt *a, int x);

/*!
 * \brief removeMenorNo Remove o menor nó da subárvore
 *
 * Remove o menor nó da subárvore a direita
 *
 * \param a     Arvore aonde vai ocorrer a busca
 * \return      Menor nó
 */
int removeMenorNo(ArvoreInt *a){
    int menorNo;
    if(!(*a)->no_esq){
        menorNo = (*a)->chave;
        if(!(*a)->no_dir)
            (*a)->no_pai->no_dir = NULL;
        else{
            (*a)->no_pai->no_dir = (*a)->no_dir;
            (*a)->no_dir->no_pai = (*a)->no_pai;
        }
        free((*a));
        return menorNo;
    }
    menorNo = procuraMenorNo(*a);
    retira(a, menorNo);
    return menorNo;
}

/*!
 * \brief retira    Remove um nó da arvore
 *
 * Remove um nó da arvore que contenha a chave x passada por parâmetro
 *
 * \param a         Arvore para remoção
 * \param x         Chave a ser removida
 * \return          Retorna a confirmação da remoção
 */
_Bool retira(ArvoreInt *a, int x){
    noArvoreInt *aux;
    aux = *a;
    if(!a)                                                      /* Se não existir nó não há como haver remoção */
        return false;
    if((*a)->chave == x){                                       /* Caso a chave seja o primeiro nó */
        if(((*a)->no_dir == NULL) && ((*a)->no_esq == NULL)){   /* Verifica se é um nó folha */
            *a = NULL;
            free(aux);
            return true;
        }
        else
            if((*a)->no_dir == NULL){                           /* Verifica se existe um nó ou a direita */
                *a = (*a)->no_esq;
                (*a)->no_pai = NULL;
                free(aux);
                return true;
            }
            else if((*a)->no_esq == NULL){                      /* ou a esquerda */
                *a = (*a)->no_dir;
                (*a)->no_pai = NULL;
                free(aux);
                return true;
            }
            else{                                               /* Se houver nó nos dois lados */
                (*a)->chave = removeMenorNo(&(*a)->no_dir);      /* Procura o menor nó na subárvore a dir. e substitui */
                return true;
            }
    }
    while(aux)                                                  /* Caso a chave não seja o primeiro nó */
        if(x > aux->chave)                                      /* Procura o nó até encontralo */
            aux = aux->no_dir;
        else if(x < aux->chave)
            aux = aux->no_esq;
        else{
            if((aux->no_dir == NULL) && (aux->no_esq == NULL)){         /* Assim que encontralo verifica se é um nó folha */
                if(x > aux->no_pai->chave)
                    aux->no_pai->no_dir = NULL;
                else
                    aux->no_pai->no_esq = NULL;
                free(aux);
                return true;
            }
            else if((aux->no_dir == NULL) || ((aux->no_esq == NULL))){  /* Verifica se existe apenas um nó em um lado */
                if(x > aux->no_pai->chave)
                    if(aux->no_dir == NULL){
                        aux->no_dir->no_pai = aux->no_pai;
                        aux->no_pai->no_dir = aux->no_esq;
                    }
                    else{
                        aux->no_dir->no_pai = aux->no_pai;
                        aux->no_pai->no_dir = aux->no_dir;
                    }
                else
                    if(aux->no_esq == NULL){
                        aux->no_pai->no_esq = aux->no_esq;
                        aux->no_esq->no_pai = aux->no_pai;
                    }
                    else{
                        aux->no_pai->no_esq = aux->no_dir;
                        aux->no_esq->no_pai = aux->no_pai;
                    }
                free(aux);
                return true;
            }
            else{                                               /* Se existe nó nos dois lados */
                aux->chave = removeMenorNo(&aux->no_dir);        /* Procura o menor nó na subárvore a dir. e substitui */
                return true;
            }
        }
    return false;                                               /* Caso não encontre retorna false */
}
