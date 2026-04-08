/*!
 *  @file Main.c
 *  @author mustl
 *  @date 2026-03-25
 *  @project Aula 8 - Listas Ligadas - Ficheiros
 *
 *  Implements the main.
 */

#include "Funcoes.h"

int main() {
	//criar lista
#pragma region CRIARLISTA

	Element* aux;		//auxiliar para criar elementos
	Element* inicioLista=NULL;	//...
	//Criar elemento
	aux = CriaElemento(12, "Ola");
	inicioLista = InsereOrdenado(inicioLista, aux);

	aux = CriaElemento(120, "Ola2");
	inicioLista = InsereOrdenado(inicioLista, aux);

	MostraLista(inicioLista);

#pragma endregion

#pragma region REMOVER

	bool res;
	inicioLista= RemoveElement(inicioLista, 12,&res);
	if (res == false) {
		printf("Não foi possível remover!!!");
	}
	else
		printf("Removido!!!\n");

#pragma endregion

#pragma region FICHEIROS

	res = GravarElementBinario("d:\\temp\\lixo.bin", inicioLista);
	inicioLista = DestroiListaII(inicioLista);
	inicioLista = LerElementsBinario("d:\\temp\\lixo.bin");
	MostraLista(inicioLista);

#pragma endregion


}
