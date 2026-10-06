#ifndef BUSCA_ARVORE_B_DISCO_ARVORE_B_H
#define BUSCA_ARVORE_B_DISCO_ARVORE_B_H

#include <stdio.h>
#include "metadados.h"
#include "no.h"

#define NOME_ARQUIVO_DADOS "clientes.dat"
#define NOME_ARQUIVO_METADADOS "metadados.dat"
#define D 2

TNo *le_no_pos(FILE *arq, int d, int pt);
int posicao(int chave, TNo *no);
TCliente *busca_no(FILE *arq, int d, int ptNo, int chave, int *pt_no, int *qtd_nos_lidos);
TCliente *busca(int chave, char *nome_arquivo_metadados, char *nome_arquivo_dados, int d, int *pt_no, int *qtd_nos_lidos);

#endif //BUSCA_ARVORE_B_DISCO_ARVORE_B_H
