/*****************************************************************//**
 * @file   btree.h
 * @brief  Árvores Binárias de Procura - (Binary Search Tree )
 * 
 * @author  lufer
 * @email	lufer@ipca.pt
 * @date    April 2026
 *********************************************************************/
/*
Ver:
https://www.geeksforgeeks.org/binary-tree-set-1-introduction/?ref=lbp
*/

#ifndef BTREE
#define BTREE

#define N 50
#define Max(x,y)  ((x>y)? (x) : (y))

#include <stdbool.h>
//or
// typedef   enum Boolean { false, true }   Boolean;

/**
 * Valor do nodo de uma árvore - Element
 */
typedef struct Element {
	int val;
	char nome[N];
}Element;

//typedef struct Element Element;


//H1: Nodo da árvore
typedef struct Node {
	Element element;			//struct	
	struct Node *leftTree;
	struct Node *rightTree;
}Node, *PtrNode;

//typedef Node *PtrNode;

#pragma region ARVORE_INFO_DESACOPOLADA

//===========================================================
//H2: Nodo da árvore generalizado - informação desacoplada!
typedef struct NodeII {
	Element *element;			//apontador para struct
	struct NodeII *leftTree;
	struct NodeII *rightTree;
}NodeII;

typedef NodeII *PtrNodeII;
//===========================================================

#pragma endregion

//================= Assinatura de métodos ===================

//Inicializa uma àrvore
Node* InitTree();

//Cria novo nodo de uma árvore binária
PtrNode NewNode(Element e);

//Destroi um nodo de uma árvore
void DestroyNode(Node **p);
//ou
// Node* DestroyNoe(Node* p);

//Calcula o Número de Nodos de uma Árvore
int TreeSize(PtrNode r);

//Calcula a Altura de uma Árvore
int TreeHeight(PtrNode r);


// =========== Operações de procura ============

PtrNode FindNode(Element e, PtrNode root);

bool ExistNode(Element e, PtrNode root);

PtrNode GetMax(PtrNode root);

PtrNode GetMin(PtrNode root);


// =========== Operações de Manipulação ============

Node *AddNode(Node *root, Element e);
//PtrNode AddNodeII(PtrNode root, Node e);
PtrNode DeleteNode(PtrNode root, Element e);
PtrNode DeleteCurrentNode(PtrNode root);
PtrNode FindMin(PtrNode root);

void PreOrder(PtrNode root);
void PosOrder(PtrNode root);
void InOrder(PtrNode root);

void Show(PtrNode root, int nivel);
void ShowII(char *s);

// =========== Balanceamento ============

PtrNode Balance(PtrNode root);
PtrNode BSTBalance(PtrNode root,Node *list, int ini, int end);
void BST2List(PtrNode root, int *tot, Node *list);
bool AddNodeIII(Node** root, Element e);

// =========== COnstruir BTS Balanceada ========

typedef struct NodeBal {
	Element element;
	struct NodeBal* leftTree;
	struct NodeBal* rightTree;
	int height;
} NodeBal, *PtrNodeBal;

int height(PtrNodeBal n);

//int max(int a, int b) {
//	return (a > b) ? a : b;
//}

int getBalance(PtrNodeBal n);
PtrNodeBal rotateRight(PtrNodeBal y);
PtrNodeBal rotateLeft(PtrNodeBal x);
PtrNodeBal insertAVL(PtrNodeBal node, Element e);
void DebugPrint(Node* r);

//Folha de Exercicios 10
struct Exp {
	char oper;		//operador: '+', '-', '*', '/'
	float val;		//valor do operando
	struct Exp *esq, *dir;
};

typedef struct Exp Exp;

Exp* Parse(char v[], int i);

#endif