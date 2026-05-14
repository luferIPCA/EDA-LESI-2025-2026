#pragma once

int Sum(int x, int y);

#define N 40

typedef struct Cidade {
	int cod;
	char nome[N];
	int visitado;
	struct Cidade* next;
}Cidade;

typedef struct Adj {
	int codDestino;
	int peso;
	struct Adj* next;
}Adj;


