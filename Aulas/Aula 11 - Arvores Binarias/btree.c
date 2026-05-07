/*****************************************************************//**
 * \file   btree.c
 * \brief  Implementação de Árvores Binárias de Procura
 * 
 * \author lufer
 * \date   April 2026
 * Ver:
https://www.geeksforgeeks.org/binary-tree-set-1-introduction/?ref=lbp
 *********************************************************************/

#include <stdio.h>
#include "btree.h"
//#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Inicia uma Árvore Binária de Procura
 * 
 * @return 
 */
Node* InitTree() {
	//Várias coisas
	return NULL;
}

/**
 * .
 * 
 * @param e
 * @return 
 */

Node* NewNode(Element e) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) return NULL;	//problemas ao criar espaço em memória	
	node->element = e;
	node->leftTree = NULL;
	node->rightTree = NULL;
	return node;
}


/*
Cria Nodo de uma Árvore Generalizada - Informação desacoplada!
H2
*/
NodeII *NewNodeGeneral(Element e) {
	NodeII *node = (NodeII*)malloc(sizeof(NodeII));
	if (node == NULL) return NULL;	//problemas ao criar espaço em memória
	/*if (node->element = (Element *)malloc(sizeof(Element)) == NULL) {
		free(node);
		return NULL;
	}*/	
	*node->element = e;
	node->leftTree = NULL;
	node->rightTree = NULL;
	return node;
}

/*
Calcula o Número de Nodos de uma Árvore
*/
int TreeSize(Node *r) {

	if (r == NULL) return 0;
	else
		return (1 + TreeSize(r->leftTree) + TreeSize(r->rightTree));
}

/*
Calcula a Altura de uma Árvore
*/
int TreeHeight(Node *root) {
	unsigned int leftHeight, rightHeight;
	if (root == NULL) return 0;
	else
	{
		leftHeight = TreeHeight(root->leftTree);
		rightHeight = TreeHeight(root->rightTree);
		return (Max(leftHeight, rightHeight) + 1);
		//ou
		//return (1+Max(TreeHeight(root->leftTree), TreeHeight(root->rightTree)));		
	}

}


// =========== Operações de procura ============

/*
Procura um elemento num árvore!
*/
Node *FindNode(Element e, Node *root) {
	if (root == NULL) return NULL;
	if (root->element.val == e.val) return root;
	else
	{
		if (root->element.val > e.val) return (FindNode(e, root->leftTree));
		else return (FindNode(e, root->rightTree));
	}
}


/*
Verifica se determinado elemento existe: IMPLEMENTAR
*/
bool ExistNode(Element e, Node *root){}

/*
Determina o maior elemento da árvore
*/
Node *GetMax(Node *root) {
	if (root == NULL) return NULL;
	if (root->rightTree == NULL)  
		return root;
	else
		return GetMax(root->rightTree);
}


/*
Determina o menor elemento da árvore: IMPLEMENTAR
*/
PtrNode GetMin(PtrNode root){
	if (!root) return NULL;
	if (root->leftTree == NULL)
		return root;
	else
		return GetMin(root->leftTree);
}

// =========== Operações de Manipulação ============

/*
Divide e Conquista Algoritmo
*/
void DoSomethingToAllNodes(struct Node *root) 
{
	if (root) {
		//DoSomeThingTo(root);
		DoSomethingToAllNodes(root->leftTree);
		DoSomethingToAllNodes(root->rightTree);
	}
}

/**
 * @brief Insere Nodo da Árvore.
 * Note: Parcially violates SOLID --> Correct
 * @param root
 * @param e
 * @return 
 */
Node* AddNode(Node* root, Element e) {
	if (root == NULL)		//arvore vazia
	{
		root = NewNode(e);		
	}
	else
	{
		if (root->element.val > e.val) {		//Insere à esquerda
			root->leftTree = AddNode(root->leftTree, e);
		}
		else
			if (root->element.val < e.val)		//Insere à direita
				root->rightTree = AddNode(root->rightTree, e);
		// duplicados são ignorados
	}
	return root;
}


/**
 * @brief Insere Nodo da Árvore.
 * Respect SOLID
 * @param root
 * @param e
 * @return
 */
