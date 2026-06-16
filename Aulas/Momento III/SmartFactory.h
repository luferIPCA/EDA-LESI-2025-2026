/*!
 * EDA - 2025-2026
*  @file SmartFactory.h
 *  @author mustl
 *  @date 2026-04-30
 *  @project EDA - Momento de avaliação III
 *
 *  Declaração the dados.
 */
#pragma once

#include <stdio.h>
#include <stdlib.h> //malloc

/*!
 *  Estrutura de uma máquina
 */
typedef struct Maquina {
    int num;        // Identificador Maquina
    double tempo;   // Tempo de operação
    int estado;     // 1 para Ativa, 0 para Avariada
} Maquina;

/*!
 *  Nodo da Lista Ligada (Sequência de máquinas na Linha)
 */
typedef struct ListaMaquinas {
    Maquina maquina;
    struct ListaMaquinas* prox;
} ListaMaquinas;

typedef struct LinhaProducao {
    char tipo; // ex: 'A', 'B', 'C'
    ListaMaquinas *linha;
} LinhaProducao;

#define TABLE_SIZE 101

/*!
 *  Tabela de Hash para múltiplas linhas de montagem
 *  Tipo A → [M1] → [M3] → [M7]
 */
typedef struct HashTable {
    LinhaProducao* linhas[TABLE_SIZE];
    struct NodoABP* inventario;    //árvore global
} HashTable;


#pragma region HASH_OUTRA_ABORDAGEM

// Tabela de Hash para múltiplas linhas de montagem 
// Cada entrada guarda o tipo (char) e o ponteiro para a sua lista
typedef struct EntradaHashII {
    char tipo;
    ListaMaquinas *linhaProducao;
    struct EntradaHash* proxColisao; // Tratamento de colisões
} EntradaHash;

typedef struct HashTableII {
    EntradaHash* tabela[TABLE_SIZE];
} HashTableII;

#pragma endregion


#pragma region QUESTÃO_3

//Questão 3
//ABP: Árvore Binária de Procura
//Como cada máquina física tem apenas um nó correspondente na árvore
typedef struct NodoABP {
    Maquina *pMaquina;      // Aponta para a máquina real
    struct NodoABP* esq, * dir;
} NodoABP;

#pragma endregion


#pragma region ASSINARURA_FUNÇÕES
// Todos os métodos devolvem 1 (sucesso) ou 0 (falha)
int Inicializar(HashTable* ht);
int Inserir(HashTable* ht, int produtoID, Maquina m);
float VerificarLinha(HashTable* ht, int produtoID);
int AtualizarMaquina(HashTable* ht, int numAntigo, Maquina nova);
int GravarDados(HashTable* ht, const char* nomeFicheiro);
int CarregarDados(HashTable* ht, const char* nomeFicheiro);

// Métodos da ABP (Inventário)
int InserirNaABP(NodoABP* raiz, Maquina *pm);
void ListarInventarioOrdenado(NodoABP *raiz); // Travessia In-Order

#pragma endregion