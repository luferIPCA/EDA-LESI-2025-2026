/*
Manipular Tabelas de Hash
lufer
2026
*/

#include <stdio.h>
#include <locale.h>	// ASCII SET
#include "hash.h"

int main() 
{	
	setlocale(LC_ALL, "Portuguese");

	//struct Node* hashTable[MAX];
	//ou
	static struct Node** hashTable;

	printf("Hash(Maria)=%d\n", Hash("Maria"));
	printf("Hash(Maria João)=%d\n", Hash("Mario"));

#pragma region ABORDAGEM 1

	// ===================== GERIR HASH ===================
	
		//Criar Tabela de Hash

		hashTable = CriaHash(MAX);

		//Inicializar Hash Table

		bool aux = IniciaHash(hashTable, MAX);
		if (aux == false) {
			//erro
		}

		//ou
		//hashTable = IniciaHashII(hashTable);
		//if (hashTable == NULL) {
		//	//erro
		//}

		//Insere valor
		hashTable = InsertValHash("Luís Vaz de Camões", hashTable);
		ShowHash(hashTable);
		
		//Insere célula
		NodePtr novo1 = NewNode("Fernando Pessoa");
		//ou
		// Node *novo1 = NewNode("Fernando Pessoa");
		hashTable = InsertNodeHash(novo1, hashTable);

		NodePtr novo2 = NewNode("Eça de Queiroz");
		hashTable = InsertNodeHash(novo2, hashTable);

		ShowHash(hashTable);

		NodePtr auxFind = FindNode("Mário Zambujal", hashTable);
		if (auxFind == NULL) {
			//ERRO
		}
		else
			ShowNode(auxFind);


		auxFind = FindNode("Eça de Queiroz", hashTable);
		if (auxFind == NULL) {
			//ERRO
		}
		else
			ShowNode(auxFind);

		hashTable = Cleanup(hashTable);
		ShowHash(hashTable);

#pragma endregion


#pragma region ABORDAGEM 2

		HashTable* hash = CriaHashII(MAX);

		Node* n1 = NewNode("Eça de Queiroz");
		hash = InsereHashOrdenado(hash, n1);



#pragma endregion
}