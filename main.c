/*!
 * Trabalho I de MATA52 - Analise e Projetos de Algoritmos
 * 
 * Implementação Arvore de Busca Binária Otima
 *
 * Alunos:
 * 	Airton Serra Ribeiro Sena
 * 	Jeferson Lima de Almeida
 * 	Wilton Leonardo Carvalho da Silva Junior
 */

#include <stdio.h>
#include <stdlib.h>
#include "libs/arvore.h"

// Comente a linha abaixo para a entrega
//#define DEBUG

/* Estrutura de Itens */
typedef struct{
    float valor;
    float peso;
} Itens;

// Contador global
int cont;

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
        if((a->no_esq == NULL) && (a->no_dir == NULL)){
            printf("chave: d%d fesq: nil fdir: nil\n", cont);
            cont++;
            printf("chave: %d fesq: d%d fdir: d%d\n", a->chave, (cont - 1), cont);
            printf("chave: d%d fesq: nil fdir: nil\n", cont);
            cont++;
	}           
        else if((a->no_esq == NULL) || (a->no_dir == NULL)){
            if((a->no_esq == NULL)){
                printf("chave: d%d fesq: nil fdir: nil\n", cont);
                printf("chave: %d fesq: d%d fdir: %d\n", a->chave, cont, a->no_dir->chave);
                cont++;
            }
            else{
                printf("chave: %d fesq: %d fdir: d%d\n", a->chave, a->no_esq->chave, cont);
                printf("chave: d%d fesq: nil fdir: nil\n", cont);
                cont++;
            }
        }
        else{
            printf("chave: %d fesq: %d fdir: %d\n", a->chave, a->no_esq->chave, a->no_dir->chave);
        }
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



int main(int argc, char *argv[]){
    int n, i;
    float m;
    ArvoreInt a;
    
    // Contador
    cont = 0;

    // Inicializa a arvore
    inicializa(&a);

    // Numero de entradas
    scanf("%d", &n);

    /* Entradas */
    Itens itens[n+1];

    for(i = 0; i < n; i++)
        scanf("%f", &itens[i].valor);

    for(i = 0; i < n; i++)
        scanf("%f", &itens[i].peso);

    scanf("%f", &m);



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

    return EXIT_SUCCESS;
}
