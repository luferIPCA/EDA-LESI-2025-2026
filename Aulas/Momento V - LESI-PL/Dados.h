/*!
 * EDA - 2025-2026
*  @file Dados.h
 *  @author mustl
 *  @date 2026-06-08
 *  @project Momento V - LESI-PL
 *
 *  Declara dados.
 */
#pragma once
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#pragma warning( disable : 4996 ) 
#pragma region Q1

typedef struct Musica {
    char titulo[100];
    int reproducoes;
    struct Musica* seguinte; // lista de músicas
} Musica;

typedef struct Artista {
    char nomeArtista[100];
    Musica* listaMusicas;    // Cabeça da lista dinâmica de músicas do artista
    struct Artista* esquerda; // Subárvore 
    struct Artista* direita;  // Subárvore 
} Artista;

bool calcularTotalReproducoes(Artista* raiz, char* nomeAlvo, int* totalOuvido);

#pragma endregion

#pragma region Q2

typedef struct Contentor {
    int idContentor;
    struct Contentor* abaixo;
} Contentor;

typedef struct Cais {
    Contentor* topoAcessivel;
} Cais;

int empilharContentor(Cais* cais, int idNovo);
bool carregarNoCamiao(Cais* caisOriginal, int id);

#pragma endregion

#pragma region Q3

#define TAMTABELA 37 //tamanho primo para Hash


typedef struct NoATM {
    char codigoTerminal[20]; // ex: "ATM-PT-8812"
    char cidade[50];
    int saldoDisponivel;
    struct NoATM* proximo;   // Lista ligada para gerir colisões 
} NoATM;

typedef struct SistemaBancario {
    NoATM* tabelaTerminais[TAMTABELA]; // hash
} SistemaBancario;

bool inserirNoSistemaParaCarregamento(SistemaBancario* sistema, char* cod, char* cid, int saldo);

#pragma endregion

#pragma region Q4

//Exercício 3
//Estrutura auxiliar simplificada para escrita em ficheiro, sem apontadores
typedef struct DadosATM {
    char codigoTerminal[20];
    char cidade[50];
    int saldoDisponivel;
} DadosATM;

bool guardarSistemaBancario(SistemaBancario* sistema, char* nomeFicheiro);
bool carregarSistemaBancario(SistemaBancario* sistema, char* nomeFicheiro);

#pragma endregion