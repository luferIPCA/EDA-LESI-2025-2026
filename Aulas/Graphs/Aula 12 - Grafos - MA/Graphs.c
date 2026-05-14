/*
Grafos: Fundamentos com MATRIZ DE ADJACENCIAS
lufer

Consultar:
https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/
*/
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>	// ASCII SET
#include "Graphs.h"
//#include <stdlib.h>			//ou <include malloc.h> - malloc()
#include <malloc.h>
//======================================================
//graph functions 
//======================================================

#pragma region H0 - GRAFO_NÂO_ORIENTADO_NAO_PESADO

//Grafo Não orientado

/*!
 *  Criar grafo.
 *
 *      @param [in,out] g        
 *      @param [in]     vertices 
 *
 *      @return 
 */
bool criarGrafo(Grafo* g, int vertices) {
	if (vertices <= 0 || vertices > MAX)
		return false;
	g->numVertices = vertices;
	//inicializa grafo
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			g->matriz[i][j] = 0;
		}
	}
	return true;
}

/*!
 *  Inserir aresta.
 *
 *      @param [in,out] g       
 *      @param [in]     origem  
 *      @param [in]     destino 
 *
 *      @return 
 */
bool inserirAresta(Grafo* g, int origem, int destino) {
	if (origem < 0 || destino < 0 || origem >= g->numVertices || destino >= g->numVertices)
		return false;
	g->matriz[origem][destino] = 1;
	g->matriz[destino][origem] = 1;
	return true;
}

/*!
 *  Remove  aresta.
 *
 *      @param [in,out] g       
 *      @param [in]     origem  
 *      @param [in]     destino 
 *
 *      @return 
 */
bool removerAresta(Grafo* g, int origem, int destino) {
	if (origem < 0 || destino < 0 ||
		origem >= g->numVertices ||
		destino >= g->numVertices)
		return false;
	g->matriz[origem][destino] = 0;
	g->matriz[destino][origem] = 0;
	return true;
}

/*!
 *  Mostrar  grafo.
 *
 *      @param [in,out] g 
 *
 *      @return 
 */
bool mostrarGrafo(Grafo* g) {
	if (g->numVertices <= 0)
		return false;
	printf("Matriz de Adjacencias:\n\n");
	for (int i = 0; i < g->numVertices; i++) {
		for (int j = 0; j < g->numVertices; j++) {
			printf("%d ", g->matriz[i][j]);
		}
		printf("\n");
	}
	return true;
}

#pragma endregion

#pragma region H1 - GRAFO_ORIENTADO_PESADO

bool criarGrafoOP(GrafoOP* g, int vertices) {
	if (vertices <= 0 || vertices > MAX)
		return false;
	g->numVertices = vertices;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			g->matriz[i][j] = 0;
		}
	}
	return true;
}

bool inserirArestaOP(GrafoOP* g,int origem,	int destino,int peso) {
	if (origem < 0 || destino < 0 ||
		origem >= g->numVertices ||
		destino >= g->numVertices || peso<=0)
		return false;
	//if (peso <= 0)
	//	return false;
	g->matriz[origem][destino] = peso;
	return true;
}

bool removerArestaOP(GrafoOP* g,int origem,int destino) {
	if (origem < 0 || destino < 0 ||
		origem >= g->numVertices ||
		destino >= g->numVertices)
		return false;
	g->matriz[origem][destino] = 0;
	return true;
}

bool mostrarGrafoOP(GrafoOP* g) {
	if (g->numVertices <= 0)
		return false;
	printf("Matriz de Adjacencias com Custos:\n\n");
	for (int i = 0; i < g->numVertices; i++) {
		for (int j = 0; j < g->numVertices; j++) {
			printf("%3d ", g->matriz[i][j]);
		}
		printf("\n");
	}
	return true;
}

#pragma endregion

#pragma region H2_GRAFO_ESTRUTURADO

//Com ou Sem Estrutura de controlo
//Com array de vertices

