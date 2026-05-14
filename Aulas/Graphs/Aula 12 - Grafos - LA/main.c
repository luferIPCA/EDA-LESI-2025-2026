/*
Grafos: Fundamentos
lufer
Consultar:
https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/
*/
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 ) //evita MSG ERROS: _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>	// ASCII SET
#include "LAGraph.h"

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

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
	  
	  int v = TOTALVERTICES;	//cuidado com o número total
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


	  ////======================================
	  ////H3: tudo dinâmico
	  ////======================================
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
	  free(gr);

#pragma endregion

#pragma region PATH

	  // 1. Criar um grafo com 6 vértices (ex: 0 a 5)
	  int numVertices = TOTALVERTICES;
	  g = createGraph(numVertices);
	  if (!g) return 1;

	  // 2. Adicionar arestas ponderadas (Simulação de um mapa de cidades/pontos)
	  // Exemplo: 0-1 (peso 4), 0-2 (peso 2), 1-2 (peso 5), 1-3 (peso 10), 2-4 (peso 3), 4-3 (peso 4), 3-5 (peso 11)
	  addEdgeWeightII(g, 0, 1, 4.0);
	  addEdgeWeightII(g, 0, 2, 2.0);
	  addEdgeWeightII(g, 1, 2, 5.0);
	  addEdgeWeightII(g, 1, 3, 10.0);
	  addEdgeWeightII(g, 2, 4, 3.0);
	  addEdgeWeightII(g, 4, 3, 4.0);
	  addEdgeWeightII(g, 3, 5, 1.0);

	  printf("--- Sistema de Gestao de Rotas ---\n");
	  printGraphWeight(g, true);

	  // 3. Definir Origem e Destino
	  int origem = 0;
	  int destino = 3;

	  printf("\nA calcular a melhor rota de %d para %d...\n", origem, destino);

	  // 4. Obter o caminho mais curto (Lógica separada da apresentação)
	  NodoCaminho* caminhoEncontrado = GetShortestPath(g, origem, destino);

	  // 5. Mostrar o caminho usando o método de visualização
	  if (caminhoEncontrado != NULL) {
		  printf("Sucesso! Caminho mais curto encontrado:\n");
		  MostrarCaminho(caminhoEncontrado);

		  // Se quisesses o custo total, poderias passar a distância de outra forma, 
		  // ou calcular percorrendo a lista e consultando o grafo.
	  }
	  else {
		  printf("Erro: Nao existe ligacao entre os pontos selecionados.\n");
	  }

	  // 6. LIMPEZA DE MEMÓRIA (Fundamental)
	  if (caminhoEncontrado) {
		  LibertarCaminho(caminhoEncontrado);
		  printf("\nMemoria do caminho libertada.");
	  }

	  // Faltaria aqui uma função para libertar o grafo g (free de todas as listas e do array)
	  printf("\nPrograma terminado.\n");

#pragma endregion

	  destroyGraph(g);
	  return 0;
} 
