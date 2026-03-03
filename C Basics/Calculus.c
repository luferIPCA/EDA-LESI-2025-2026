/**
 * @file Calculus.exe
 * @brief Programa principal para testar a biblioteca Calc
 * @author lufer
 * @contact lufer@ipca.pt
 * @date 12-02-2026
 */

#include <stdio.h>
#include <stdlib.h>  // para rand() e srand()
#include <time.h>    // para time()

#include "Calc.h"    // incluir a biblioteca

#ifndef SIZE
#define SIZE 10
#endif

int main() {
	//int v[SIZE]={12,34,23,56,47};
	

    int v[SIZE];
    
    // Inicializar gerador de números aleatórios
    // valores aleatórios entre 0 e )9 (%100)
    srand((unsigned int)time(NULL));
    for (int i = 0; i < SIZE; i++) {
        v[i] = rand() % 100;
    }

    // Calcula a média chamando a função que está na biblioteca
	float m=CalcAverage(v,SIZE);

    printf("Array size = %d\n", SIZE);
	printf("Average: %4.1f",m);
	
	return 0;
}
