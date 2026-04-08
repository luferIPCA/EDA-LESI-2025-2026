/*!
 * EDA - 2025-2026
*  @file Dados.h
 *  @author mustl
 *  @date 2026-04-06
 *  @project Aula 9 - Listas Duplamente Ligadas
 *
 *  Declares the dados.
 */
#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

 // Definição do nó
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;


/*!
 *  Gere a lista de elementos
 */
typedef struct List {
	Node* head;
	int totalNodes;
	Node* tail;
}List;

#pragma region ASSINATURA_FUNÇÔES
Node* CriarNodo(int valor);
//Não adequado: Porquê?
//Node* inserirOrdenado(Node* head, int valor, bool* sucesso);

//Adequado
Node* InserirOrdenado(Node* head, Node* novoNo, bool* sucesso);

//Lista controlada
List* InserirOrdenadoControlado(List* lista, Node* novoNo, bool* sucesso);

//Lista controlada com tail
List* InserirOrdenadoControladoTail(List* lista, Node* novoNo, bool* sucesso);
bool MostrarInverso(List* lista);
#pragma endregion