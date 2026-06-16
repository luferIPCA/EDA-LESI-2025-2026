
#pragma once
#include "Dados.h"

// Questão 1
bool Atualiza(int* x, int* y, int z);

// Questão 2
bool ContaPares(int* valores, int tamanho, int x, int* total);

// Questão 3
int MostraCarro(Carro* c);
bool CriaFichaCarro(Carro* c, char* matricula, char* nome);
Carro* CriaFichaCarroII(char* matricula, char* nome, bool* res);
Carro* EncontraCondutor(Parque* p, char* mat);