Node* AddNodeII(Node* root, Node* novo) {

	if (root == NULL)
		return novo;

	if (novo->element.val < root->element.val) {
		root->leftTree = AddNodeII(root->leftTree, novo);
	}
	else {
		root->rightTree = AddNodeII(root->rightTree, novo);
	}

	return root;
}

//H3: como controlar?
//PtrNode AddNodeIII(PtrNode *root, Element e) {
bool AddNodeIII(Node **root, Element e) {
	if (*root == NULL) {
		*root = NewNode(e);
		return true;
	}
	if ((*root)->element.val == e.val) {
		return false; // ignorar repetidos
	}
	if ((*root)->element.val > e.val) {
		return AddNodeIII(&(*root)->leftTree, e);
	}
	else
		return AddNodeIII(&(*root)->rightTree, e);
}

/*
Remove Nodo da Árvore
1º Procurar
2º Apagar se encontrado
*/
PtrNode DeleteNode(PtrNode root, Element e) {
	//árvore vazia ou enexistente
	if (root == NULL) return NULL;	

	if (root->element.val > e.val)
		root->leftTree = DeleteNode(root->leftTree, e);
	else
		if (root->element.val < e.val) {
			root->rightTree = DeleteNode(root->rightTree, e);
		}
		else    //(root->element.val == e.val) 
		{
			root = DeleteCurrentNode(root);
		}
	return root;

	//h2
	//root = FindNode(e, root);
	//root = DeleteCurrentNode(root);
	//return root;

	//h3
	//return (DeleteCurrentNode(FindNode(e, root)));

}

/*
Apaga Nodo. Refaz árvore
*/
PtrNode DeleteCurrentNode(PtrNode root) {
	PtrNode aux;
	if (root == NULL) return NULL;	//Nada para apagar!

	if (root->leftTree == NULL && root->rightTree == NULL) {	//único nodo
		DestroyNode(&root);
		return NULL;
	}
	else 
		if (root->leftTree==NULL){		//só tem sub-arvore direita...ligar à direita
			aux = root;
			root = root->rightTree;
			DestroyNode(&aux);
		}
		else
		{
			if (root->rightTree == NULL) {	//só com sub-arvore esquerda
				aux = root;
				root = root->leftTree;
				DestroyNode(&aux);
			}
			else       //com sub-arvores esquerda e direita
			{
				//substitui pelo menor da sub-arvore direita
				root->element = FindMin(root->rightTree)->element;
				//elimina o menor da sub-arvore direita
				root->rightTree = DeleteNode(root->rightTree, root->element);
			}
		}
	return root;
}

#pragma region DeleteII
/* Remover num único método */
Node* deleteNode(Node* root, int key)
{
	// basico
	if (root == NULL)
		return root;

	// Se menor, apagar na sub-arvore esquerda
	if (key < root->element.val)
		root->leftTree = deleteNode(root->leftTree, key);

	// Se maio, apagar na sub-arvore direita
	else if (key > root->element.val)
		root->rightTree = deleteNode(root->rightTree, key);

	//Se encontrei, apagar!
	else {
		// node com uma ou sem nenhuma sub-arvores
		if (root->leftTree == NULL) {
			struct node* temp = root->rightTree;
			free(root);
			return temp;
		}
		else if (root->rightTree == NULL) {
			struct node* temp = root->leftTree;
			free(root);
			return temp;
		}

		// node com duas sub-arvores
		// encontrar o mais pequeno à direita
		Node* temp = FindMin(root->rightTree);

		// Copiar o valor do node menor
		root->element.val = temp->element.val;

		// apagar o node menor na sub-árvore direita
		root->rightTree = deleteNode(root->rightTree, temp->element.val);
	}
	return root;
}
#pragma endregion


/*
Destroy Nodo de Árvore
*/
void DestroyNode(Node **p) {		//DestroyNode(PtrNode *p)	
	//Fazer varias coisas...
	if (*p != NULL) {
		free(*p);
		*p = NULL;
		//H2
		//free((*p)->element);
		//*p = NULL;
	}
}

/*
Identico ao GetMin
*/
PtrNode FindMin(PtrNode root) {
	if (root->leftTree == NULL) return root;
	else
		return(FindMin(root->leftTree));
}

