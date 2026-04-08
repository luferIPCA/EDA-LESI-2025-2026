/*!
 *  @file Funcoes.c
 *  @author mustl
 *  @date 2026-03-21
 *  @project Aula 8 - Listas Ligadas - Ficheiros
 *
 *  Implementa funcoes.
 *      Alterar
 *      Remover
 *      Gravar em ficheiro
 *      Carregar de ficheiro
 */

#include "Dados.h"

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
	while (aux && aux->value < v) {
		aux = aux->prox;
	}
	if (aux && aux->value == v) return aux;	//valor encontrado
	return NULL;
}


Element* CriaElemento(int v, char* nome) {
	Element* aux;

	aux = (Element*)malloc(sizeof(Element));
	if (aux != NULL) {
		aux->value = v;
		if (nome) strcpy(aux->nome, nome);
		aux->prox = NULL;
		aux->apagado = false;
	}
	return aux;
}

/*!
 *  Inseres the ordenado. Admite repetições
 *
 *      @param [in,out] h    
 *      @param [in,out] novo 
 *
 *      @return 
 */
Element* InsereOrdenadoII(Element* h, Element* novo) {
	Element* ant = NULL, * atual = h;

	// procurar posição (ordenado crescente)
	while (atual != NULL && atual->value < novo->value) {
		ant = atual;
		atual = atual->prox;
	}

	// inserir no início
	if (ant == NULL) {
		novo->prox = h;
		h = novo;
	}
	else {
		novo->prox = atual;
		ant->prox = novo;
	}

	return h;
}

/*!
 *  Insere Ordenado sem admitir repetições.
 *
 *      @param [in,out] inicio
 *      @param [in,out] novo
 *
 *      @return
 */
Element* InsereOrdenado(Element* inicio, Element* novo) {
	Element* ant = NULL, * atual = inicio;
	//validações
	if (novo == NULL) return inicio;

	//Se já existe, não insere
	if (ProcuraElemento(inicio, novo->value)) return inicio;

	// procurar posição (ordenado crescente)
	while (atual != NULL && atual->value < novo->value) {
		ant = atual;
		atual = atual->prox;
	}

	// inserir no início
	if (ant == NULL) {
		novo->prox = inicio;
		inicio = novo;
	}
	else {
		novo->prox = atual;
		ant->prox = novo;
	}

	return inicio;
}



/*!
 *  Insere ordenado com controlo de sucesso.
 *
 *      @param [in,out] inicio Head da lista
 *      @param [in,out] novo   novo elemento a adicionar
 *      @param [in,out] res    resultado: true - Sucesso, false - Erro
 *
 *      @return 
 */
Element* InsereOrdenadoControlado(Element* inicio, Element* novo, bool *res) {

	*res = false;		//por defeito é falso
	//validações
	if (novo == NULL) return inicio;
	//Se já existe, não insere
	if (ProcuraElemento(inicio, novo->value)) 
		return inicio;

	//procurar a posição
	//1ª posição
	if (inicio == NULL) {
		inicio = novo; return inicio;
	}
	if (inicio->value > novo->value) {
		novo->prox = inicio;
		inicio = novo;
	}
	//procura posição
	Element* aux = inicio;
	Element* aux2 = aux;
	while (aux->value < novo->value && aux->prox != NULL)
	{
		aux2 = aux;
		aux = aux->prox;
	}
	//se for na última posição
	if (aux->value < novo->value)
		aux->prox = novo;
	else
	{
		novo->prox = aux;
		aux2->prox = novo;
	}
	*res = true;
	return inicio;
}
 /**
 * @brief Altera dados do Elemento
 * @param [in]	h	Apontador para inicio da Lista
 * @param [in]	cod	Codigo do elemento a alterar
 * @param [in]	novoNome	novo nome para o elemento
 * @return	Apontador para Lista
 */
Element* AlteraElement(Element* h, int v, char*novoNome) {
	Element* aux = ProcuraElemento(h, v);
	if (aux != NULL)		//se encontrou o Element
	{
		strcpy(aux->nome, novoNome);
	}
	return h;
}

/*!
 *  Removes the element.
 *
 *      @param [in,out] h   
 *      @param [in]     cod 
 *
 *      @return 
 */
Element* RemoveElement(Element* h, int cod, bool *res) {
	if (h == NULL) {
		*res = false; return NULL;
	}			//Lista vazia
	//if (!ProcuraElemento(h, cod)) return h;	//se não existe

	if (h->value == cod) {		//remove no inicio da lista
		Element* aux = h;
		h = h->prox;
		*res = true;
		free(aux);
	}
	else
	{
		Element* aux = h;
		Element* auxAnt = aux;
		while (aux && aux->value != cod) {	//procura para revover
			auxAnt = aux;
			aux = aux->prox;
		}
		if (aux != NULL) {					//se encontrou, remove
			auxAnt->prox = aux->prox;
			*res = true;
			free(aux);
		}
	}
	
	return h;
}

/**
* @brief Remove Element de forma Recursiva. Código indexado pelo seu código (cod)
* @param [in]	h	Apontador para inicio da Lista
* @param [in]	cod	Codigo do Element a alterar
* @return	Apontador para Lista
*/
Element* RemoveElementRecursivo(Element* head, int cod, int*res) {
	Element* aux;

	if (head == NULL)
		return NULL;

	if (head->value == cod) {
		aux = head;
		head = head->prox;
		*res = true;
		free(aux);
	}
	else {
		head->prox = RemoveElementRecursivo(head->prox, cod, res);
	}

	return head;
}

