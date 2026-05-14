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
#include <malloc.h>
// Lidar com "exceções"
// assert(x>=10) - stderror output caso x<10

//Ver: http://www.geeksforgeeks.org/graph-and-its-representations/
//Exercicio: 
//Analisar http://www.thecrazyprogrammer.com/2014/03/depth-first-search-dfs-traversal-of-a-graph.html

#pragma warning( disable : 4996 ) //evita MSG ERROS: _CRT_SECURE_NO_WARNINGS

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
struct AdjListNode* newAdjListNode(int dest)
{
	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	//assert(newNode);		//lida com invariante ex: assert(x>10) - stderror output
	if (!newNode) return NULL;
	newNode->idVertice = dest;
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
	for (i = 0; i < nVertices; ++i) {
		graph->array[i].head = NULL;
		graph->array[i].idVertice = i;
	}

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
	if (graph == NULL || src>TOTALVERTICES || dest>TOTALVERTICES) return false; 	//tratar restantes validações
	
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
Apenas percorre a menor distância saindo de um determinado verticce
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
 *  Destoy Adjacent
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
	strcpy(aux->city, name);
	aux->id= identifier;
	aux->ptAdjacent = NULL;
	aux->ptNext = NULL;
	return aux;
}

bool NodeDestroy(Node *ptNode) {
	if (!ptNode) return false;
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
		printf("%d-", current->id);
		printf("%s\n", current->city);
		Adjacent *currentAdjacent = current->ptAdjacent;
		while (currentAdjacent != NULL)
		{
			printf("\t");
			printf("adjacent-%d\n", currentAdjacent->ptDestiny->id);
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
		if (current->id == origin)
			originNode = current;
		if (current->id == destiny)
			destinyNode = current;
		current = current->ptNext;
	}
	//Não existem?
	if (originNode == NULL || destinyNode == NULL)
	{		return graph;
	}

	//Cria nova adjacencia
	Adjacent* inserted = AdjacentCreate(destinyNode);
	if (inserted == NULL) return graph;
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

#pragma region PATH_GRAFO_PESADO

/*!
 *  Adds the edge weight.
 *
 *      @param [in,out] graph 
 *      @param [in]     src   
 *      @param [in]     dest  
 *      @param [in]     p     
 *
 *      @return 
 */
bool addEdgeWeightII(Graph* graph, int src, int dest, float p) {
	// 1. Validação de segurança (evita Heap Corruption)
	if (graph == NULL || src < 0 || src >= graph->totVertices ||
		dest < 0 || dest >= graph->totVertices) {
		return false;
	}

	// 2. Criar aresta da Origem para o Destino (src -> dest)
	AdjListNode* newNode = newAdjListNode(dest);
	if (newNode == NULL) return false;

	newNode->peso = p;
	// Insere à cabeça da lista de adjacências do vértice 'src'
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	// 3. Criar aresta do Destino para a Origem (dest -> src)
	// Obrigatório por ser um grafo NÃO ORIENTADO
	newNode = newAdjListNode(src);
	if (newNode == NULL) return false;

	newNode->peso = p;
	// Insere à cabeça da lista de adjacências do vértice 'dest'
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;

	return true;
}


/*
* Dijkstra
Encontra e imprime o caminho mais curto entre origem e destino
*/
bool ShortestPath(Graph* graph, int startNode, int endNode) {
	if (!graph || startNode < 0 || startNode >= graph->totVertices ||
		endNode < 0 || endNode >= graph->totVertices) return false;

	float dist[TOTALVERTICES];
	int prev[TOTALVERTICES];
	bool visited[TOTALVERTICES];
	//ou
	// 	int n = graph->totVertices;
	// Alocação dinâmica dos arrays auxiliares
	//float* dist = (float*)malloc(n * sizeof(float));
	//int* prev = (int*)malloc(n * sizeof(int));
	//bool* visited = (bool*)malloc(n * sizeof(bool));

	int n = TOTALVERTICES;
	// 1. Inicialização
	for (int i = 0; i < n; i++) {
		dist[i] = (float)INT_MAX; // "Infinito"
		prev[i] = -1;             // Sem predecessor
		visited[i] = false;
	}

	dist[startNode] = 0;

	for (int count = 0; count < n - 1; count++) {
		// 2. Encontrar o vértice com a menor distância ainda não visitado
		float min = (float)INT_MAX;
		int u = -1;

		for (int v = 0; v < n; v++) {
			if (!visited[v] && dist[v] <= min) {
				min = dist[v];
				u = v;
			}
		}

		if (u == -1 || u == endNode) break; // Se não há mais alcance ou chegámos ao destino

		visited[u] = true;

		// 3. Atualizar distâncias dos vizinhos de u
		AdjListNode* aux = graph->array[u].head;
		while (aux != NULL) {
			int v = aux->idVertice;
			if (!visited[v] && dist[u] != INT_MAX && (dist[u] + aux->peso < dist[v])) {
				dist[v] = dist[u] + aux->peso;
				prev[v] = u;
			}
			aux = aux->next;
		}
	}

	// 4. Exibir o resultado
	if (dist[endNode] == INT_MAX) {
		printf("Não existe caminho entre %d e %d\n", startNode, endNode);
		return false;
	}

	printf("Menor custo de %d para %d: %.2f\n", startNode, endNode, dist[endNode]);
	printf("Caminho: ");
	printPathRecursive(prev, endNode);
	printf("\n");

	return true;
}

// Algoritmo de Dijkstra com reconstrução de lista segura 
NodoCaminho* GetShortestPath(Graph* graph, int startNode, int endNode) {
	int n = graph->totVertices;
	float* dist = (float*)malloc(n * sizeof(float));
	int* prev = (int*)malloc(n * sizeof(int));
	bool* visited = (bool*)malloc(n * sizeof(bool));

	// Inicialização: distâncias a "infinito" e precedentes a -1
	for (int i = 0; i < n; i++) {
		dist[i] = 1000000.0f;
		prev[i] = -1;
		visited[i] = false;
	}

	dist[startNode] = 0.0f;

	for (int count = 0; count < n - 1; count++) {
		float min = 1000000.0f;	//necessário para o Dijkstra
		int u = -1;

		for (int i = 0; i < n; i++) {
			if (!visited[i] && dist[i] < min) {
				min = dist[i];
				u = i;
			}
		}

		if (u == -1 || u == endNode) break;
		visited[u] = true;

		AdjListNode* aux = graph->array[u].head;
		while (aux) {
			if (!visited[aux->idVertice] && dist[u] + aux->peso < dist[aux->idVertice]) {
				dist[aux->idVertice] = dist[u] + aux->peso;
				prev[aux->idVertice] = u;
			}
			aux = aux->next;
		}
	}

	// RECONSTRUÇÃO: Inserção à cabeça garante que o destino aponta para NULL
	NodoCaminho* listaResult = NULL;
	if (prev[endNode] != -1 || startNode == endNode) {
		int atual = endNode;
		while (atual != -1) {
			NodoCaminho* novo = (NodoCaminho*)malloc(sizeof(NodoCaminho));
			novo->idVertice = atual;
			novo->prox = listaResult; // Na 1ª vez, listaResult é NULL
			listaResult = novo;
			atual = prev[atual];
		}
	}

	free(dist); free(prev); free(visited);
	return listaResult;
}

// Função auxiliar para imprimir o caminho de forma recursiva
void printPathRecursive(int prev[], int j) {
	if (prev[j] == -1) {
		printf("%d", j);
		return;
	}
	printPathRecursive(prev, prev[j]);
	printf(" -> %d", j);
}

void MostrarCaminho(NodoCaminho* caminho) {
	if (caminho == NULL) {
		printf("\nCaminho nao encontrado ou inexistente.\n");
		return;
	}

	printf("\nTrajeto encontrado: ");
	NodoCaminho* aux = caminho;
	while (aux != NULL) {
		printf("%d", aux->idVertice);
		if (aux->prox != NULL) printf(" -> ");
		aux = aux->prox;
	}
	printf("\n");
}

void LibertarCaminho(NodoCaminho* caminho) {
	NodoCaminho* temp;
	while (caminho != NULL) {
		temp = caminho;
		caminho = caminho->prox;
		free(temp);
	}
}

bool existeCaminho(Graph* g, int origem, int destino) {
	NodoCaminho* caminho = GetShortestPath(g, origem, destino);
	if (caminho != NULL) {
		LibertarCaminho(caminho); // Importante limpar a memória!
		return true;
	}
	MostrarCaminho(caminho);
	return false;
}

void destroyGraph(Graph* g) {
	if (!g) return;
	for (int i = 0; i < g->totVertices; i++) {
		AdjListNode* aux = g->array[i].head;
		while (aux) {
			AdjListNode* temp = aux;
			aux = aux->next;
			free(temp); // Liberta cada aresta
		}
	}
	free(g->array); // Liberta o array de vértices
	free(g);        // Liberta a estrutura do grafo
}

bool SaveGraphToCSV(Graph* g, char* filename) {
	if (!g) return;
	FILE* fp = fopen(filename, "w");
	if (!fp) return false;

	// A primeira linha contém apenas o número de vértices
	fprintf(fp, "%d\n", g->totVertices);

	for (int i = 0; i < g->totVertices; i++) {
		AdjListNode* aux = g->array[i].head;
		while (aux) {
			// As linhas seguintes contêm a estrutura: origem;destino;peso
			fprintf(fp, "%d;%d;%.2f\n", i, aux->idVertice, aux->peso);
			aux = aux->next;
		}
	}
	fclose(fp);
	return true;
}

#include <string.h>

/**
 * Carrega um grafo a partir de um ficheiro CSV.
 * O ficheiro deve estar no formato: origem;destino;peso
 */
Graph* LoadGraphFromCSV(char* filename) {
	FILE* fp = fopen(filename, "r");
	if (!fp) return NULL;

	int nVertices = 0;
	// 1. Ler o número de vértices (primeira linha)
	// Lê caracteres até encontrar o fim da linha
	int c;
	while ((c = fgetc(fp)) != EOF && c != '\n') {
		if (c >= '0' && c <= '9') {
			nVertices = nVertices * 10 + (c - '0');
		}
	}

	if (nVertices <= 0) {
		fclose(fp);
		return NULL;
	}

	Graph* g = createGraph(nVertices);
	if (!g) {
		fclose(fp);
		return NULL;
	}

	// 2. Ler as arestas (origem;destino;peso)
	while (true) {
		int v_origem = 0, v_destino = 0;
		float v_peso = 0.0, decimal = 0.1;
		bool emDecimal = false;

		// Ler Origem (até ao ;)
		while ((c = fgetc(fp)) != EOF && c != ';') {
			if (c >= '0' && c <= '9') v_origem = v_origem * 10 + (c - '0');
		}
		if (c == EOF) break;

		// Ler Destino (até ao ;)
		while ((c = fgetc(fp)) != EOF && c != ';') {
			if (c >= '0' && c <= '9') v_destino = v_destino * 10 + (c - '0');
		}

		// Ler Peso (até ao \n ou EOF)
		while ((c = fgetc(fp)) != EOF && c != '\n') {
			if (c >= '0' && c <= '9') {
				if (!emDecimal) v_peso = v_peso * 10 + (c - '0');
				else { v_peso += (c - '0') * decimal; decimal /= 10; }
			}
			else if (c == '.' || c == ',') {
				emDecimal = true;
			}
		}

		// 3. Adicionar aresta ao grafo
		if (v_origem < nVertices && v_destino < nVertices) {
			addEdgeWeightII(g, v_origem, v_destino, v_peso);
		}

		if (c == EOF) break;
	}

	fclose(fp);
	return g;
}

#pragma endregion

