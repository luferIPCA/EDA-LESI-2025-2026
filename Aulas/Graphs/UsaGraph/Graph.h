#pragma once

int Sum(int x, int y);

#define N 40

struct Cidade {
	char nome[N];
	int visitado;
	struct Cidade* next;
}Cidade;


