#include "cliente.h"
#include "metadados.h"
#include "no.h"
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
    TNo *no_lido;
    TCliente *cliente_encontrado;
    int pos;
    no_lido = le_no_pos(arq, d, ptNo);
    *qtd_nos_lidos += 1;
    pos = posicao(chave, no_lido);
    
    if (pos < no_lido->m && no_lido->clientes[pos]->cod_cliente == chave) {

        *pt_no = ptNo;
        cliente_encontrado = cliente(chave, no_lido->clientes[pos]->nome);
        libera_no(d, no_lido);
        return cliente_encontrado;

    } else {

        if (no_lido->p[pos] == -1) {

        libera_no(d, no_lido);
        return NULL;

        } else {

            cliente_encontrado = busca_no(arq, d, no_lido->p[pos], chave, pt_no, qtd_nos_lidos);
            libera_no(d, no_lido);
            return cliente_encontrado;
        }
    }
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
    FILE *metadados, *dados;
    TMetadados *meta_open;
    TCliente *cliente_encontrado;
    metadados = fopen(nome_arquivo_metadados, "rb");
    dados = fopen(nome_arquivo_dados, "rb");
    if (dados == NULL || metadados == NULL){

        if (metadados != NULL) fclose(metadados);
        if (dados != NULL) fclose(dados);
        return NULL;

    } else {

        meta_open = le_metadados(metadados);
        fclose(metadados);
        
        if (meta_open == NULL || meta_open->pont_raiz == -1){

            fclose(dados);
            if (meta_open != NULL) free(meta_open);
            return NULL;

        } else {

            cliente_encontrado = busca_no(dados, meta_open->d, meta_open->pont_raiz, chave, pt_no, qtd_nos_lidos);
            fclose(dados);
            free(meta_open);
            return cliente_encontrado;
        }
    }
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
