/*!
 *  @file Dados.h
 *  @author mustl
 *  @date 2026-04-21
 *  @project Biblioteca para Listas Ligadas Simples
 *
 *  Declares the dados.
 *
 */

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#pragma warning (disable:4996)

#define M 100

/*!
 *  Elemento da lista
 */
typedef struct Element {
	int value;
	char nome[M];
	bool apagado;
	struct Element* prox;
}Element;

/*!
 *  Gere a lista de elementos
 */
typedef struct Elements {
	struct Element* head;
	int totalElements;
	struct Elements* tail;
}Elements;


typedef struct ElementFile {
	int value;
	char nome[M];
}ElementFile;

