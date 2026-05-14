/**
*
* lufer
*
* Grafos Não Orientados | Orientados
*
* Procura em Profundidade: Stack
* Procura em Largura:		Queue
* Consultar:
* https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/
*/

#include <stdio.h>
#include <stdbool.h>

#ifndef GRF
#define GRF

#define MAX 6 

typedef struct Adj {
	int peso;
}Adj;

//Estruturas para o Grafo 
//
//"Lista" de vértices 
//Vertice* setVertices[MAX];
//
//Matriz de adjacências
//int adjMatrix[MAX][MAX];
//

#pragma region H0 - GRAFO_NAO_ORIENTADO

//Grafo Não orientado

typedef struct {
	int numVertices;
	int matriz[MAX][MAX];
} Grafo;

bool criarGrafo(Grafo* g, int vertices);
bool inserirAresta(Grafo* g, int origem, int destino);
bool removerAresta(Grafo* g, int origem, int destino);
bool mostrarGrafo(Grafo* g);

#pragma endregion

#pragma region H1 - GRAFO_ORIENTADO_PESADO

typedef struct {
	int numVertices;
	int matriz[MAX][MAX];
} GrafoOP;

bool criarGrafoOP(GrafoOP* g, int vertices);
bool inserirArestaOP(GrafoOP* g,int origem,int destino,int peso);
bool removerArestaOP(GrafoOP* g,int origem,int destino);
bool mostrarGrafoOP(GrafoOP* g);

#pragma endregion

#pragma region H2_GRAFO_ESTRUTURADO

//Vertices têm mais informação
// 
//Vertice
typedef struct Vertice {
	char nome;
	bool visitado;
	int distance;
}Vertice;

//Eventualmente usar
typedef struct {
	Vertice vertices[MAX];//outra opção Vertice *vertices[MAX];
	int adjMatrix[MAX][MAX];
	int numVertices;
} GrafoV;

//auxiliar
int vertCount;

bool InitAdj(int m[][MAX], int tot);
//bool AddEdge(GrafoV* g, int start, int end);

bool AddEdge(int adjMatrix[][MAX], int start, int end);
bool AddEdgeWeight(int adjMatrix[][MAX], int start, int end, int peso);
bool AddVertice(Vertice gr[], char label, int* count);
//outra hipotese
//bool AddVerticeII(Vertice* gr[], char label, int *count);
bool ProcessaVertice(Vertice setVertices[], int vertIndex);
//int GetVertAdjunNaoVisitado(int vertIndex);
int GetVertAdjunNaoVisitado(int adjMatrix[][MAX],Vertice setVertices[], int vertIndex);


void limparVisitados(Vertice* setVertices[], int tot);

#pragma endregion

#pragma region H3_GRAFO_MATRIZ_ADJACENCIAS_ESTRUTURADA

bool CriaMatriz(Adj* adjMatrix[][MAX], int totv);
Adj* GetAdjacentes(int vertice, Adj* adjMatrix[][MAX], int totVertice);

#pragma endregion

#endif // 

