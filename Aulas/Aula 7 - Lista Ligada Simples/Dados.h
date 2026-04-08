/*!
 *  @file Dados.h
 *  @author mustl
 *  @date 2026-03-14
 *  @project Aula 7
 *
 *  Define dados.
 *
 *  Rever:
 *      https://www.geeksforgeeks.org/data-types-in-c/

 */

#pragma once

#include <stdbool.h>

#pragma warning (disable:4996)

#define M 100

/*!
 *  Elemento da lista
 */
typedef struct Element {
	int value;
	char nome[M];
	struct Element* prox;
}Element;

/*!
 *  Gere a lista de elementos
 */
typedef struct Elements {
	struct Element* head;
	int totalElements;
}Elements;

/* 
Auxiliar para Inserção
*/
typedef struct {
	Element* inicio;
	bool inserido;
} Resultado;



