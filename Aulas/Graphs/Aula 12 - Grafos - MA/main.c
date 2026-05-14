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
#include "BFT.h"
#include "DFT.h"
#include <stdlib.h>

int main() {
	setlocale(LC_ALL, "Portuguese");


#pragma region H0 - GRAFO_NAO_ORIENTADO

	//Exemplo de Criação de matriz
	//#define N 4
	//int matriz[N][N] = {
	//	{0, 1, 1, 0},
	//	{1, 0, 1, 1},
	//	{1, 1, 0, 0},
	//	{0, 1, 0, 0}
	//};

	Grafo g;

	if (!criarGrafo(&g, 5)) {
		printf("Erro ao criar grafo\n");
		return 1;
	}

	if(inserirAresta(&g, 0, 1)) {
		printf("Aresta 0-1 inserida\n");
	}
	else {
		printf("Erro ao inserir aresta 0-1\n");
	};
	inserirAresta(&g, 0, 2);
	inserirAresta(&g, 1, 3);
	inserirAresta(&g, 3, 4);

	mostrarGrafo(&g);

	printf("\nRemover aresta 0-2\n\n");

	removerAresta(&g, 0, 2);

	mostrarGrafo(&g);

#pragma endregion

#pragma region H0 - GRAFO_ORIENTADO_PESADO

//Explorar

#pragma endregion

#pragma region H2_GRAFO_MATRIZ_ADJ

	//Estruturas para o Grafo 
	//Adjacencias: Array 2D (matriz) de 0 ou 1: Existe ou não Adjacência	
	int adjMatrix[MAX][MAX];

	Vertice setVertices[MAX];
	//outra hipótese
	//Vertices: "array" de apontadores para vértices 
	//Vertice* setVertices[MAX];

	//ou simplesmente
	//GrafoV g;

	bool aux;
	vertCount = 0;
    
	//Constroi vertices do grafo
	aux = AddVertice(setVertices, 'S', &vertCount);   // 0 
	aux = AddVertice(setVertices, 'A', &vertCount);   // 1 
	aux = AddVertice(setVertices, 'B', &vertCount);   // 2 
	aux = AddVertice(setVertices, 'C', &vertCount);   // 3 
	aux = AddVertice(setVertices, 'D', &vertCount);   // 4 
	aux = AddVertice(setVertices, 'E', &vertCount);   // 5
  
	//outra hipotese
	// aux = AddVerticeII(setVertices, 'E', &vertCount); 
	
	//cri matriz
	aux = InitAdj(adjMatrix, MAX);
	//Grafo não pesado
	// 
	//AddEdge(0, 1, 7);    // S - A 
	//AddEdge(0, 2, 12);   // S - B 
	//AddEdge(0, 3, 9);    // S - C 
	//AddEdge(1, 4, 3);    // A - D 
	//AddEdge(2, 4, 7);    // B - D 
	//AddEdge(3, 4, 1);    // C - D 

	//Grafo Pesado
	aux = AddEdgeWeight(adjMatrix,0, 1, 8);    // S - A 
	aux = AddEdgeWeight(adjMatrix,0, 2, 12);    // S - B 
	aux = AddEdgeWeight(adjMatrix,0, 3, 9);    // S - C 
	aux = AddEdgeWeight(adjMatrix, 1, 4, 3);    // A - D 
	aux = AddEdgeWeight(adjMatrix, 2, 4, 7);    // B - D 
	aux = AddEdgeWeight(adjMatrix, 3, 4, 1);    // C - D 
	aux = AddEdgeWeight(adjMatrix, 3, 5, 2);    // C - E 
   
	//Mostra um determinado vertice
	if (!ProcessaVertice(setVertices, 3)) {
	};

#pragma endregion

#pragma region H3_GRAFO_MATRIZ_ADJACENCIAS_II

	//Vertices: 0...N
	//Estruturas para o Grafo 
	//Array 2D (matriz) de apontadores para Adjacências
	Adj* matriz[MAX][MAX];

	bool r= CriaMatriz(matriz, MAX);

	//cria uma adjacência
	Adj* adj = (Adj*)malloc(sizeof(Adj));
	if (!adj) exit(0);
	adj->peso = 1;

	//Regista Adjacências entre vertices 4 e 5

	//Grafo Não orientado
	matriz[4][5] = adj;
	matriz[5][4] = adj;

	//Grafo Orientado: pesos diferentes
	matriz[4][5]->peso = 12;
	matriz[5][4]->peso = 23;

	Adj* adjacentes = GetAdjacentes(4, matriz, MAX);

#pragma endregion

#pragma region TRAVESSIA
	
	printf("\nTravessia Breadth First:\n");
	BFSTraversal(adjMatrix, setVertices,MAX);
	

	printf("\nTravessia Depth First:\n"); 
	DFSTraversal(adjMatrix, setVertices, MAX);
	int idx = DepthFirstSearch(adjMatrix, setVertices, MAX, 'D');

	if (idx != -1) {
		printf("O vértice %c foi encontrado no índice %d.\n", setVertices[idx].nome, idx);
	}
	else {
		printf("Vértice não encontrado.\n");
	}


	/*Best b = bestPath(adjMatrix, MAX, 0);
	
	ShowAllPath(b, MAX, 0);*/

#pragma endregion

	printf("\n");
	system("pause");
	return 0;
} 

/*
Exercício: Gestão de Caminhos

struct vertex{
int ID;
string name;
int district;
bool visited;
int distance;
vector<adjVertex> adj;
};

*/
