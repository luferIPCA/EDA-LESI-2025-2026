/*!
 * EDA - 2025-2026
*  @file Dados.h
 *  @author mustl
 *  @date 2026-06-16
 *  @project Momento I
 *
 *  Declaração the dados.
 */

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning (disable:4996)
 //ou #define _CRT_SECURE_NO_WARNINGS


#define MAXSIZE 100  // Para Questão 2 


//Questão 3
#define MAXMATRICULA 20
#define MAXNOME 50
#define MAXPARQUE 100

typedef struct {
    char matricula[MAXMATRICULA];
    char dono[MAXNOME];
} Carro;

typedef struct {
    Carro carros[MAXPARQUE];
    int total;
} Parque;
