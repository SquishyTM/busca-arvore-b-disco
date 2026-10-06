#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "no.h"

void imprime_no(int d, TNo *no)
{
	int i;
	printf("NO: %d, %d, (", no->m, no->pont_pai);
	for (i = 0; i < 2 * d; i++) {
		printf("%d, ", no->p[i]);
	}
	printf("%d) \n", no->p[i]);
	for (i = 0; i < 2 * d; i++) {
		if (no->clientes[i])
			imprime_cliente(no->clientes[i]);
	}
}

TNo *no(int d, int m, int pont_pai)
{
	int i;
	TNo *no = (TNo *) malloc(sizeof(TNo));
	if (no) memset(no, 0, sizeof(TNo));
	no->m = m;
	no->pont_pai = pont_pai;
	no->p = (int *) malloc(sizeof(int) * (2 * d + 1));
	no->clientes = (TCliente **) malloc(sizeof(TCliente *) * 2 * d);
	for (i = 0; i < 2 * d; i++) {
		no->p[i] = -1;
		no->clientes[i] = NULL;
	}
	no->p[2 * d] = -1;
	return no;
}

TNo *no_vazio(int d)
{
	return no(d, 0, -1);
}

TNo *cria_no(int d, int m, int pont_pai, int size, ...)
{
	TNo *n = no(d, m, pont_pai);
	int i;
	va_list ap;
	va_start(ap, size);
	for (i = 0; i < n->m + 1; i++) {
		n->p[i] = va_arg(ap, int);
	}
	for (i = 0; i < n->m; i++) {
		n->clientes[i] = va_arg(ap, TCliente *);
	}
	va_end(ap);
	return n;
}

void salva_no(int d, TNo *no, FILE *out)
{
	int i;
	fwrite(&no->m, sizeof(int), 1, out);
	fwrite(&no->pont_pai, sizeof(int), 1, out);
	//garantidamente, sempre havera pelo menos 1 chave no noh
    //portanto, p0 sempre vai existir
	fwrite(&no->p[0], sizeof(int), 1, out);

	TCliente *vazio = cliente(-1, "");

	for (i = 0; i < 2 * d; i++) {
		if (no->clientes[i]) {
			salva_cliente(no->clientes[i], out);
		} else {
			salva_cliente(vazio, out);
		}
		fwrite(&no->p[i + 1], sizeof(int), 1, out);
	}
	free(vazio);
}

TNo *le_no(int d, FILE *in)
{
	int i;
	TNo *no = (TNo *) malloc(sizeof(TNo));
	if (0 >= fread(&no->m, sizeof(int), 1, in)) {
		free(no);
		return NULL;
	}
	fread(&no->pont_pai, sizeof(int), 1, in);
	no->p = (int *) malloc(sizeof(int) * (2 * d + 1));
	no->clientes = (TCliente **) malloc(sizeof(TCliente *) * 2 * d);

	fread(&no->p[0], sizeof(int), 1, in);
	for (i = 0; i < no->m; i++) {
		no->clientes[i] = le_cliente(in);
		fread(&no->p[i + 1], sizeof(int), 1, in);
	}

	// Termina de ler dados nulos para resolver problema do cursor
	// Dados lidos sao descartados
	TCliente *vazio;
	for (i = no->m; i < 2 * d; i++) {
		no->clientes[i] = NULL;
		vazio = le_cliente(in);
		fread(&no->p[i + 1], sizeof(int), 1, in);
		free(vazio);
	}
	return no;
}

int tamanho_no(int d)
{
	return sizeof(int) + // m
		sizeof(int) + // pont_pai
		sizeof(int) * (2 * d + 1) + // p
		tamanho_cliente() * (2 * d); // clientes
}

void libera_no(int d, TNo *no)
{
	int i;
	for (i = 0; i < 2 * d; i++) {
		free(no->clientes[i]);
	}
	free(no->clientes);
	free(no->p);
	no->clientes = NULL;
	no->p = NULL;
	free(no);
}