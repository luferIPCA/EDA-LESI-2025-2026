/*
//Grafos: Lista de Adjacências
//
// Procura em Profundidade: Stack
// Procura em Largura:		Queue
//lufer
*/
#include <stdio.h>
#include <stdbool.h>
#include "LAGraph.h"
#include "assert.h"
#include <stdlib.h>
// Lidar com "exceções"
// assert(x>=10) - stderror output caso x<10

//Ver: http://www.geeksforgeeks.org/graph-and-its-representations/
//Exercicio: 
//Analisar http://www.thecrazyprogrammer.com/2014/03/depth-first-search-dfs-traversal-of-a-graph.html

#pragma region GRAFO_NAO_ORIENTADO_I

//=========================================================
//H1 - Grafo orientado, não pesado, matriz fixa (TOTALVERTICES)
//=========================================================


/*
Cria Grafo
Vertices: 0, 1, 2, 3...
Inicializa vertices com lista de adjacencias=NULL
*/
bool CriaGraph(Vertice *gr, int tot) {
	//se número de vertices não for válido
	if (tot <= 0 || tot > TOTALVERTICES || gr==NULL) return false;
	//incializa
	for (int i = 0; i < tot; i++) {
		gr[i].valor = 0;
		gr[i].prox = NULL;
	}
	return true;
}
/*
Mostra Grafo
*/
void MostraGrafo(Vertice *lista) {
	int i;
	Vertice* tmp;
	for (i = 0; i < TOTALVERTICES; i++) {
		tmp = lista[i].prox;
		printf("Vertice %d: (%d) ==>", i, lista[i].valor);
		while (tmp != NULL) {
			printf("%d  ", tmp->valor);
			tmp = tmp->prox;
		}
		printf("\n");
	}
}

/*
Nova aresta, ordenando adjacências, grafo orientado
Vertice origem:a
Vertice destino:b
*/
bool InsereAresta(Vertice *lista, int a, int b) {

	if (lista == NULL || a<0 || b<0 || a>TOTALVERTICES || b>TOTALVERTICES) return false;
	Vertice *destino;
	Vertice *tmp;

	//Novo vertice para o destino
	destino = (Vertice*)malloc((int)sizeof(Vertice));
	//assert(destino);
	if (!destino) return false;
	destino->valor = b;
	destino->prox = NULL;

	//Regista vertice destino como adjacente
	if (lista[a].prox == NULL)	// se lista vazia - é único adjacente	
		lista[a].prox = destino;
	else {						//insere vértices ordenados
		tmp = lista[a].prox;
		//insere inicio da lista
		if (tmp->valor > b) {	//insere inicio da lista
			destino->prox = tmp;
			lista[a].prox = destino;
		} 		          
		else if (tmp->prox == NULL) {
			destino->prox = tmp->prox;
			tmp->prox = destino;
		}
		else {
			while ((tmp->prox != NULL) && (tmp->prox->valor < b))
				tmp = tmp->prox;
			destino->prox = tmp->prox;
			tmp->prox = destino;
		}
		lista[a].valor++;			// conta adjacentes!
	}
	return true;
}

#pragma endregion

#pragma region GRAFO_NAO_ORIENTADO_II

//=========================================================
//H2 - Grafo Não Orientado, pesado, Matriz calculada
//=========================================================

/*
Novo Nodo
*/
struct AdjListNode* newAdjListNode(int val)
{
	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	//assert(newNode);		//lida com invariante ex: assert(x>10) - stderror output
	if (!newNode) return NULL;
	newNode->idVertice = val;
	newNode->next = NULL;
	newNode->peso = 0;		//grafo ponderado; (peso=0) por omissão!
	return newNode;
}

