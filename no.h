#ifndef BUSCA_ARVORE_B_DISCO_NO_H
#define BUSCA_ARVORE_B_DISCO_NO_H

#include <stdio.h>
#include "cliente.h"

typedef struct No {
    int m; //quantidade de chaves armazenadas no nó
    int pont_pai; //posição do nó pai no arquivo de dados
    int *p; //array de ponteiros (posições no arquivo de dados) para os filhos
    TCliente **clientes; //array de clientes
} TNo;

void imprime_no(int d, TNo *no);
TNo *no(int d, int m, int pont_pai);
TNo *no_vazio(int d);
TNo *cria_no(int d, int m, int pont_pai, int size, ...);
void salva_no(int d, TNo *no, FILE *out);
TNo *le_no(int d, FILE *in);
int tamanho_no(int d);
void libera_no(int d, TNo *no);

#endif //BUSCA_ARVORE_B_DISCO_NO_H
