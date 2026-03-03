/**
* Author: lufer
* Email: lufer@ipca.pt
* Desc: Módulo para Gerir Arrays
*/

#include<stdbool.h>
#include "Globais.h"

#pragma region Arrays

/**
* Encontra o maior valor de um array de inteiros
*/
int FindMaxArray(int v[], int n) {
	if (n <= 0) return -1;	//ATENÇÃO: não é solução robusta
	int maior = v[0];
	for (int i = 1; i < n; i++) {
		if (v[i] > maior) maior = v[i];
	}
	return maior;
}

/**
*/
bool ExisteValorArray(Carro v[], int n) {
	//código
	return false;

}

/**
* Calcula a média....
* ATENÇÃO: Solução não robusta. Com uso de apontadores melhora-se!
*/
float AvgDistObject(Objeto v[], int n) {
	float totDist = 0.0f;

	if (n <= 0) return 0.0f; //conflito pois a média pode ser zero!

	for (int i = 0; i < n; i++) {
		totDist += v[i].distancia;
	}
	return(totDist / n);
}

#pragma endregion
