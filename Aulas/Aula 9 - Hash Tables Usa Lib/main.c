/*
Manipular Tabelas de Hash
lufer
2026
*/

#include <stdio.h>
#include <locale.h>	// ASCII SET
#include "hash.h"
#include "Libs\Dados.h"
#include "Libs\Funcoes.h"

#pragma comment(lib,"Libs\\Aula 9 - Lista Lib.lib")

int main() 
{	
	setlocale(LC_ALL, "Portuguese");

	printf("Hash(Maria)=%d\n", Hash("Maria"));
	printf("Hash(Maria João)=%d\n", Hash("Mario"));

	HashTable* hash = CriaHashII(MAX);
	Element* n1 = CriaElemento(12, "Maria");
	int res = InsereHashOrdenado(hash, n1);
	bool r= ShowHashII(hash);


#pragma endregion
}