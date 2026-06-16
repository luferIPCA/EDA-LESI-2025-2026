/*!
 * EDA - 2025-2026
*  @file Questao3.c
 *  @author mustl
 *  @date 2026-06-03
 *  @project Momento V
 *
 *  Implements Questao 3
 */
#include "Dados.h"

//ABP

/*!
 *  Consultar coima.
 *
 *      @param [in,out] raiz          
 *      @param [in,out] matricula 
 *      @param [in,out] coima         
 *
 *      @return 
 */
bool CalculaCoima(RegistroInfracao* raiz, char* matricula, float* coimaTotal) {
    // Não existe infração registada
    if (raiz == NULL) {
        return false;
    }

    int comp = strcmp(matricula, raiz->matricula);

    // Veículo encontrado
    if (comp == 0) {
        float somatorio = 0.0f;
        Coima* atualCoima = raiz->listaCoimas;

        // Analisa o conjunto de coimas pendentes 
        while (atualCoima != NULL) {
            somatorio += atualCoima->valorCoima;
            atualCoima = atualCoima->seguinte;
        }

        *coimaTotal= somatorio; // Devolve o valor total acumulado por referência
        return true;            // Confirma que o veículo existe e tem registo
    }

    // Procura no resto da árvore
    if (comp < 0) {
        return CalculaCoima(raiz->esquerda, matricula, coimaTotal);
    }
    else {
        return CalculaCoima(raiz->direita, matricula, coimaTotal);
    }
}