/*
Inicializa a matriz de adjacências
*/
bool InitAdj(int m[][MAX], int tot) {
	//validações...=> return false;
	if (tot <= 0 || tot > MAX) return false;
	for (int i = 0; i<tot; i++)  
	{
		for (int j = 0; j<tot; j++) // matrix to 0 
			m[i][j] = 0;
	}
	return true;
}


/*
Insere vertice no grafo
Melhorar com "bool AddVertice (graph, vertice)"
*/
bool AddVertice(Vertice gr[], char label, int* count) {
	if (*count <0 || *count>MAX) return false;
	//insere
	gr[(*count)].distance = 0;
	gr[(*count)].nome = label;//porque é "char", senão usar strcpy
	gr[(*count)++].visitado = false;
	return false;
}

/*
* Outra hipotese
Insere vertice no grafo
Melhorar com "bool AddVertice (graph, vertice)": SOLID
*/
bool AddVerticeII(Vertice* gr[], char label, int *count) {
	if (*count <0 || *count>MAX) return false;
	//insere
	struct Vertice* novoVert = (struct Vertice*) malloc(sizeof(struct Vertice));
	if (novoVert) {
		novoVert->nome = label;
		novoVert->visitado = false;
		gr[(*count)++] = novoVert;
		return true;
	}
	return false;
}

/*
Adicionar aresta ao conjunto de arestas. Grafo não orientado!
*/
bool AddEdge(int adjMatrix[][MAX], int start, int end) {
	//testes...return false
	adjMatrix[start][end] = 1;
	adjMatrix[end][start] = 1;
	return true;
}

bool AddEdgeII(GrafoV*g, int start, int end) {
	//testes...return false
	g->adjMatrix[start][end] = 1;
	g->adjMatrix[end][start] = 1;
	return true;
}

bool AddEdgeWeight(int adjMatrix[][MAX], int start, int end, int peso) {
	//testes...return false
	adjMatrix[start][end] = peso;
	adjMatrix[end][start] = peso;
	return true;
}

//Processa vertice: exemplo, mostrar!
bool ProcessaVertice(Vertice setVertices[], int vertIndex) {
	//validações..return false
	printf("\nVertice %c (%d) \n ", setVertices[vertIndex].nome, vertIndex);
	return true;
}

//encontra vertice adjacente mas não visitado
int GetVertAdjunNaoVisitado(int adjMatrix[][MAX], Vertice setVertices[], int vertIndex) {
	int i;

	for (i = 0; i<vertCount; i++) {
		//if (adjMatrix[vertIndex][i] == 1 && setVertices[i]->visitado == false)
		if (adjMatrix[vertIndex][i] >0 && setVertices[i].visitado == false)
			return i;
	}
	return -1;
}

#pragma endregion

#pragma region H3_GRAFO_MATRIZ_ADJACENCIAS_ESTRUTURADA

bool CriaMatriz(Adj* adjMatrix[][MAX], int totalVertices) {
	if (totalVertices<0 || totalVertices>MAX) return false;
	for (int i = 0; i < totalVertices; i++) {
		for (int j = 0; j < totalVertices; j++)
			adjMatrix[i][j] = NULL;
	}
	return true;
}
/*!
 *  ATENÇÃO:
 *  (Alterar int adjMatrix[][MAX] para Adj* adjMatrix[][MAX])
 *
 *  Returns the adjacentes.
 *
 *      @param [in] vertice    
 *      @param [in] adjMatrix  
 *      @param [in] totVertice 
 *
 *      @return The adjacentes.
 *      ATENÇÃO: MELHORAR
 */
Adj* GetAdjacentes(int vertice, Adj* adjMatrix[][MAX], int totVertice) {
	if (totVertice <= 0 || vertice <0 || vertice>MAX) return NULL;

	Adj* adjs = (Adj*)malloc(sizeof(Adj)*MAX);//pode não ser necessário MAX
	int auxTot = 0;
	if (!adjs) return NULL;
	for (int i = 0; i < MAX; i++) {
		if (adjMatrix[vertice][i]!=NULL && adjMatrix[vertice][i]->peso > 0)
		{
			adjs[auxTot]= *adjMatrix[vertice][i];
			auxTot++;
		}
	}
	return adjs;
}

#pragma endregion
