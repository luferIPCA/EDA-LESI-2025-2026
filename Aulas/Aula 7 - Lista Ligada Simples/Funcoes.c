/*!
 *  @file Funcoes.c
 *  @author mustl
 *  @date 2026-03-14
 *  @project Aula 7 - Lista Ligada Simples
 *
 *  Implementa funcoes.
 *
 */

#include "Dados.h"
#include "Funcoes.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

#pragma region A

Element* CriaElemento(int v, char nome[]) {
	Element* aux;
	aux = (Element*)malloc(sizeof(Element));
	if (aux!=NULL) {
		aux->value = v;
		strcpy(aux->nome, nome);
		aux->prox = NULL;
	}
	return aux;
}


#pragma endregion

/*!
 *  Cria element.
 *
 *      @param [in] v 
 *
 *      @return 
 */
Element* CriaElement(int v) {
	Element* aux;
	aux = (Element*)malloc(sizeof(Element));
	if (aux != NULL) {
		aux->value = v;
		aux->prox = NULL;
	}
	return (aux);
}


Element* InsereInicio(Element* inicio, Element* novo) {
	//validar parametros
	if (novo == NULL) return inicio;//Não há nada para inserir
	//h1
	novo->prox = inicio;
	inicio = novo;

	//h2
	/*
	if (!inicio) //ou if(inicio==NULL)
	{
		inicio = novo;	//primeiro elemento da lista!
	}
	else {
		novo->prox = inicio;
		inicio = novo;
	}
	*/
	return inicio;
}


Element* InsereFim(Element* inicio, Element* novo) {
	
	if (!novo) return inicio;//nada para inserir
	//se a lista for vazia
	if (inicio == NULL) {
		inicio = novo; 
		return inicio;
		//ou
		//return novo;
	}
	Element* aux = inicio;
	//senão coloca-se no fim da lista...
	while (aux->prox != NULL) aux = aux->prox;
	//insere no fim
	aux->prox = novo;
	return inicio;
}


/*!
 *  Mostra lista sem retorno de controlo
 *
 *      @param [in,out] ini 
 */
void MostraTudo(Element* ini) {
	Element* aux = ini;
	while (aux) {
		printf("Valor: %d", ini->value);
		aux = aux->prox;
	}
}

/*!
 *  Mostra lista com retorno de controlo
 *
 *      @param [in,out] h 
 *
 *      @return 
 */
int MostraLista(Element* h) {
	if (!h) return 0;
	Element* aux = h;
	int tot = 0;
	while (aux != NULL) {
		printf("v=%d\n", aux->value);
		aux = aux->prox;
		tot++;
	}
	return tot;
}

/*!
 *  Procura elemento.
 *
 *      @param [in,out] h 
 *      @param [in]     v 
 *
 *      @return 
 */

Element* ProcuraElemento(Element* h, int v) {
	Element* aux = h;
	while (aux && aux->value<v) {
		aux = aux->prox;
	}
	if (aux && aux->value == v) return aux;	//valor encontrado
	return NULL;
}

/*!
 *  Procura elemento e devolve bool caso existe ou não
 *
 *      @param [in,out] h
 *      @param [in]     v
 *
 *      @return
 */
bool ExisteElemento(Element* h, int v) {
	Element* aux = h;
	while (aux && aux->value < v) {
		aux = aux->prox;
	}
	if (aux && aux->value == v) return true;	//valor encontrado
	return false;
}

/*!
 *  Procura elemento Recursivo! Devolve bool caso existe ou não
 *
 *      @param [in,out] h
 *      @param [in]     v
 *
 *      @return
 */
bool ExisteElementRecursivo(Element* h, int v) {
	if (h == NULL) return false;
	if (h->value == v) return true;
	return (ExisteElementRecursivo(h->prox, v));
}


/*!
 *  Insere Ordenado mas não testa se existem repetições.
 *
 *      @param [in,out] inicio
 *      @param [in,out] novo
 *
 *      @return
 */
Element* InsereOrdenado(Element* inicio, Element* novo) {
	//Validações
	if (novo == NULL) return inicio;

	// Inserção no início ou Lista vazia
	if (inicio == NULL || novo->value < inicio->value) {
		novo->prox = inicio;
		return novo;
	}
	//restantes situações
	//procurar a posição correta
	Element* aux = inicio;
	Element* aux2 = aux;	//sempre atrás de aux

	while ((aux->value < novo->value) && aux != NULL)
	{
		aux2 = aux;
		aux = aux->prox;
	}
	//insere entre elementos
	aux2->prox = novo;
	novo->prox = aux;
	
	return inicio;
}

#pragma region MAIS_INSERÇÔES

/*!
 *  Insere Ordenado sem admitir repetições.
 *
 *      @param [in,out] inicio 
 *      @param [in,out] novo   
 *
 *      @return 
 */
