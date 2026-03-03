
/**
 * @file Calc.h
 * @brief Funções de cálculo sobre arrays simples
 * @author lufer <lufer@ipca.pt>
 * @date 12-02-2026
 * @example example.c
 *   
 */


#ifndef BENFICA
#define BENFICA 

 /**
 * @brief Calcula a média dos valores de um vetor de inteiros.
 *
 * @param[in] vals Vetor de inteiros
 * @param[in] size Número de elementos do vetor
 * @return Média dos valores ou 0 se size <= 0
 */
float CalcAverage(int vals[], int size);

typedef struct Person{
    int age;
} Person;

//typedef struct Person Person;


Person v;

#endif