/*
Cria grafo preparado para conter "nVertices" 
*/
Graph* createGraph(int nVertices)
{
	//estrutura para guardar info do grafo
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	//assert(graph);
	if (graph == NULL) return NULL;
	graph->totVertices = nVertices;

	//Cria array de lista de adjacencias de tamanho nVertices
	graph->array = ( VerticeII*) malloc(nVertices * sizeof(VerticeII));
	if (graph->array == NULL) return NULL;
	//ou
	// assert(graph->array);

	// Inicializa cada lista de adjacencias
	int i;
	for (i = 0; i < nVertices; ++i)
		graph->array[i].head = NULL;

	return graph;
}

/*
Adicona aresta em grafo não orientado e não pesado
*/
bool addEdge(Graph* graph, int src, int dest)
{
	if (!graph) return false;//ver restantes validações
	
	//novo nodo para vertice destino
	AdjListNode* newNode = newAdjListNode(dest);
	//Insere à cabeça da lista de adjacências
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// grafo não orientado => addEdgs (graph, dest,src) 
	newNode = newAdjListNode(src);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
	return true;
}


/*
Insere aresta ponderada, ie, com um peso, em grafo não orientado
*/
bool addEdgeWeight(struct Graph* graph, int src, int dest, float p)
{
	if (graph == NULL ) return false; 	//tratar restantes validações
	
	//novo nodo para vertice destino
	struct AdjListNode* vdest = newAdjListNode(dest);	
	vdest->peso = p;		//ponderação

	//Insere à cabeça da lista de adjacências
	vdest->next = graph->array[src].head;
	graph->array[src].head = vdest;

	// grafo não orientado => addEdgs (graph, dest,src) 
	struct AdjListNode* vsource = newAdjListNode(src);
	vsource->peso = p;		//ponderação
	vsource->next = graph->array[dest].head;
	graph->array[dest].head = vsource;
}

//Outra Abordagem
/*
bool addEdgeII(Graph* graph, int src, int dest, float p)
{
	//novo nodo para vertice destino
	struct AdjListNode* newNode = newAdjListNode(dest);
	//Insere à cabeça da lista de adjacências
	newNode->next = graph->array[src].head;
	newNode->peso = p;
	graph->array[src].head = newNode;

	addEdgeII(graph, dest, src, p);

}

bool addEdgeWeightII(Graph* graph, int src, int dest, float p)
{
	addEdgeII(graph, src, dest, p);
	addEdgeII(graph, dest, src, p);
}
*/

/*
Mostra Grafo
*/
bool printGraph(struct Graph* graph)
{
	if (!graph) return false;
	int v;
	for (v = 0; v < graph->totVertices; ++v)
	{
		struct AdjListNode* aux = graph->array[v].head;
		printf("\n Lista de Adjacencia do Vertice (%d)", v);
		while (aux)
		{
			printf("-> %d", aux->idVertice);
			aux = aux->next;
		}
		printf("\n");
	}
	return true;
}

/*
Mostra grafo pesado ou não
*/
bool printGraphWeight(Graph* graph, bool pesado)
{
	if (!graph) return false;
	int v;
	for (v = 0; v < graph->totVertices; ++v)
	{
		AdjListNode* aux = graph->array[v].head;
		printf("\n Lista de Adjacencia do Vertice (%d)", v);
		while (aux)
		{
			if(pesado==false)
				printf("-> %d", aux->idVertice);
			else
				printf("-> (%d): Peso= %2.0f", aux->idVertice, aux->peso);
			
			aux = aux->next;
		}
		printf("\n");
	}
	return true;
}

/*
Menor distância saindo de um determinado verticce
*/
float ShorterDistance(Graph* graph, int v) {
	if (!graph) return 0;
	//assert (v existe e é válido)
	
	AdjListNode* aux = graph->array[v].head;
	if (!aux) return 0;		//não existe adjacentes
	float menor = aux->peso;//menor é o primeiro
	aux = aux->next;
	while (aux)
	{
		if ((aux->peso > menor) && (aux->peso != 0))
			menor = aux->peso;
		aux = aux->next;
	}
	return menor;
}

#pragma endregion

#pragma region GRAFO_NAO_ORIENTADO_III

//=========================================================
//H3 - Estruturas Dinâmicas
//=========================================================

