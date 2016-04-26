#include <stdio.h>
#include <stdlib.h>
#include "libs/arvore.h"

/*
 * Assumindo que OPTIMAL-BST(p, q, n) - return e, root
 * aonde 'p' e 'q' são as frequencias de acesso (válido, inválido)
 * e 'e' e 'root', são a matriz de custos e a matriz de indices
 * respectivamente
 */
void optimalBST(int *p, int *q, int n, int e[][n+1], int root[][n+1]){
    int i, l, j, r, t, menor, indice_menor;
    int w[n+1][n+1];      // Pesos

    // Inicializa os valores
    for(i = 0; i <= n; i++){
        e[i][i] = q[i];
        w[i][i] = q[i];

        for(j = i + 1; j <= n; j++)
            w[i][j] = w[i][j-1] + p[j] + q[j];
    }

    // Constroi a matriz de indices e inicializa os valores de e[i][j]
    for(i = 0; i <= (n - 1); i++){
        j = i +1;
        e[i][j] = e[i][i] + e[j][j] + w[i][j];
        root[i][j] = j;
    }

    for(l = 2; l <= n; l++){
        for(i = 0; i <= (n - l); i++){
            j = i + l;

            //e[i][j] = UINT32_MAX;
            //w[i][j] = w[i][j - 1] + p[j] + q[j];

            // Como inicializamos e + 1
            indice_menor = root[i][j-1];
            menor = e[i][indice_menor - 1] + e[indice_menor][j];

            for(r = indice_menor; r <= root[i+1][j]; r++){
                // Calculamos o custo atual sem a adição do peso
                t = e[i][r - 1] + e[r][j];
                // Se ele é menor que o menor
                if(t < menor){
                    menor = t;
                    indice_menor = r;
                }
            }

            // Como ainda falta o peso adicionamos esse a
            // matriz de custos, e atualizamos a matriz de indices
            e[i][j] = w[i][j] + menor;
            root[i][j] = indice_menor;
        }
    }
}

int main(int argc, char *argv[]){
    int n, i;
    ArvoreInt a;    // Arvore de Inteiros

    // Inicializa a arvore
    inicializa(&a);

    // Numero de entradas
    scanf("%d", &n);

    /* Entradas */
    // Como os indices podem acabar em n inicializamos
    // todos os vetores e matrizes com n + 1 posições
    int k[n + 1];           // Chaves Entradas
    int p[n + 1];           // Custo válido
    int q[n + 1];           // Custo inválido
    /* Saidas */
    int e[n + 1][n + 1];    // Custos resultantes
    int r[n + 1][n + 1];    // Indices resultantes

    // Chaves
    for(i = 1; i <= n; i++)
        scanf("%d ", &k[i]);

    // Probabilidades acesso válido
    for(i = 1; i <= n; i++)
        scanf("%d ", &p[i]);

    // Probabilidades acesso inválido
    for(i = 0; i <= n; i++)
        scanf("%d ", &q[i]);

    /* Optimal BST */
    optimalBST(p, q, n, e, r);

    return EXIT_SUCCESS;
}