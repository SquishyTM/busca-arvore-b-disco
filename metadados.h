#ifndef BUSCA_ARVORE_B_DISCO_METADADOS_H
#define BUSCA_ARVORE_B_DISCO_METADADOS_H

#include <stdio.h>

typedef struct Metadados {
    int d; //ordem da arvore
    int pont_raiz;
    int pont_prox_no_livre;
} TMetadados;

void imprime_metadados(TMetadados *metadados);
TMetadados *metadados(int d, int pont_raiz, int pont_prox_no_livre);
void salva_metadados(TMetadados *metadados, FILE *out);
void salva_arq_metadados(char *nome_arquivo, TMetadados *metadados);
TMetadados *le_metadados(FILE *in);
TMetadados *le_arq_metadados(char *nome_arquivo);
int tamanho_metadados();

#endif //BUSCA_ARVORE_B_DISCO_METADADOS_H
