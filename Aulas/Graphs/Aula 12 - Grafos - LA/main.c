/*
Grafos: Fundamentos
lufer
Consultar:
https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/
*/
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>	// ASCII SET
#include "LAGraph.h"



int main() {
	setlocale(LC_ALL, "Portuguese");

#pragma region ARRAY_LISTA_ADJACENCIAS
//======================================
//H1 - Estrutura de Vértices Fixa
//======================================
//Grafo

	Vertice conjuntoVertices[TOTALVERTICES + 1];

	  int i, a, b;

	  bool aux = CriaGraph(conjuntoVertices, TOTALVERTICES);

	  if(!InsereAresta(conjuntoVertices, 7, 1))
		  printf("Aresta entre %d e %d não foi inserida",7,1);
	  //analisar retorno booleano
	  InsereAresta(conjuntoVertices, 0, 1);
	  InsereAresta(conjuntoVertices, 0, 2);
	  InsereAresta(conjuntoVertices, 2, 3);
	  InsereAresta(conjuntoVertices, 3, 1);

	  printf("\nGrafo Orientado\n");
	  MostraGrafo(conjuntoVertices);

	  //======================================
	  //H2 - Grafo não orientado e pesado
	  //======================================
	  
	  int v = 5;
	  struct Graph* g = createGraph(v);
	  //aresta não ponderadas - peso 0
	  if(!addEdge(g, 0, 1))	
		  printf("Aresta entre %d e %d não foi inserida", 0, 1);	//sem peso
	  addEdge(g, 0, 4);
	  addEdge(g, 1, 2);
	  addEdge(g, 1, 3);
	  addEdge(g, 1, 4);

	  //arestas ponderadas
	  if(!addEdgeWeight(g, 2, 3,4.2))
		  printf("Aresta entre %d e %d com peso %0.1f não foi inserida", 2, 3, 4.2);
	  if (!addEdgeWeight(g, 3, 4, (float)7))
		  printf("Aresta entre %d e %d com peso %2.0f não foi inserida", 3, 4, (float)7);
	  if (!addEdgeWeight(g, 2, 6, 14.4))
		  printf("Aresta entre %d e %d com peso %2.0f não foi inserida", 2, 6, 14.2);

	  //Mostra Grafo
	  printf("\nGrafo Não Orientado\n");
	  if(!printGraph(g))
		  printf("Grafo inexistente\n");

	  printf("\nGrafo Não Orientado\n");
	  // mostra a lista de adjacências
	  if(!printGraphWeight(g, true))
		  printf("Grafo inexistente\n");;

	  //Menor Distância saindo de um Vertice v

	  printf("\nMenor Distância saindo de (%d) = %2.1f\n", 2, ShorterDistance(g, 2));


	  //======================================
	  //H3: tudo dinâmico
	  //======================================
	  Node *gr = NULL;

	  gr=CreateGraphTable(gr, 0, "Lisboa");
	  gr = CreateGraphTable(gr, 1, "Porto");
	  gr = CreateGraphTable(gr, 2, "Braga");
	  gr = CreateGraphTable(gr, 3, "Barcelos");
	  gr = CreateGraphTable(gr, 4, "Coimbra");

	  gr = CreateAdjacent(gr, 0, 1);
	  gr = CreateAdjacent(gr, 0, 4);

	  gr = CreateAdjacent(gr, 1, 0);
	  gr = CreateAdjacent(gr, 1, 2);
	  gr = CreateAdjacent(gr, 1, 3);
	  gr = CreateAdjacent(gr, 1, 4);

	  gr = CreateAdjacent(gr, 2, 1);
	  gr = CreateAdjacent(gr, 2, 3);

	  gr = CreateAdjacent(gr, 3, 1);
	  gr = CreateAdjacent(gr, 3, 2);
	  gr = CreateAdjacent(gr, 3, 4);

	  gr = CreateAdjacent(gr, 4, 0);
	  gr = CreateAdjacent(gr, 4, 1);
	  gr = CreateAdjacent(gr, 4, 3);

	  ListGraph(gr);

#pragma endregion

	  system("pause");
	  return 0;
} 
