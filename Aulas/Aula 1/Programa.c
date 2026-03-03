/**
* Author: lufer
* Email: lufer@ipca.pt
* Desc: Organização de projetos
* 
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "Globais.h"

#pragma warning(disable : 4996) 
#pragma comment(lib,"Lib/CalcLib.lib")

/**
* Programa Principal
*/
int main() { 


	//int x = Soma(3, 4);

	Carro y;
	
	int x = Soma(12, 34);
	printf("Soma: %d\n", x);

	strcpy(objetos[0].designacao,"Porto");
	objetos[0].distancia = 70;

	strcpy(objetos[1].designacao, "Lisboa");
	objetos[1].distancia = 350;

	float media = AvgDistObject(objetos, 2);
	
	printf("Media: %0.2f\n", media);

	char c=_getche();
}