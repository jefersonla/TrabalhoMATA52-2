/*!
 * Trabalho I de MATA52 - Analise e Projetos de Algoritmos
 * 
 * Implementação do algoritmo KNAPSACK 0-1, e RKNAPSAC
 * que são implementações binárias e fracionárias do
 * problema da mochila
 *
 * Alunos:
 * 	Airton Serra Ribeiro Sena
 * 	Jeferson Lima de Almeida
 * 	Wilton Leonardo Carvalho da Silva Junior
 */

#include <stdio.h>
#include <stdlib.h>

// Comente a linha abaixo para a entrega
//#define DEBUG

/* Tipo de itens que podem ser postos na mochila */
typedef struct{
    float proporcao;
    float valor;
    float peso;
} Item;

// Variaveis auxiliares
float proximo_valor = -1;

/* Função de corte */
float Bound(int n, float mochila, Item *itens, int pos_atual, float va, float pa){
    int i;
    float valor_atual = va;
    float peso_atual = pa;

    // Enquanto houver itens
    for(i = pos_atual; i <= n; i++){
        peso_atual += itens[i].peso;
        // Se o peso atual for menor que a mochila continue adicionando itens
        if(peso_atual < mochila)
            valor_atual += itens[i].valor;
        // Caso contrário pare a adição de itens na mochila
        else
            return (valor_atual + (1 - (peso_atual - mochila) / itens[i].peso) * itens[i].valor);
    }

    // Se foi possível adicionar todos os itens, retornamos o total
    return valor_atual;
}

/* Algoritmo Knapsack Binário */
void Knapsack(int n, float mochila, Item *itens, int *res_bin, int* aux, int pos_atual, float valor_atual, float peso_atual){
    int i;

    // Se a posição atual é maior que n paramos a execução
    if(pos_atual > n)
        return;

    // Se o peso atual mais o peso da posição que está sendo lida for menor que a mochila
    if(peso_atual + itens[pos_atual].peso <= mochila){
        // Adicionamos o item a lista de itens
        aux[pos_atual] = 1;

        // Chamamos recursivamente o algoritmo
        Knapsack(n, mochila, itens, res_bin, aux, pos_atual + 1,
                 valor_atual + itens[pos_atual].valor, peso_atual + itens[pos_atual].peso);

        // Se estamos na última posição do vetor, e ela é válida
        if(((valor_atual + itens[pos_atual].valor) > proximo_valor) && (pos_atual == n)){
            // Salvamos o valor da variavel auxiliar
            proximo_valor = valor_atual + itens[pos_atual].valor;

            // Atualizamos a resposta
            for(i = 0; i <= pos_atual; i++)
                res_bin[i] = aux[i];
        }
    }

    // Se o retorno da função bound for maior ou igual ao próximo valor
    if(Bound(n, mochila, itens, pos_atual, valor_atual, peso_atual) >= proximo_valor){
        // Removemos o item da lista de itens
        aux[pos_atual] = 0;

        // Chamamos recursivamente o algoritmo
        Knapsack(n, mochila, itens, res_bin, aux, pos_atual + 1, valor_atual, peso_atual);
        if((valor_atual > proximo_valor) && (pos_atual == n)){
            // Salvamos o valor da variavel auxiliar
            proximo_valor = valor_atual;

            // Atualizamos a resposta
            for(i = 0; i <= pos_atual; i++)
                res_bin[i] = aux[i];
        }
    }
}

/* Algoritmo Knapsack Fracionário */
void RKnapsack(int n, float mochila, Item *itens, float *res_frac){
    int i = 0;
    float valor_atual = 0;
    float peso_atual = 0;

    // Enquanto o peso atual for menor que a mochila, e houver itens restante
    while((peso_atual < mochila) && (i < n)){
        // Se o peso atual somado ao peso do item atual é menor que a mochila
        // Adicionamos o item inteiro a mochila
        if(peso_atual + itens[i].peso <= mochila){
            peso_atual += itens[i].peso;
            valor_atual += itens[i].valor;
            res_frac[i] = 1;
            i++;
        }
        // Caso contrário, adicionamos apenas uma parte do item
        else{
            res_frac[i] = (mochila - peso_atual) / itens[i].peso;
            peso_atual = mochila;
            valor_atual += res_frac[i] * itens[i].valor;
            i++;
        }
    }
}

