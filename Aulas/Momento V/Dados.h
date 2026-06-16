/*!
 * EDA - 2025-2026
*  @file Dados.h
 *  @author mustl
 *  @date 2026-06-03
 *  @project Momento V
 *
 *  Declares the dados.
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma region Questão 1

//Lista Ligada Simples

/*!
 *  Chassis
 */
typedef struct Chassis {
    int numSerie;
    struct Chassis* anterior; // Ponteiro para o chassis que fica "atrás"
} Chassis;

typedef struct LinhaPintura {
    Chassis* topoEntrada;     // Posição mesmo à entrada da cabine
} LinhaPintura;

int RegistarChassis(LinhaPintura* linha, int novoNum);
bool RemoverChassis(LinhaPintura* linhaOriginal, int alvoNum);

#pragma endregion

#pragma region Questão 2

#define TAMTABELA 31
#define SIZENOME 50
#define SIZECARTAO 10


/*!
 *  Hash com listas ligadas simples
 */

/*!
 *  
 */
typedef struct Cacifo {
    char codigoCartao[SIZECARTAO];
    int numeroCacifo;
    char nomeUtente[SIZENOME];
    struct Cacifo* proximo;
} Cacifo;

typedef struct SistemaCartoes {
    Cacifo* corredor[TAMTABELA];
} SistemaCartoes;

// Estrutura auxiliar para gravação direta e limpa em disco
typedef struct CacifoFicheiro {
    char codigoCartao[SIZECARTAO];
    int numeroCacifo;
    char nomeUtente[SIZENOME];
} CacifoFicheiro;


int IndiceHash(char* chave);
int LocalizarCacifo(SistemaCartoes* sistema, char* codigo, char* nomeUtente);
bool InserirNoSistema(SistemaCartoes* sistema, char* cod, int cacifo, char* nome);


#pragma endregion

#pragma region Questão 3

//Árvore Binária de Procura
#define SIZEMATRICULA 9

typedef struct Coima {
    int numCoima;               // Número identificador da coima
    float valorCoima;           // Valor da coima em euros
    struct Coima* seguinte;     // Ponteiro para a próxima coima do mesmo veículo
} Coima;

typedef struct RegistroInfracao {
    char matricula[SIZEMATRICULA]; // Formato "XX-YY-ZZ\0"
    Coima* listaCoimas;
    struct RegistroInfracao* esquerda;
    struct RegistroInfracao* direita;
} RegistroInfracao;

bool CalculaCoima(RegistroInfracao* raiz, char* matricula, float* coima);

#pragma endregion


#pragma region Questão 4

bool GuardarSistemaFicheiro(SistemaCartoes* sistema, char* nomeFicheiro);
bool CarregarSistemaFicheiro(SistemaCartoes* sistema, char* nomeFicheiro);
#pragma endregion