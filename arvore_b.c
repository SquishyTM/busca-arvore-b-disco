#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include "arvore_b.h"

/*
 * Le o nó que está na posição pt do arquivo de dados
 */
TNo *le_no_pos(FILE *arq, int d, int pt) {
    fseek(arq, pt, SEEK_SET);
    return le_no(d, arq);
}

/*
 * Busca binária da posição em que a chave deveria estar dentro do nó.
 */
int posicao(int chave, TNo *no) {
    int inicio = 0;
    int fim = no->m;
    int pos = (fim + inicio) / 2;
    while (pos != no->m && chave != no->clientes[pos]->cod_cliente && inicio < fim) {
        if (chave > no->clientes[pos]->cod_cliente) {
            inicio = pos + 1;
        } else {
            fim = pos;
        }
        pos = (fim + inicio) / 2;
    }
    return pos;
}

/*
 * Busca a chave na subárvore cuja raiz está gravada na posição ptNo do arquivo de dados
 * d é a ordem da árvore
 * Retorna uma cópia do cliente encontrado (criada com a função cliente), ou NULL caso a chave não exista
 * Grava em *pt_no a posição (no arquivo de dados) do nó onde a chave foi encontrada, ou -1 caso ela não exista
 * Incrementa *qtd_nos_lidos uma vez para cada nó lido do arquivo de dados
 * (cada nó deve ser lido no máximo uma vez)
 */
TCliente *busca_no(FILE *arq, int d, int ptNo, int chave, int *pt_no, int *qtd_nos_lidos) {
    //TODO: Implementar essa funcao
    return NULL;
}

/*
 * Busca o cliente de código chave na árvore B armazenada em disco
 * d é a ordem da árvore
 * Retorna uma cópia do cliente encontrado (criada com a função cliente), ou NULL caso a chave não exista
 * Grava em *pt_no a posição (no arquivo de dados) do nó onde a chave foi encontrada, ou -1 caso ela não exista
 * Grava em *qtd_nos_lidos a quantidade de nós lidos do arquivo de dados durante a busca
 * Uma árvore vazia (pont_raiz igual a -1) não tem nós para ler
 */
TCliente *busca(int chave, char *nome_arquivo_metadados, char *nome_arquivo_dados, int d, int *pt_no, int *qtd_nos_lidos) {
    //TODO: Implementar essa funcao
    *pt_no = -1;
    *qtd_nos_lidos = 0;
    return NULL;
}

int main () {
    /* Essa função gera a saída que é usada nos testes. Ela NÃO DEVE SER MODIFICADA */

    /* Le do teclado a chave a ser buscada */
    int chave;
    scanf("%d", &chave);

    //Chama função a ser testada
    int pt_no = -1;
    int qtd_nos_lidos = 0;
    TCliente *cli = busca(chave, NOME_ARQUIVO_METADADOS, NOME_ARQUIVO_DADOS, D, &pt_no, &qtd_nos_lidos);

    //Imprime a posição do nó onde a chave foi encontrada
    printf("PONT %d\n", pt_no);

    //Imprime o cliente encontrado (nada é impresso se a chave não existir na árvore)
    printf("CLIENTE:\n");
    if (cli != NULL) {
        imprime_cliente(cli);
    }

    //Imprime a quantidade de nós lidos do arquivo de dados
    printf("NOS LIDOS: %d\n", qtd_nos_lidos);
}
