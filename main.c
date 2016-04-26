#include <stdio.h>
#include <stdlib.h>
#include "libs/arvore.h"

// Comente a linha abaixo para a entrega
//#define DEBUG

/*!
 * \brief imprimirArvore Imprime a árvore binária
 *
 * Imprime a árvore binária, mostrando os nós a direita e a esquerda
 * de uma visualização em ordem da mesma
 * Obs.: A sequência nil indica a falta de próximo nó
 *
 * \param a Árvore a ser impressa
 */
void imprimirArvore(noArvoreInt *a){
    if(a){
        imprimirArvore(a->no_esq);
        if((a->no_esq == NULL) && (a->no_dir == NULL))
            printf("chave: %d fesq: nil fdir: nil\n", a->chave);
        else if((a->no_esq == NULL) || (a->no_dir == NULL))
        if((a->no_esq == NULL))
            printf("chave: %d fesq: nil fdir: %d\n", a->chave, a->no_dir->chave);
        else
            printf("chave: %d fesq: %d fdir: nil\n", a->chave, a->no_esq->chave);
        else
            printf("chave: %d fesq: %d fdir: %d\n", a->chave, a->no_esq->chave, a->no_dir->chave);
        imprimirArvore(a->no_dir);
    }
}

// Adiciona os nós
noArvoreInt *adicionaNo(noArvoreInt *pai, int *chave, int n, int r[][n+1], int i, int j){
    noArvoreInt *p;

    if(i == j){
        p = NULL;
    }
    else{
        p = (ArvoreInt) malloc (sizeof(noArvoreInt));
        p->no_pai = pai;
        p->chave = chave[r[i][j]];
        p->no_esq = adicionaNo(p, chave, n, r, i, r[i][j] - 1);
        p->no_dir = adicionaNo(p, chave, n, r, r[i][j], j);
    }

    return p;
}

// Constroi a arvore
void constroiArvore(ArvoreInt *a, int *chave, int n, int r[][n+1], int i, int j){
    noArvoreInt *p;

    p = (ArvoreInt) malloc (sizeof(noArvoreInt));
    p->no_pai = NULL;
    p->chave = chave[r[i][j]];
    p->no_esq = adicionaNo(p, chave, n, r, i, r[i][j] - 1);
    p->no_dir = adicionaNo(p, chave, n, r, r[i][j], j);

    *a = p;
}

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
        w[i][i] = q[i];
        e[i][i] = q[i];
        root[i][i] = 0;

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

            for(r = indice_menor + 1; r <= root[i+1][j]; r++){
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
    int n, i, j;
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
        scanf("%d", &k[i]);

    // Probabilidades acesso válido
    for(i = 1; i <= n; i++)
        scanf("%d", &p[i]);

    // Probabilidades acesso inválido
    for(i = 0; i <= n; i++)
        scanf("%d", &q[i]);

    /* Optimal BST */
    optimalBST(p, q, n, e, r);

#ifdef DEBUG
    // Printa o custo da matriz e
    printf("DEBUG - MATRIZ DE CUSTOS\n");
    for (i = 0; i <= n; i++) {
        for (j = i; j <= n; j++)
            printf("%d ", e[i][j]);

        printf("\n");
    }

    // Printa os indices presentes na matrix root
    printf("DEBUG - MATRIZ DE INDICES\n");
    for (i = 0; i <= n; i++) {
        for (j = i; j <= n; j++)
            printf("%d ", r[i][j]);

        printf("\n");
    }
#endif

    // Constroi arvore com as tabelas
    constroiArvore(&a, k, n, r, 0, n);

    // Imprime a arvore construida
    imprimirArvore(a);

    return EXIT_SUCCESS;
}
