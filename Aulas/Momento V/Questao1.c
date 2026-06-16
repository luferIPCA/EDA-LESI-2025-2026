/*!
 * EDA - 2025-2026
*  @file Questao1.c
 *  @author mustl
 *  @date 2026-06-03
 *  @project Momento V
 *
 *  Implements Questao 1
 */
#include "Dados.h"

/*!
 *  b) Registar novo chassis.
 *
 *      @param [in,out] linha   
 *      @param [in]     novoNum 
 *
 *      @return 
 */
int RegistarChassis(LinhaPintura* linha, int novoNum) {
    Chassis* atual = linha->topoEntrada;
    int total = 0;
    bool duplicado = false;

    // Detetar duplicados
    // Melhor: Função Existe()
    while (atual != NULL) {
        if (atual->numSerie == novoNum) {
            duplicado = true;
            return total;// Se existir, não insere e devolve o total atual
        }
        total++;
        atual = atual->anterior;
    }

    // Alocação dinâmica do novo chassis
    // Melhor: Não viola SOLID: entrar já um Chassis
    Chassis* novoChassis = (Chassis*)malloc(sizeof(Chassis));
    if (novoChassis == NULL) return total;

    novoChassis->numSerie = novoNum;
    novoChassis->anterior = linha->topoEntrada; // Empurra o anterior para trás
    linha->topoEntrada = novoChassis;           // Assume o topo da linha
    total++;

    return total;
}


/*!
 *  c) Remover um chassis. Manter a ordem da stack
 *
 *      @param [in,out] linhaOriginal 
 *      @param [in]     alvoNum       
 *
 *      @return 
 */
bool RemoverChassis(LinhaPintura* linhaOriginal, int alvoNum) {
    LinhaPintura linhaAuxiliar;
    linhaAuxiliar.topoEntrada = NULL; //para guardar temporariamente
    bool encontrado = false;

    // Passo 1: Transferir os elementos até expor o alvo no topo original
    while (linhaOriginal->topoEntrada != NULL) {
        if (linhaOriginal->topoEntrada->numSerie == alvoNum) {
            encontrado = true;
            break;
        }
        Chassis* temp = linhaOriginal->topoEntrada;
        linhaOriginal->topoEntrada = temp->anterior;

        temp->anterior = linhaAuxiliar.topoEntrada;
        linhaAuxiliar.topoEntrada = temp;
    }

    // Passo 2: Se foi localizado, remove e liberta a memória
    if (encontrado) {
        Chassis* aRemover = linhaOriginal->topoEntrada;
        linhaOriginal->topoEntrada = aRemover->anterior;
        free(aRemover);
    }

    // Passo 3: Repor todos os chassis retirados temporariamente na ordem correta
    while (linhaAuxiliar.topoEntrada != NULL) {
        Chassis* repor = linhaAuxiliar.topoEntrada;
        linhaAuxiliar.topoEntrada = repor->anterior;

        repor->anterior = linhaOriginal->topoEntrada;
        linhaOriginal->topoEntrada = repor;
    }

    return encontrado;
}
