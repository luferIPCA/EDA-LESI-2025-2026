
/*****************************************************************//**
 * @file   hash.h
 * @brief  Tabelas de Hash
 * Index->Lista Ligada
 * @author lufer
 * @date   Abril 2026
 *********************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "Listas.h"
#include "Libs\Dados.h"



#ifndef HASH
#define HASH
#define MAX 31 /* tamanho da tabela de hashing -> recomenda-se que seja primo */

//h1: Tabela de Hash é apenas um array de apontadores para Listas
//static struct Node* hashTable[MAX];	//definir no main() sem ser "static"
//ou
//static struct Node** hashTable;

//h2: Tabela de Hash dentro de uma estrutura para controlo

typedef struct HashTable {
	int max;
	struct Element* tabela[MAX];
}HashTable;

// -----
// RELEMBRAR:
//char* nome;
// ou
//char nome[20];

//Node** ht;
// ou
//Node* ht[]
// -----

#pragma region FUNÇÔES

HashTable* CriaHashII(int size);
HashTable* IniciaHashTable(int size, HashTable* ht);
bool InsertSimple(char* val, HashTable* ht);
bool ExisteInHash(HashTable* ht, char* value);
int InsereHashOrdenado(HashTable* ht, Element* novo);
bool RemoveHashNode(HashTable* ht, char* value);
bool SaveHashII(HashTable* h, char* fileName);
bool ShowHashII(HashTable* h);
#pragma endregion


#pragma region Assinatura de Funcões Auxiliares

//Auxiliares
void AsciiTable();
int ToUpperCase(char c);


#pragma endregion

#endif // !HASH