Element* InsereOrdenadoII(Element* inicio, Element* novo) {

	//validações
	if (novo == NULL) return inicio;
	//Se já existe, não insere
	if (ExisteElemento(inicio,novo->value)) return inicio;

	// Inserção no início ou Lista vazia
	if (inicio == NULL || novo->value < inicio->value) {
		novo->prox = inicio;
		return novo;
	}
	//restantes situações
	//procurar a posição correta
	Element* aux = inicio;
	Element* aux2 = aux;	//sempre atrás de aux

	while ((aux->value < novo->value) && aux != NULL)
	{
		aux2 = aux;
		aux = aux->prox;
	}
	//insere entre elementos
	aux2->prox = novo;
	novo->prox = aux;

	return inicio;
	
}

/*!
 *  Insere Ordenado com retorno de sucesso|insucesso
 */
bool InsereOrdenadoIII(Element** inicio, Element* novo) {
	if (novo == NULL) return false;

	if (*inicio == NULL || novo->value < (*inicio)->value) {
		novo->prox = *inicio;
		*inicio = novo;
		return true;
	}

	Element* aux = *inicio;

	while (aux->prox != NULL && aux->prox->value < novo->value) {
		aux = aux->prox;
	}

	novo->prox = aux->prox;
	aux->prox = novo;

	return true;
}


/*!
 *  Insere Ordenado com retorno de sucesso|insucesso
 */
Element* InsereOrdenadoIV(Element* inicio, Element* novo, bool* inserido) {
	if (novo == NULL) {
		if (inserido) *inserido = false;
		return inicio;
	}

	if (inicio == NULL || novo->value < inicio->value) {
		novo->prox = inicio;
		if (inserido) *inserido = true;
		return novo;
	}

	Element* aux = inicio;

	while (aux->prox != NULL && aux->prox->value < novo->value) {
		aux = aux->prox;
	}

	novo->prox = aux->prox;
	aux->prox = novo;

	if (inserido) *inserido = true;
	return inicio;
}

/*!
 *  Inseres the ordenado com sucesso e insucesso
 *
 *      @param [in,out] inicio 
 *      @param [in,out] novo   
 *
 *      @return 
 */
Resultado InsereOrdenadoV(Element* inicio, Element* novo) {
	Resultado res;
	res.inicio = inicio;
	res.inserido = false;

	// Validação
	if (novo == NULL)
		return res;

	// Inserção no início
	if (inicio == NULL || novo->value < inicio->value) {
		novo->prox = inicio;
		res.inicio = novo;
		res.inserido = true;
		return res;
	}

	Element* aux = inicio;
	Element* aux2=NULL;

	while (aux != NULL && aux->value < novo->value) {
		aux2 = aux;
		aux = aux->prox;
	}

	// Inserção entre aux2 e aux
	if (aux2) aux2->prox = novo;
	novo->prox = aux;

	res.inicio = inicio;
	res.inserido = true;
	return res;
}

#pragma endregion

#pragma region REMOVER
/*!
 *  Removes element.
 *
 *      @param [in,out] inicio   
 *      @param [in]     valor    
 *      @param [in,out] removido 
 *
 *      @return 
 */
Element* RemoveElemento(Element* inicio, int valor, bool* removido) {
	if (removido) *removido = false;

	if (inicio == NULL)
		return inicio;

	Element* aux = inicio;
	Element* auxAnt = NULL;

	// Procurar o elemento
	while (aux != NULL && aux->value <= valor) {
		auxAnt = aux;
		aux = aux->prox;
	}

	// Não encontrou
	if ((aux == NULL) || aux->value!=valor)
		return inicio;

	// Caso 1: remover o primeiro
	if (auxAnt == NULL) { //ou if (aux==inicio)
		inicio = aux->prox;
	}
	else {
		// Caso 2: remover do meio ou fim
		auxAnt->prox = aux->prox;
	}

	free(aux);

	if (removido) *removido = true;
	return inicio;
}

/*!
 *  Removes all elements equal to "valor"
 *
 *      @param [in,out] inicio   
 *      @param [in]     valor    
 *      @param [in,out] removido 
 *
 *      @return 
 */
Element* RemoveTodos(Element* inicio, int valor, bool* removido) {
	if (removido) *removido = false;
	if (!inicio) return NULL;

	Element* atual = inicio;
	Element* anterior = NULL;

	while (atual != NULL) {
		if (atual->value == valor) {

			if (atual == inicio) {  // remover no início
				inicio = atual->prox; //ou inicio = inicio->prox;
			}
			else {                // meio ou fim
				anterior->prox = atual->prox;
			}
			free(atual);
			if (removido) *removido = true;
		}
		else {
			anterior = atual;
			atual = atual->prox;
		}
	}

	return inicio;
}
#pragma endregion
