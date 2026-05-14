/*
Grafos: Travessia em Profundidade com Matriz de Adjacências: DFT

Procura em Profundidade: Stack
Procura em Largura:		Queue
lufer
Analisar
--------
Descrição: http://www.geeksforgeeks.org/depth-first-traversal-for-a-graph/
Aplicação: http://www.geeksforgeeks.org/applications-of-depth-first-search/
*/
#include<stdio.h>
#include <stdbool.h>
#include "Graphs.h"
#include "DFT.h"


//inicia variáveis
top = -1;
//vertexCount = 0;

#pragma region STACK
//======================================================
//Stack Functions
//======================================================
void push(int item) {  
   stack[++top] = item;  
}  
 
int pop() {  
   return stack[top--];  
}  
 
int peek() { 
   return stack[top]; 
} 
 
bool isStackEmpty() { 
   return top == -1; 
} 

#pragma endregion

//======================================================
//Depth First Algorithm
//======================================================

/*
DFS
Percorre o grafo em profundidade
*/

/**
 * DepthFirstSearch - Procura um alvo específico.
 * Retorna o índice ou -1 se não encontrar.
 */
int DepthFirstSearch(int adjMatrix[][MAX], Vertice setVertices[], int vertCount, char alvo) {
    int stack[MAX];
    int top = -1;

    if (vertCount <= 0) return -1;

    stack[++top] = 0;

    while (top != -1) {
        int currentIdx = stack[top];

        if (!setVertices[currentIdx].visitado) {
            setVertices[currentIdx].visitado = true;

            // CONDIÇÃO DE PARAGEM: Encontrou o alvo?
            if (setVertices[currentIdx].nome == alvo) {
                limparVisitados(setVertices, vertCount);
                return currentIdx;
            }
        }

        int vizinho = -1;
        for (int i = 0; i < vertCount; i++) {
            if (adjMatrix[currentIdx][i] != 0 && !setVertices[i].visitado) {
                vizinho = i;
                break;
            }
        }

        if (vizinho != -1) {
            stack[++top] = vizinho;
        }
        else {
            top--;
        }
    }

    limparVisitados(setVertices, vertCount);
    return -1;
}

 /**
  * DFSTraversal - Visita todos os nós acessíveis.
  */
void DFSTraversal(int adjMatrix[][MAX], Vertice setVertices[], int vertCount) {
    int stack[MAX];
    int top = -1;

    if (vertCount <= 0) return;

    // Começar pelo primeiro vértice (índice 0)
    stack[++top] = 0;

    printf("--- Iniciando Travessia DFS ---\n");

    while (top != -1) {
        int currentIdx = stack[top];

        // Se ainda não foi visitado, processa-o agora
        if (!setVertices[currentIdx].visitado) {
            setVertices[currentIdx].visitado = true;
            printf("Visitado: %c\n", setVertices[currentIdx].nome);
        }

        // Procurar o primeiro vizinho adjacente não visitado
        int vizinho = -1;
        for (int i = 0; i < vertCount; i++) {
            if (adjMatrix[currentIdx][i] != 0 && !setVertices[i].visitado) {
                vizinho = i;
                break; // "Mergulha" no primeiro que encontrar
            }
        }

        if (vizinho != -1) {
            stack[++top] = vizinho; // Empilha para visitar no próximo ciclo
        }
        else {
            top--; // Backtrack: não há mais vizinhos, volta ao anterior
        }
    }

    limparVisitados(setVertices, vertCount);
    printf("--- Travessia Concluída ---\n");
}

void limparVisitados(Vertice setVertices[], int t) {
    for (int i = 0; i < vertCount; i++) {
        setVertices[i].visitado = false;
        setVertices[i].distance = 0;
    }
}

//==================================================
/* Exercício
Grafo Pesado com distâncias entre vértices (cidades)

Devolver a cidade que se encontra mais perto....e não foi visitada!!
*/
//==================================================