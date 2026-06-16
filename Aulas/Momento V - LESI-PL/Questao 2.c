/*!
 * EDA - 2025-2026
*  @file Questao 2.c
 *  @author mustl
 *  @date 2026-06-08
 *  @project Momento V - LESI-PL
 *
 *  Implementa Questao 2.
 */

#include "Dados.h"

/*!
 *  Inserção sem duplicados com retorno da contagem total
 *
 *      @param [in,out] cais   
 *      @param [in]     idNovo 
 *
 *      @return 
 */
// Melhor:
// int empilharContentor(Cais* cais, Contentor novo) {
int empilharContentor(Cais* cais, int idNovo) {
    Contentor* atual = cais->topoAcessivel;
    int contador = 0;
    bool existe = false;

    // Verificar duplicação e contar quantos já existem
    while (atual != NULL) {
        if (atual->idContentor == idNovo) {
            existe = true;
        }
        contador++;
        atual = atual->abaixo;
    }

    if (existe) {
        return contador; // Não insere, devolve apenas o tamanho atual
    }

    // Alocação e inserção no topo
    //Melhor: Respeitar SOLID..não deve fazer malloc aqui...deve entrar um Contentor
    Contentor* novo = (Contentor*)malloc(sizeof(Contentor));
    if (novo == NULL) return contador;

    novo->idContentor = idNovo;
    novo->abaixo = cais->topoAcessivel;
    cais->topoAcessivel = novo;
    contador++;

    return contador;
}

/*!
 *  Remoção de elemento do meio..usa lista temporária.
 *
 *      @param [in,out] caisOriginal 
 *      @param [in]     idAlvo       
 *
 *      @return 
 */
bool carregarNoCamiao(Cais* caisOriginal, int id) {
    
    Cais caisTemporario;    //lista temporária
    caisTemporario.topoAcessivel = NULL;
    bool encontrado = false;

    // 1: Retirar até encontrar o id que procura
    while (caisOriginal->topoAcessivel != NULL) {
        if (caisOriginal->topoAcessivel->idContentor == id) {
            encontrado = true;
            break;
        }
        // Retira do topo original e coloca no topo da lista temporária
        Contentor* temp = caisOriginal->topoAcessivel;
        caisOriginal->topoAcessivel = temp->abaixo;

        temp->abaixo = caisTemporario.topoAcessivel;
        caisTemporario.topoAcessivel = temp;
    }

    // 2: Se encontrou, retira o contentor, retira 
    if (encontrado) {
        Contentor* alvo = caisOriginal->topoAcessivel;
        caisOriginal->topoAcessivel = alvo->abaixo;
        free(alvo);
    }

    // 3: Repor os contentores da lista temporária 
    while (caisTemporario.topoAcessivel != NULL) {
        Contentor* repor = caisTemporario.topoAcessivel;
        caisTemporario.topoAcessivel = repor->abaixo;

        repor->abaixo = caisOriginal->topoAcessivel;
        caisOriginal->topoAcessivel = repor;
    }

    return encontrado;
}
