

#include "Funcoes.h"

#define N 50

/*!
 *  Mostra  uber.
 *
 *      @param [in,out] p
 *
 *      @return
 */
bool MostraUber(Uber* p) {
	if (p == NULL) return false;
	printf("Nome: %s\n", p->nome);
	printf("Estado: %d\n", p->ocupado);
	return true;
}

Uber* DefineFicha(int cod, char* nome, bool estado, Uber* p) {
	if (p == NULL) return NULL;
	p->cod = cod;
	strcpy(p->nome, nome);
	p->ocupado = estado;
	return p;
}

bool ExisteCondutor(Uber* condutores, int size, int cod) {
	Uber* aux = condutores;
	if (size <= 0) return false;
	for (int i = 0; i < size; i++)
		if (aux++->cod == cod) return true;
	return false;
}

bool MostraCondutores(Uber* condutores, int size) {
	if (size <= 0 || condutores == NULL) return false;
	for (int i = 0; i < size; i++)
		MostraUber(&condutores[i]);
	return true;
}

bool RegistaCondutor(Uber* p, Uber condutores[], int* size) {
	if (*size == N) return false;
	if (ExisteCondutor(condutores, *size, p->cod) == true) return false;
	condutores[*size] = *p;
	++*size;
	return true;
}