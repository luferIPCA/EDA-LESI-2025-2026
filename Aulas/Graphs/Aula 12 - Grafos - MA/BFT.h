
/*
//Grafos Não Orientados | Orientados
//
// Procura em Profundidade: Stack
// Procura em Largura:		Queue
//lufer

*/

#include "Graphs.h"

#ifndef BFT	//Largura
#define BFT 

#define MAXDISTANCE 9999

//Auxiliar ao Dijkstra
typedef struct Best {
	int distance[MAX];
	int anteriores[MAX];
}Best;

// =====================================================
// Breadth First Algorithm
// =====================================================

//assinaturas
//queue functions
//void insertQueue(int data);
//bool insertQueue(int queue[], int* rear, int data);
//int nextQueue();
//bool isQueueEmpty();

//graphs functions

int BreadthFirstSearch(int adjMatrix[][MAX], Vertice setVertices[], int vertCount, char alvo);

void BFSTraversal(int adjMatrix[][MAX], Vertice setVertices[], int totVertices);

Best bestPath(int adjMatrix[MAX][MAX], int n, int v);

//auxiliar
void ShowAllPath(Best b, int n, int v);
#endif // !BFT