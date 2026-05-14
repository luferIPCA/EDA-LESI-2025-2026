/*
Grafos Não Orientados | Orientados

Procura em Profundidade: Stack
Procura em Largura:		Queue
lufer

Ver http://www.tutorialspoint.com/data_structures_algorithms/depth_first_traversal_in_c.htm
*/

#include <stdio.h>
#include <stdbool.h>
#include "Graphs.h"

// =====================================================
//Depth First Algorithm : STACK
// =====================================================

#ifndef DFS
#define DFS

int stack[MAX];  
int top;  

//assinaturas
//Stack
void push(int item);
int pop();
int peek();
bool isStackEmpty();
//graph
int DepthFirstSearch(int adjMatrix[][MAX], Vertice setVertices[], int totV, char alvo);

void DFSTraversal(int adjMatrix[][MAX], Vertice setVertices[], int t); 

#endif // !DFS