/**
* @brief Ordena Lista
* @param [in]	h	Apontador para inicio da Lista
* @return	Apontador para Lista ordenada
*/
Element* OrdenaLista(Element* h) {
	if (h == NULL) return NULL;
	Element* listaOrdenada = NULL;
	Element* aux = h;
	Element* novo;
	while (aux) {
		novo = CriaElemento(aux->value, aux->nome);
		listaOrdenada = InsereOrdenado(listaOrdenada, novo);
		aux = aux->prox;
	}
	return listaOrdenada;
}


/**
* @brief Destroi todos os nodos da lista
* @param [in]	h	Apontador para inicio da Lista
*/

bool DestroiLista(Element** h) {
	if (h == NULL) return false;
	//if (h != NULL) {
		Element* aux;
		while (*h) {
			aux = *h;
			*h = (*h)->prox;
			free(aux);
		}
	//}
	return true;
}

//ou

Element* DestroiListaII(Element* h) {
	if (h != NULL) {
		Element* aux;
		while (h) {
			aux = h;
			h = h->prox;
			free(aux);
		}
	}
	return h;
}


#pragma region FICHEIROS

// ========================= Ficheiros ============================
//Ver : https://www.geeksforgeeks.org/readwrite-structure-file-c/

/**
* @brief Preservar dados em ficheiro
* Grava todos os nodos da Lista em Ficheiro
*/
bool GravarElementBinario(char* nomeFicheiro, Element* h) {
	FILE* fp;

	if (h == NULL) return false;
	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;
	//grava todos registos da lista no ficheiro
	Element* aux = h;
	ElementFile auxElement;	//struct auxiliar para gravar em ficheiro!
	while (aux) {			//while(aux!=NULL)
		//Colocar no registo de ficheiro a inf que está no registo de memória
		auxElement.value = aux->value;
		strcpy(auxElement.nome, aux->nome);
		fwrite(&auxElement, sizeof(ElementFile), 1, fp);
		aux = aux->prox;
	}
	fclose(fp);
	return true;
}

/**
* @brief Lê informação de ficheiro
*/
Element* LerElementsBinario(char* nomeFicheiro) {
	FILE* fp;
	Element* h = NULL;
	Element* aux;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;
	//lê n registos no ficheiro
	ElementFile auxElement;
	while (fread(&auxElement, sizeof(ElementFile), 1, fp)) {
		//printf("Element=%s\n", auxElement.nome);
		aux = CriaElemento(auxElement.value, auxElement.nome);
		h = InsereOrdenado(h, aux);
	}
	fclose(fp);
	return h;
}

/*!
 *  Lers the elements binario com feof()
 *
 *      @param [in,out] nomeFicheiro 
 *
 *      @return 
 */
Element* LerElementsBinarioII(char* nomeFicheiro) {
	FILE* fp;
	Element* h = NULL;
	Element* aux;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;

	ElementFile auxElement;

	while (!feof(fp)) {
		if (fread(&auxElement, sizeof(ElementFile), 1, fp) == 1) {
			aux = CriaElemento(auxElement.value, auxElement.nome);
			h = InsereOrdenado(h, aux);
		}
	}

	fclose(fp);
	return h;
}
#pragma endregion


void MostraLista(Element* h) {
	Element* aux = h;
	while (aux) {
		printf("Cod: %d\n", aux->value);
		aux = aux->prox;
	}
}

#pragma region HISTÓRICO


Element* RemoverLogico(Element* h, int value, bool *res) {
	Element* aux = h;
	*res = false;
	while (aux != NULL) {
		if (aux->value == value && !aux->apagado) {
			aux->apagado = true;		//apenas marca como removido!
			*res=true;
			return h;
		}
		aux = aux->prox;
	}

	return h; // não encontrou
}

Element* ApagaElementoEfetivo(Element* h, int value, bool *res) {
	Element* atual = h, * ant = NULL;
	*res = false;
	while (atual != NULL) {
		if (atual->value == value) {
			if (ant == NULL) {
				// remover cabeça
				h = atual->prox;
			}
			else {
				ant->prox = atual->prox;
			}
			free(atual);
			*res = true;
			return h;
		}
		//senão, avança
		ant = atual;
		atual = atual->prox;
	}

	return h; // não encontrou
}


Element* ApagaRemovidos(Element* h, char* nomeFicheiroHistorico, bool *res) {
	*res = false;
	FILE* fh = fopen(nomeFicheiroHistorico, "ab");
	if (fh == NULL) return h;

	Element* atual = h;
	ElementFile ef;	//registo para ficheiro

	while (atual != NULL) {
		if (atual->apagado) {
			// guardar dados
			ef.value = atual->value;
			strcpy(ef.nome, atual->nome);
			fwrite(&ef, sizeof(ElementFile), 1, fh);

			int val = atual->value;        // guardar valor
			atual = atual->prox;           // avançar antes de apagar
			
			//ou usar ef.value
			//h = ApagaElementoEfetivo(h, ef.value, res);
			h = ApagaElementoEfetivo(h, val, res);
		}
		else {
			atual = atual->prox;
		}
	}

	fclose(fh);
	return h;
}


bool GravarElementos(Element* h, char* ficheiroAtivos, char* ficheiroHistorico) {
	FILE* fa, * fh;

	fa = fopen(ficheiroAtivos, "wb");
	fh = fopen(ficheiroHistorico, "wb");

	if (fa == NULL || fh == NULL) return false;

	Element* aux = h;
	ElementFile ef;

	while (aux != NULL) {
		ef.value = aux->value;
		strcpy(ef.nome, aux->nome);

		if (aux->apagado) {
			fwrite(&ef, sizeof(ElementFile), 1, fh);
		}
		else {
			fwrite(&ef, sizeof(ElementFile), 1, fa);
		}

		aux = aux->prox;
	}

	fclose(fa);
	fclose(fh);
	return true;
}



#pragma endregion


