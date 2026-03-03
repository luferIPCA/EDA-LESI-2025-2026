/**
* Author: lufer
* Email: lufer@ipca.pt
* Date: 2025
* Desc: Módulo de estruturas e tipos globais
*/

//#pragma once

#ifndef DADOSGLOBAIS
#define DADOSGLOBAIS 1

#pragma region Dados

#define N 20
#define M 20

typedef struct Carro {
	int ano;
	char marca[N];
}Carro;


typedef struct Objeto {
	char designacao[M];
	float distancia;
}Objeto;

Objeto objetos[N];


#pragma endregion

#pragma region Calculos

int Soma(int x, int y);
int Abs(int n);

#pragma endregion

#pragma region Arrays

int FindMaxArray(int v[], int n);
float AvgDistObject(Objeto v[], int n);

#pragma endregion


#endif 