/* Compara itens QuickSort */
int compareItem(const void *iten1, const void *iten2){
    return  ((Item *) iten1)->proporcao > ((Item *) iten2)->proporcao ? -1 :
            ((((Item *) iten1)->proporcao == ((Item *) iten2)->proporcao) ? 0 : 1);
}

int main(int argc, char *argv[]){
    int n, i;
    float m;

    // Numero de entradas
    scanf("%d", &n);

    /* Entradas */
    float res_fracionaria[n];
    int res_binario[n];
    int aux_itens[n];
    Item itens[n];

    for(i = 0; i < n; i++)
        scanf("%f", &itens[i].valor);

    for(i = 0; i < n; i++) {
        scanf("%f", &itens[i].peso);

        // Proporção
        itens[i].proporcao  = itens[i].valor / itens[i].peso;

        // Inicializa res_fracionaria
        res_fracionaria[i] = 0;

        // Inicializa res_binario
        res_binario[i] = 0;
    }

    // Tamanho da mochila
    scanf("%f", &m);

    /* Ordena os arrays usando o quicksort */
    qsort(itens, (sizeof(itens) / sizeof(Item)), sizeof(Item), compareItem);

    /* Executa o algoritmo da mochila binário */
    Knapsack(n - 1, m, itens, res_binario, aux_itens, 0, 0.0, 0.0);

    /* Executa o algoritmo da mochila fracionário */
    RKnapsack(n, m, itens, res_fracionaria);

#ifdef DEBUG
    // Printa o resultado numa forma linda, porém apenas para debug
    float saida = 0;

    /* Resultado Binário */
    printf("Binario\n");
    printf("\n\tItem\tPeso\tValor\tSelecionado");
    for(i = 0; i < n; i++)
        printf("\n\t%d\t%.1f\t%.1f\t%d", i + 1, itens[i].peso, itens[i].valor, res_binario[i]);

    printf("\n\nA mochila ira carregar os seguintes Item: ");
    for(i = 0; i < n; i++)
        if(res_binario[i]){
            printf("%d ", i + 1);
            saida += itens[i].valor;
        }

    printf("\n Lucro Maximo: %.1f ", saida);

    /* Resultado Fracionário */
    saida = 0;
    printf("\n\nFracionario\n");
    printf("\n\tItem\tPeso\tValor\tQuantidade");
    for(i = 0; i < n; i++){
        printf("\n\t%d\t%.1f\t%.1f\t%.1f\t", i + 1, itens[i].peso, itens[i].valor, res_fracionaria[i]);
    }

    printf("\n\nA mochila ira carregar os seguintes Item: ");
    for(i = 0; i < n; i++) {
        if(res_fracionaria[i] != 0.0){
            printf("i%d %.1f ", i + 1, res_fracionaria[i]);
            saida += res_fracionaria[i] * itens[i].valor;
        }
    }

    printf("\n Lucro Maximo: %.1f\n", saida);
#else
    float saida = 0;

    // Acumula o resultado total
    for(i = 0; i < n; i++) {
        saida += res_fracionaria[i] * itens[i].valor;
    }

    // Imprime o resultado final - Fracionada
    printf("%.1f\n", saida);

    // Imprime as respostas fracionárias
    for(i = 0; i < n; i++) {
        if(res_fracionaria[i] != 0){
            printf("i%d %.1f\n", i + 1, res_fracionaria[i]);
        }
    }

    // Acumula o resultado final binária
    for(i = 0, saida = 0; i < n; i++)
        if(res_binario[i]){
            saida += itens[i].valor;
        }

    // Imprime o resultado final - Binária
    printf("%.1f\n", saida);

    // Imprime os itens binários
    for(i = 0; i < n; i++)
        if(res_binario[i]){
            printf("i%d\n", i + 1);
        }
#endif

    // Descomentar a linha abaixo se você estiver no windows e precisar pausar a execução
    // getchar();

    return EXIT_SUCCESS;
}
