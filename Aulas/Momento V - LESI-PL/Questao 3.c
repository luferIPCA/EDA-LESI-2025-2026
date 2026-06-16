/*!
 * EDA - 2025-2026
*  @file Questao 3.c
 *  @author mustl
 *  @date 2026-06-08
 *  @project Momento V - LESI-PL
 *
 *  Implement Questao 3
 */

#include "Dados.h"

/*!
 *  Calcula indice hash.
 *
 *      @param [in,out] codigo 
 *
 *      @return 
 */
int calcularIndiceHash(char* codigo) {
    int soma = 0;
    for (int i = 0; codigo[i] != '\0'; i++) soma += codigo[i];
    return soma % TAMTABELA;
}

/*!
 *  Função de consulta do terminal com múltiplos retornos
 *
 *      @param [in,out] sistema         
 *      @param [in,out] codigoProcurado 
 *      @param [in,out] cidadeDestino   
 *      @param [in,out] saldoDestino    
 *
 *      @return 
 */
int consultarTerminal(SistemaBancario* sistema, char* codigoProcurado, char* cidadeDestino, int* saldoDestino) {
    // 1. Obter ínidice da Hash
    int indice = calcularIndiceHash(codigoProcurado);

    // 2. Apontar para o início da lista de colisões
    NoATM* atual = sistema->tabelaTerminais[indice];

    // 3. Percorrer a lista à procura do código correspondente
    while (atual != NULL) {
        if (strcmp(atual->codigoTerminal, codigoProcurado) == 0) {
            strcpy(cidadeDestino, atual->cidade); // Passa a cidade por referência
            *saldoDestino = atual->saldoDisponivel; // Passa o saldo por referência
            return 1; // Sucesso (Qualquer valor diferente de -1 indica registo válido)
        }
        atual = atual->proximo;
    }

    return -1; // Não correu bem!
}

/*!
 *  Inserir ATM no sistema .
 *
 *      @param [in,out] sistema
 *      @param [in,out] cod
 *      @param [in,out] cid
 *      @param [in]     saldo
 */
     bool inserirNoSistemaParaCarregamento(SistemaBancario * sistema, char* cod, char* cid, int saldo) {
     int idx = calcularIndiceHash(cod);
     NoATM* novo = (NoATM*)malloc(sizeof(NoATM));
     if (novo == NULL) return false;
     strcpy(novo->codigoTerminal, cod);
     strcpy(novo->cidade, cid);
     novo->saldoDisponivel = saldo;
     novo->proximo = sistema->tabelaTerminais[idx];
     sistema->tabelaTerminais[idx] = novo;
     return true;
 }
