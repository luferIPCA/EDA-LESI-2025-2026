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
#include <stdlib.h>
#include "Graphs.h"
#include "BFT.h"


//======================================================
//Breath First Algorithm
//======================================================

/**
 * BreadthFirstSearch - Procura em Largura
 * Objetivo: Encontrar um alvo específico e retornar o seu índice.
 */
int BreadthFirstSearch(int adjMatrix[][MAX], Vertice setVertices[], int vertCount, char alvo) {
    int queue[MAX];
    int front = 0;
    int rear = -1;
    int count = 0;

    if (vertCount <= 0) return -1;

    // Inicializar primeiro nó
    setVertices[0].visitado = true;
    queue[++rear] = 0;
    count++;

    while (count != 0) {
        int currentIdx = queue[front++];
        count--;

        // VERIFICAÇÃO DO ALVO
        if (setVertices[currentIdx].nome == alvo) {
            limparVisitados(setVertices, vertCount);
            return currentIdx;
        }

        for (int i = 0; i < vertCount; i++) {
            if (adjMatrix[currentIdx][i] != 0 && !setVertices[i].visitado) {
                setVertices[i].visitado = true;
                queue[++rear] = i;
                count++;
            }
        }
    }

    limparVisitados(setVertices, vertCount);
    return -1;
}

/**
 * BFSTraversal - Travessia em Largura
 * Objetivo: Visitar todos os nós por camadas (níveis).
 */

void BFSTraversal(int adjMatrix[][MAX], Vertice setVertices[], int vertCount) {
        int queue[MAX];
        int front = 0;
        int rear = -1;
        int count = 0;

        // Acesso com PONTO (.) porque setVertices[0] é a própria estrutura
        setVertices[0].visitado = true;
        setVertices[0].distance = 0;
        queue[++rear] = 0;
        count++;

        while (count != 0) {
            int currentIdx = queue[front++];
            count--;

            printf("Visitado: %c\n", setVertices[currentIdx].nome);

            for (int i = 0; i < vertCount; i++) {
                // Usamos o ponto (.) em todo o lado
                if (adjMatrix[currentIdx][i] != 0 && !setVertices[i].visitado) {
                    setVertices[i].visitado = true;
                    setVertices[i].distance = setVertices[currentIdx].distance + 1;
                    queue[++rear] = i;
                    count++;
                }
            }
        }

        // Reset final
        for (int i = 0; i < vertCount; i++) setVertices[i].visitado = false;
}


//==================================================
/* Exercício
Grafo Pesado com distâncias entre vértices (cidades)

Devolver a cidade que se encontra mais perto....e não foi visitada!!
*/
//==================================================