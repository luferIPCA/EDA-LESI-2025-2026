/*!
 *  @file Funcoes.h
 *  @author mustl
 *  @date 2026-03-12
 *  @project Aula 6 - Memória Dinamica
 *
 *  Implementação  de funções.
 */

#include "Dados.h"
#include <stdbool.h>
#include <stdlib.h>	//strptime

#pragma once

#pragma region clube
/*!
 *
 *  @clube: Nome do clube 
 */
void ShowClube(Clube c);

Clube* NewClub(int numSocios, char* nomeClube);
Clube* NewClubData(int numSocios, char* nomeClube, char* data);

int NumSocios(Clube c);

#pragma endregion

#pragma region Socio

Socio* CriaSocio(int num, float cota);

void MostraSocio(Socio* h);

#pragma endregion

#pragma region SociosClube

SociosClube* CriaClubeSocios(Clube c);

void MostraSociosClube(SociosClube *h);

bool InsereNovoSocio(Socio *c, SociosClube* sc);

#pragma endregion

#pragma region Auxiliares
struct tm *GetDate(const char* d);
#pragma endregion