/**
 * @brief 
 *
 * @param root
 */
void PreOrder(Node* root) {
	if (root == NULL) return;
	printf("Val=%d\n", root->element.val);
	PreOrder(root->leftTree);
	PreOrder(root->rightTree);
}


/**
 * @brief 
 *
 * @param root
 */
void PosOrder(Node* root){
	if (root == NULL) return;
	PosOrder(root->leftTree);
	PosOrder(root->rightTree);
	printf("Val=%d", root->element.val);	
}

/**
 * @brief Ordenado
 * 
 * @param root
 */
void InOrder(Node* root){
	if (root == NULL) return;
	InOrder(root->leftTree);
	printf("Val=%d\n", root->element.val);
	InOrder(root->rightTree);
}

#pragma region Funções_como_Parametro
/*
Passagem de Funções como parâmetro
*/
//int (*)(const char *, ...)
/*!
 *  Shows the tree in Order
 *
 *      @param [in] root 
 *      @param [in] f    
 */
void ShowTree(PtrNode root, void(*f)(int v)) {
	if (root == NULL) return;
	//printf("Val=%d\n", root->element.val);
	ShowTree(root->leftTree, f);
	(*f)(root->element.val);
	ShowTree(root->rightTree, f);
}


void ShowII(int v) {
	printf("%d\n", v);
}

#pragma endregion

// =========== Balanceamento ============

/*
Balanceamento da Árvore existentes
a) Percorrer em ordem (in-order) → obter elementos ordenados
b) Construir uma nova árvore balanceada a partir desse array
*/
/*!
 *		a) Percorrer em ordem (in-order) → obter elementos ordenados
 *
 *      @param [in] root 
 *
 *      @return 
 */
PtrNode Balance(PtrNode root) {
	PtrNode newRoot=NULL;
	if (root == NULL) return NULL;

	int tot = TreeSize(root); //quantos nodos tem a arvore?
	int count = 0;

	//criar estrutura "dinâmica" auxiliar
	Node *listNode;
	if ((listNode = (Node *)malloc(sizeof(Node)*tot))==NULL) return NULL;
	//preenche "lista" a partir da arvore
	BST2List(root, &count, listNode);
	//balanceia arvore
	newRoot = BSTBalance(newRoot, listNode, 0, tot - 1);
	free(listNode);
	return newRoot;
}

/*
Balanceia árvore. Travessia Binária de um array!
*/
 /*!
  *  b) Construir uma nova árvore balanceada a partir desse array
  *
  *      @param [in]     root 
  *      @param [in,out] list 
  *      @param [in]     ini  
  *      @param [in]     end  
  *
  *      @return 
  */
PtrNode BSTBalance(PtrNode root, Node *list, int ini, int end) {
	unsigned int m;

	if (ini <= end) {
		m = (ini + end) / 2;
		root = AddNode(root, list[m].element);
		root = BSTBalance(root,list, ini, m - 1);
		root = BSTBalance(root, list, m+1, end);
	}
	return root;
}

/*
Cria uma "Lista" a partir dos elementos de uma arvore
E se for para uma Lista verdadeira?
*/
void BST2List(PtrNode root, int *count, Node *list) {
	if (root != NULL) {
		BST2List(root->leftTree, count, list);
		printf("count = %d\n", *count);
		list[(*count)++].element = root->element;
		BST2List(root->rightTree, count, list);
	}
}

#pragma region AVL

int height(PtrNodeBal n) {
	return (n == NULL) ? 0 : n->height;
}

//int max(int a, int b) {
//	return (a > b) ? a : b;
//}

int getBalance(PtrNodeBal n) {
	return (n == NULL) ? 0 : height(n->leftTree) - height(n->rightTree);
}

/*!
 *  Rotação à direita
 *
 *      @param [in] y
 *
 *      @return
 *      y
 *     /  
 *    x   
 *   / \  
 *  A   T2    
 */
PtrNodeBal rotateRight(PtrNodeBal y) {
	PtrNodeBal x = y->leftTree;
	PtrNodeBal T2 = x->rightTree;

	x->rightTree = y;
	y->leftTree = T2;

	y->height = max(height(y->leftTree), height(y->rightTree)) + 1;
	x->height = max(height(x->leftTree), height(x->rightTree)) + 1;

	return x;
}

