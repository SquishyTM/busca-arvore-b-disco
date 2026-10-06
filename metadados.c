#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>

#include "metadados.h"

void imprime_metadados(TMetadados *metadados)
{
	printf("%d, %d, %d\n", metadados->d, metadados->pont_raiz, metadados->pont_prox_no_livre);
}

TMetadados *metadados(int d, int pont_raiz, int pont_prox_no_livre)
{
	TMetadados *metadados = (TMetadados *) malloc(sizeof(TMetadados));
	if (metadados) memset(metadados, 0, sizeof(TMetadados));
	metadados->d = d;
	metadados->pont_raiz = pont_raiz;
	metadados->pont_prox_no_livre = pont_prox_no_livre;
	return metadados;
}

void salva_metadados(TMetadados *metadados, FILE *out)
{
	fwrite(&metadados->d, sizeof(int), 1, out);
	fwrite(&metadados->pont_raiz, sizeof(int), 1, out);
	fwrite(&metadados->pont_prox_no_livre, sizeof(int), 1, out);
}

void salva_arq_metadados(char *nome_arquivo, TMetadados *metadados)
{
	FILE *out = fopen(nome_arquivo, "wb");
	salva_metadados(metadados, out);
	fclose(out);
}

TMetadados *le_metadados(FILE *in)
{
	TMetadados *metadados = (TMetadados *) malloc(sizeof(TMetadados));
	if (0 >= fread(&metadados->d, sizeof(int), 1, in)) {
		free(metadados);
		return NULL;
	}
	fread(&metadados->pont_raiz, sizeof(int), 1, in);
	fread(&metadados->pont_prox_no_livre, sizeof(int), 1, in);
	return metadados;
}

TMetadados *le_arq_metadados(char *nome_arquivo)
{
	FILE *in = fopen(nome_arquivo, "rb");
	TMetadados *resultado = le_metadados(in);
	fclose(in);
	return resultado;
}

int tamanho_metadados()
{
	return sizeof(int) + //d
	    sizeof(int) + // pont_raiz
		sizeof(int); // pont_prox_no_livre
}