/*!
 * EDA - 2025-2026
*  @file Questao 4.c
 *  @author mustl
 *  @date 2026-06-08
 *  @project Momento V - LESI-PL
 *
 *  Implementa Questao 4
 */

#include "Dados.h"
#include <stdio.h>

/*!
 *  Guarda toda a informação da Tabela de Hash em Ficheiro Binário
 *
 *      @param [in,out] sistema      
 *      @param [in,out] nomeFicheiro 
 *
 *      @return 
 */
bool guardarSistemaBancario(SistemaBancario* sistema, char* nomeFicheiro) {
    FILE* f = fopen(nomeFicheiro, "wb");
    if (f == NULL) return false;

    // Percorrer obrigatoriamente toda a Hash
    for (int i = 0; i < TAMTABELA; i++) {
        NoATM* atual = sistema->tabelaTerminais[i];
        // Percorrer a lista ligada 
        while (atual != NULL) {
            DadosATM aux;
            strcpy(aux.codigoTerminal, atual->codigoTerminal);
            strcpy(aux.cidade, atual->cidade);
            aux.saldoDisponivel = atual->saldoDisponivel;
            //escreve no ficheiro
            fwrite(&aux, sizeof(DadosATM), 1, f);
            atual = atual->proximo;
        }
    }
    fclose(f);
    return true;
}


/*!
 *  Carregar toda a informação guardada no ficheiro
 *
 *      @param [in,out] sistema      
 *      @param [in,out] nomeFicheiro 
 *
 *      @return 
 */
bool carregarSistemaBancario(SistemaBancario* sistema, char* nomeFicheiro) {
    FILE* f = fopen(nomeFicheiro, "rb");
    if (f == NULL) return false;

    // Inicializar a hash
    for (int i = 0; i < TAMTABELA; i++) {
        sistema->tabelaTerminais[i] = NULL;
    }

    DadosATM lido;
    // Ler registos do ficheiros
    bool aux = false;
    while (fread(&lido, sizeof(DadosATM), 1, f) == 1) {
        aux = inserirNoSistemaParaCarregamento(sistema, lido.codigoTerminal, lido.cidade, lido.saldoDisponivel);
        if (aux == false) {
            return false;
        }
    }

    fclose(f);
    return true;
}
