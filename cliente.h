#ifndef BUSCA_ARVORE_B_DISCO_CLIENTE_H
#define BUSCA_ARVORE_B_DISCO_CLIENTE_H

#include <stdio.h>

#define TAM_NOME 100

typedef struct Cliente {
    int cod_cliente;
    char nome[TAM_NOME];
} TCliente;

void imprime_cliente(TCliente *cliente);
TCliente *cliente(int cod, char *nome);
void salva_cliente(TCliente *cliente, FILE *out);
TCliente *le_cliente(FILE *in);
int tamanho_cliente();

#endif //BUSCA_ARVORE_B_DISCO_CLIENTE_H
