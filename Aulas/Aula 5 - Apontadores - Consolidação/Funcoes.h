/*!
 * EDA - 2025-2026
*  @file Funcoes.h
 *  @author mustl
 *  @date 2026-03-03
 *  @project Aula 5 - Apontadores - Consolidação
 *
 *  Declares the funcoes.
 */
#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#pragma warning (disable:4996)

#define N 50

typedef struct Uber {
	int cod;
	char nome[N];
	bool ocupado;
}Uber;

/*!
 *  Mostra  uber.
 *
 *      @param [in,out] p
 *
 *      @return
 */
bool MostraUber(Uber* p);

/*!
 *  Define ficha.
 *
 *      @param [in]     cod
 *      @param [in,out] nome
 *      @param [in]     estado
 *      @param [in,out] p
 *
 *      @return
 */
Uber* DefineFicha(int cod, char* nome, bool estado, Uber* p);

/*!
 *  Existe condutor.
 *
 *      @param [in,out] condutores
 *      @param [in]     size
 *      @param [in]     cod
 *
 *      @return
 */
bool ExisteCondutor(Uber* condutores, int size, int cod);

/*!
 *  Mostra  condutores.
 *
 *      @param [in,out] condutores
 *      @param [in]     size
 *
 *      @return
 */
bool MostraCondutores(Uber* condutores, int size);

/*!
 *  Registas the condutor.
 *
 *      @param [in,out] p
 *      @param [in]     condutores
 *      @param [in,out] size
 *
 *      @return
 */
bool RegistaCondutor(Uber* p, Uber condutores[], int* size);