/*!
 *  Rotação à Esquerda
 *
 *      @param [in] y
 *
 *      @return
 *      y
 *       \
 *        x
 *       / \
 *      T2  K
 *
 *      x
 *     / \
 *    T2   y
 *       / 
 *      K
 */
PtrNodeBal rotateLeft(PtrNodeBal y) {
	PtrNodeBal x = y->rightTree;
	PtrNodeBal T2 = x->leftTree;

	x->leftTree = y;
	y->rightTree = T2;

	x->height = max(height(x->leftTree), height(x->rightTree)) + 1;
	y->height = max(height(y->leftTree), height(y->rightTree)) + 1;

	return y;
}

/*!
 *  Insere Balanceado.
 *  Esta implementação não respeita o SOLID..porquê? Corrija!
 *
 *      @param [in] node
 *      @param [in] e
 *
 *      @return
 */
PtrNodeBal insertAVL(PtrNodeBal node, Element e) {
	if (node == NULL) {
		PtrNodeBal newNode = (PtrNodeBal)malloc(sizeof(NodeBal));
		newNode->element = e;
		newNode->leftTree = newNode->rightTree = NULL;
		newNode->height = 1;
		return newNode;
	}
	if (e.val < node->element.val)
		node->leftTree = insertAVL(node->leftTree, e);
	else if (e.val > node->element.val)
		node->rightTree = insertAVL(node->rightTree, e);
	else
		return node;	//ignora repetidos

	node->height = 1 + max(height(node->leftTree), height(node->rightTree));

	int balance = getBalance(node);

	// Left Left
	if (balance > 1 && (e.val < node->leftTree->element.val))
		return rotateRight(node);

	// Right Right
	if (balance < -1 && (e.val > node->rightTree->element.val))
		return rotateLeft(node);

	// Left Right
	if (balance > 1 && (e.val > node->leftTree->element.val)) {
		node->leftTree = rotateLeft(node->leftTree);
		return rotateRight(node);
	}

	// Right Left
	if (balance < -1 && (e.val < node->rightTree->element.val)) {
		node->rightTree = rotateRight(node->rightTree);
		return rotateLeft(node);
	}

	return node;
}

#pragma endregion

/*
Mostrar um determinado nível da árvore
*/
void Show(PtrNode root, int nivel) {
	int i;
	if (root == NULL) {
		for (i = 0; i < nivel; i++) printf("\t");	//indentar
		printf("*\n");
		return;
	}
	Show(root->rightTree, nivel + 1);
	for (i = 0; i < nivel; i++) printf("\t");		//indentar
	printf("%d\n", root->element.val);
	Show(root->leftTree, nivel + 1);
}

/*
Exercício Folha 10
Parsing a uma string com expressão em pre-order

*/
Exp* Parse(char v[], int i) {
	char o;
	Exp *aux=NULL;

	if (i < sizeof(v)) {
		o = v[i];
		aux = (Exp*)malloc(sizeof(Exp));
		if (!aux) return NULL;
		aux->val = o;		
		if ((o == '+') || (o == '-')) {
			aux->oper = o;
			aux->dir = Parse(v, ++i);
			aux->esq = Parse(v, ++i);
		}
	}
	return aux;
}


/*
Cria Array a partir de Árvore
Array tem dimensão suficiente para conter toda a árvore...
*/
void Copy2Array(Node *root, int array[])
{
	static int i = 0;
	if (root != NULL)
	{
		Copy2Array(root->leftTree, array);
		array[i] = root->element.val;
		i++;
		Copy2Array(root->rightTree, array);
	}
}

/*
Quantos são maiores que determinado elemento
*/
int CountGreaterX(Node* root, int x)
{
	if (root == NULL)
		return 0;
	if (root->element.val > x)
		return 1 + CountGreaterX(root->leftTree, x) + CountGreaterX(root->rightTree, x);
	else
		return CountGreaterX(root->rightTree, x);
}

void DebugPrint(Node* r) {
	if (!r) return;

	printf("Node val = %d\n", r->element.val);

	DebugPrint(r->leftTree);
	DebugPrint(r->rightTree);
}