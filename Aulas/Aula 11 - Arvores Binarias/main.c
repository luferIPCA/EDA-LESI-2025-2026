/*
Árvores Binárias de Procura - (Binary Search Tree )
lufer@ipca.pt
Ver:
https://www.geeksforgeeks.org/binary-tree-set-1-introduction/?ref=lbp
*/
#include <stdio.h>
#include <locale.h>	// ASCII SET
#include "btree.h"
#include <stdbool.h>

int main() {

	setlocale(LC_ALL, "Portuguese");

#pragma region ESSENCIAL

	Node* raiz = InitTree();		//raiz=NULL;
	//printf("%d", raiz == NULL);

	Element e;

	e.val = 12;
	raiz = AddNode(raiz, e);

	e.val = 7;
	raiz = AddNode(raiz, e);

	e.val = 15;
	raiz = AddNode(raiz, e);

	//Mostrar Arvore com função auxiliar como parâmetro
	ShowTree(raiz, ShowII);

	printf("\n ---------ANTES DE ELIMINAR NODO-----------\n");
	PreOrder(raiz);

	DeleteNode(raiz, e);

	printf("\n ---------DEPOIS DE ELIMINAR NODO-----------\n");
	PreOrder(raiz);

	e.val = 15;
	raiz = AddNode(raiz, e);

	e.val = 9;
	raiz = AddNode(raiz, e);

	e.val = 8;
	raiz = AddNode(raiz, e);

	e.val = 6;
	raiz = AddNode(raiz, e);

	printf("\n ---------DEPOIS DE ADICIONAR 15, 9, 8, 6 -----------\n");
	PreOrder(raiz);

	printf("----ORDENADO---------------\n");

	//e.val = 7;
	//DeleteNode(raiz, e);

	InOrder(raiz);

	printf("-------------------\n");

#pragma endregion

#pragma region BALANCEAMENTO

	 int tot = TreeSize(raiz);
	 int count = 0;

	Show(raiz, 1);
	//ou
	//DebugPrint(raiz);

	raiz = Balance(raiz);

	Show(raiz, 1);

#pragma endregion

#pragma region Folha_10

	//Folha 10
	Exp* aux;
	aux = Parse("+23", 0);
	system("pause");
	return 0;

#pragma endregion


#pragma region DUPLOS_APONTADORES

	Node* root = NULL;
	bool res = AddNodeIII(&root, e);

#pragma endregion

}

//Explorar
/*
* 0-Criar Dados.h
* 1-Definir struct Nodo da árvore
* 2- Definir métodos:
*  - Cria Árvore
*  - Cria Nodo de Árvore
*  - No "main" Inserir diretamente nodos na árvore
*      - root = novoNodo1
*      - root->left = novoNodo1
*      - root->right= novoNodo2
*      - etc.
*  - Percorre arvore
*  - Mostra árvore
*  - Existe Nodo
*  - Devolve Nodo
*  - Adicionar Nodo
*  - Remover Nodo
*  - Quantos são maiores
*  - Gerar Array a partir de Árvore
**/