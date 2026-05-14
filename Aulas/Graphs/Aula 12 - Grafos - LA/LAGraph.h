/*
//Grafos: Lista de Adjacências
//
// Procura em Profundidade: Stack
// Procura em Largura:		Queue
//lufer
*/
//#pragma once
//ou
#ifndef GRF
#define GRF



//=========================================================
//H1 : grafo orientado, não pesado (pouco eficiente): porquê?
//=========================================================
#define TOTALVERTICES 8

//Vertice
typedef struct Vertice {
	int valor;				//número de adjacentes ou valor do vertice
	struct Vertice* prox;	//lista de adjacentes
}Vertice;

bool CriaGraph(Vertice *gr, int tot);
void MostraGrafo(Vertice *lista);
bool InsereAresta(Vertice *lista, int a, int b);


//=========================================================
//H2 - Grafo orientado e pesado (mais eficiente): porquê?
//=========================================================

// nodo da Lista de Adjacências
typedef struct AdjListNode
{
	int idVertice;
	float peso;			//grafo pesado
	struct AdjListNode* next;
}AdjListNode;

// Inf de Certice
typedef struct VerticeII
{
	int idVertice;
	//outros dados do vertice
	AdjListNode *head;  // head da Lista de adjacencias
}VerticeII;

// Um Grafo:
//	Um array de Lista de Adjacências!!!
//		Array = numero de vértices do Grafo
//	Uma lista de Listas de Adjacencias

typedef struct Graph
{
	int totVertices;	//total de vertices
	VerticeII* array;	//ou struct AdjList array[N]
}Graph;

//prototipos funções

Graph* createGraph(int nVertices);
AdjListNode* newAdjListNode(int val);
//Insere em grafo não orientado e pesado
bool addEdgeWeight(Graph* graph, int src, int dest, float p);
//insere em grafo não orientado e não pesado
bool addEdge(Graph* graph, int src, int dest);
//Menor Distância
float ShorterDistance(Graph* graph, int v);
bool printGraph(Graph* graph);
bool printGraphWeight(Graph* graph, bool pesado);


//=========================================================
//H3
//Só estruturas dinâmicas
////=========================================================

typedef struct Node Node;
typedef struct Adjacent Adjacent;

/*!
 *  Adjacências
 */
struct Adjacent {
	Node *ptDestiny;
	Adjacent *ptNext;
};

/*!
 *  Vertices
 */
struct Node
{
	int *ptIdentifier;	//simplificar para int
	char *ptCity;		//simplifcar para char[]
	Adjacent *ptAdjacent;
	Node *ptNext;
};

typedef struct GraphIII
{
	int totalVertices;
	int totalEdges;

	Node* nodes;
}GraphIII;

Adjacent *AdjacentCreate(Node *destiny);
bool AdjacentDestroy(Adjacent* ptAdjacent);
bool ListGraph(Node *graph);
Node* CreateGraphTable(Node* graph, int position, char cityName[]);
Node* CreateAdjacent(Node* graph, int origin, int destiny);
#endif // !GRF