Adjacent *AdjacentCreate(Node *destiny)
{
	Adjacent *adjacent;

	adjacent = (Adjacent*)malloc(sizeof(Adjacent));
	if (adjacent == NULL)
	{
		return NULL;
	}

	adjacent->ptDestiny = destiny;
	adjacent->ptNext = NULL;

	return adjacent;
}

/*!
 *  Destoy Adjacents
 *
 *      @param [in,out] ptAdjacent 
 *
 *      @return 
 */
bool AdjacentDestroy(Adjacent *ptAdjacent)
{
	if (!ptAdjacent) return false;
	if(ptAdjacent) free(ptAdjacent);
	return true;
}

Node *NodeCreate(int identifier, char name[])
{
	Node *aux;

	aux = (Node*)malloc(sizeof(Node));
	if (aux == NULL)
	{
		return NULL;
	}
	//espaço para um int
	if ((aux->ptAdjacent = (int *)malloc(sizeof(int))) == NULL)
	{
		free(aux);
		return NULL;
	}
	//epaço para a cidade
	if ((aux->ptCity = (char *)malloc(strlen(name) + 1)) == NULL) {
		free(aux->ptCity);
		free(aux);
		return NULL;
	}

	aux->ptIdentifier= identifier;
	strcpy(aux->ptCity, name);
	aux->ptAdjacent = NULL;
	aux->ptNext = NULL;
	return aux;
}

bool NodeDestroy(Node *ptNode) {
	if (!ptNode) return false;
	free(ptNode->ptIdentifier);
	free(ptNode->ptCity);
	free(ptNode);
	return true;
}

/*!
 *  Creates the graph table.
 *
 *      @param [in,out] graph    
 *      @param [in]     position 
 *      @param [in]     cityName 
 *
 *      @return 
 */
Node* CreateGraphTable(Node* graph,int position,char cityName[])
{
	Node* previous = NULL;
	Node* current = graph;

	Node* inserted = NodeCreate(position, cityName);

	if (inserted == NULL)
		return graph;

	//avança até ao fim dos vertices...podia ordenar!
	while (current != NULL)
	{
		previous = current;
		current = current->ptNext;
	}
	//grafo vazio
	if (previous == NULL)
	{
		inserted->ptNext = graph;
		graph = inserted;
	}
	else //insere no fim
	{
		previous->ptNext = inserted;
	}

	return graph;
}

bool ListGraph(Node *graph) {
	if (!graph) return false;
	Node *current = graph;
	while (current != NULL) {
		printf("%d-", *current->ptIdentifier);
		printf("%s\n", current->ptCity);
		Adjacent *currentAdjacent = current->ptAdjacent;
		while (currentAdjacent != NULL)
		{
			printf("\t");
			printf("adjacent-%d\n", *currentAdjacent->ptDestiny->ptIdentifier);
			currentAdjacent = currentAdjacent->ptNext;
		}
		current = current->ptNext;
	}
}

Node* CreateAdjacent(Node* graph,int origin,int destiny)
{
	Node* originNode = NULL;
	Node* destinyNode = NULL;

	Node* current = graph;

	//encontrar
	while (current != NULL)
	{
		if (*current->ptIdentifier == origin)
			originNode = current;

		if (*current->ptIdentifier == destiny)
			destinyNode = current;

		current = current->ptNext;
	}

	//Não existem?
	if (originNode == NULL || destinyNode == NULL)
	{
		return graph;
	}

	//Cria nova adjacencia
	Adjacent* inserted = AdjacentCreate(destinyNode);

	if (inserted == NULL)
		return graph;

	Adjacent* currentAdjacent = originNode->ptAdjacent;

	if (currentAdjacent == NULL)
	{
		originNode->ptAdjacent = inserted;
	}
	else
	{
		while (currentAdjacent->ptNext != NULL)
		{
			currentAdjacent =
				currentAdjacent->ptNext;
		}

		currentAdjacent->ptNext = inserted;
	}

	return graph;
}

#pragma endregion