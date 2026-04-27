//-----------------------------------------------------------------------
// <copyright file="Hashing.c" company="IPCA">
//     Copyright IPCA. All rights reserved.
// </copyright>
// <date>2026</date>
// <author></author>
// <email></email>
// <version></version>
// <desc>Biblioteca para manipular Tabelas de Hash</desc>
// <obs>
// https://cp-algorithms.com/string/string-hashing.html#:~:text=The%20good%20and%20widely%20used%20way%20to%20define,It%20is%20called%20a%20polynomial%20rolling%20hash%20function.
// </obs>
//-----------------------------------------------------------------------

//Tabela de Hash : array de heads de listas!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "Libs\Dados.h"
#include "Libs\Funcoes.h"

#pragma warning( disable : 4996 )

#pragma region ABORDAGEM 
// =================== OUTRA Abordgaem ================
//
//	HashTable é uma struct com uma Hash e um número de índexes

//eventuaalmente..mass evitar: problema em biblotecas, p ex.
//static HashTable ht;


HashTable* CriaHashII(int size) {
	HashTable* aux = (HashTable*)malloc(sizeof(HashTable));
	if (aux == NULL) return NULL;

	aux->max = size;

	for (int i = 0; i < size; i++) {
		aux->tabela[i] = NULL;
	}

	return aux;
}

/*
Outra hipótese: size==MAX!?
*/
HashTable* IniciaHashTable(int size, HashTable *ht) {
	ht->max = size;
	//ou ht->max = MAX;
	for (int i = 0; i < size; i++) {
		ht->tabela[i] = NULL;
	}
	return ht;
}

//ou struct Node** tabela;
/*
HashTable* IniciaHashTable(int size) {
	HashTable* ht = malloc(sizeof(HashTable));
	ht->max = size;
	ht->tabela = calloc(size, sizeof(Node*));
	return ht;
}
*/


/*
Insere no início...EVITAR - Não respeita SOLID: PORQUÊ?
*/
bool InsertSimple(char*val, HashTable *ht)
{
	int h;
	h = Hash(val);

	Element *novo = (Element*)malloc(sizeof(Element));
	if (novo != NULL) {
		novo->value = 0; //não está a ser usado
		strcpy(novo->nome, val);
		novo->prox = ht->tabela[h];
		ht->tabela[h] = novo;
		return true;
	}
	return false;
}


//bool Exist(char *val, NodePtr h);
bool ExisteInHash(HashTable* ht, char* value) {
	if (ht == NULL) return false;
	int index = Hash(value);
	Node* headList = ht->tabela[index];
	if (Exist(value, headList)) return true;
	return false;
}

/*!
 *  Inseres the hash ordenado.
 *
 *      @param [in,out] ht   
 *      @param [in,out] novo 
 *
 *      @return
 *      0: Já existe
 *      -1: Não pode ser inserido
 *      
 */
int InsereHashOrdenado(HashTable* ht, Element* novo) {
	if ((ht == NULL) || novo == NULL) return -1;
	if (ExisteInHash(ht, novo->nome)) return 0;
	int ind = Hash(novo->nome);
	Element* lista = ht->tabela[ind];
	//Element* InsereOrdenado(Element* inicio, Element* novo);
	ht->tabela[ind] = InsereOrdenado( ht->tabela[ind],novo);
	return true;
}

bool RemoveHashNode(HashTable* ht, char* value) {
	if ((ht == NULL) || value == NULL) return -1;
	int index = Hash(value);
	//procura cod associado a value..
	bool r = false;
	//ht->tabela[Hash(value)] = RemoveElement(ht->tabela[Hash(value)],cod,&r);
	return r;
}

bool SaveHashII(HashTable* h, char* fileName) {
	//validações
	if (h == NULL || fileName == NULL) return false;
	FILE* fp = fopen(fileName, "wb");
	if (fp == NULL) return false;

	bool r = false;
	for (int i = 0; i < MAX; i++) {
		if (h->tabela[i] != NULL)
		{
			//r = SaveList(h->tabela[i],fp);
		}
	}
	fclose(fp);
	return r;

}

bool ShowHashII(HashTable* ht) {
	if (ht == NULL) return false;
	for (int i = 0; i < MAX; i++)
		ShowList(ht->tabela[i]);
	return false;
}

#pragma endregion

#pragma region AUXILIARES

// ===================== AUXILIARES ===================

	/*
	* Converte caracter em minúsculas
	*/
int ToUpperCase(char c) {
	/* subtair 21 ao valor ASCII atual do caracter(exemplo:'a'-'A'=32)
	*/
	if ('a' <= c && c <= 'z')
		return c - 32;
	else
		return (int)c;
}

/*
Mostra Tabela de ASCII
*/
void AsciiTable() {
	for (int i = 0; i < 255; i++) {
		printf("%x %d %c\n", i, i, i);
	}
}

/*
Derivação da Função de Hash
*/
int HashIII(char* v, int size) {
	int i, h = v[0];
	for (i = 1; v[i] != '\0'; i++)
		h = (h * 251 + v[i]) % size;
	return h;
}

#pragma endregion

