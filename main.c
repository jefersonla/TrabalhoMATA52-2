#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "libs/arvore.h"

#define MAX_CHAVES 1000

typedef struct{
    int chave;
    int freq;
}Chaves;

/*
 * Assumindo que OPTIMAL-BST(p, q, n) - return e, root
 * aonde p e q são as frequencias e chaves
 * ! TEM QUE VERIFICAR OS INDICES... quando é 0 e quando é 1
 */
void optimalBST(int *p, int *q, int n, int *e[n + 1], int *root[n]){
    int i, l, j, r, t;
    int w[n+1][n];

    // Inicializa os valores - Falta verificar a questão dos indices
    for(i = 0; i < (n + 1); i++){
        e[i][i - 1] = q[i-1];
        w[i][i - 1] = q[i-1];
    }

    for(l = 0; l < n; l++){
        for(i = 0; i < (n - l + 1); i++){
            j = i + l - 1;
            e[i][j] = -1;
            w[i][j] = w[i][j - 1] + q[j] + p[j];

            for(r = i; r <= j; r++){
                t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if(t < e[i][j]){
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
}

int main(int argc, char *argv[]){
    int n, i;
    char opcao[14];         // Opção
    ArvoreInt a;            // Arvore de Inteiros
    Chaves chave[MAX_CHAVES];   // Chaves Entradas

    // Inicializa a arvore
    inicializa(&a);

    // Numero de entradas
    scanf("%d", &n);

    // Chaves
    for(i = 0; i < n; i++)
        scanf("%d ", &chave[i].chave);

    // Probabilidades
    for(i = 0; i < n; i++)
        scanf("%d ", &chave[i].freq);

    /* Optimal BST */


    return EXIT_SUCCESS;
}