/*!
 * EDA - 2025-2026
*  @file Arvore.c
 *  @author mustl
 *  @date 2026-04-39
 *  @project Momento III
 *
 *  Implementa uma Árvore Binária de Procura (ABP)
 *
 *      Porquê árvore:
 *
 *      Lista Ligada: Serve para a sequência (ordem física de montagem).
 *      Hash Table: Serve para o acesso rápido por categoria (tipo de produto).
 *      Árvore Binária de Procura: Serve para a ordenação e pesquisa no inventário global.
 */
#include "SmartFactory.h"

#pragma region ABP

 /*!
  *  ABP: Listar inventario ordenado. Travessia InOrder
  *
  *      @param [in,out] raiz
  */
void ListarInventarioOrdenado(NodoABP* raiz) {
    if (raiz == NULL) return;
    ListarInventarioOrdenado(raiz->esq);
    printf("ID: %d | Tempo: %.2f | Estado: %s\n",
        raiz->pMaquina->num,
        raiz->pMaquina->tempo,
        raiz->pMaquina->estado ? "Ativo" : "Avariado");
    ListarInventarioOrdenado(raiz->dir);
}

// ABP: Inserção por ordem de código (num)
int InserirNaABP(NodoABP* raiz, Maquina* pm) {
    if (raiz == NULL) {
        raiz = (NodoABP*)malloc(sizeof(NodoABP));
        raiz->pMaquina = pm;
        raiz->esq = raiz->dir = NULL;
        return 1;
    }
    if (pm->num < raiz->pMaquina->num)
        return InserirNaABP(raiz->esq, pm);
    else if (pm->num > raiz->pMaquina->num)
        return InserirNaABP(raiz->dir, pm);

    return 0; // Já existe na árvore
}
#pragma endregion