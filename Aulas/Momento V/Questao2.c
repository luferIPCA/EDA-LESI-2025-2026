/*!
 * EDA - 2025-2026
*  @file Questao2.c
 *  @author mustl
 *  @date 2026-06-03
 *  @project Momento V
 *
 *  Implements Questao 2
 */
#include "Dados.h"


/*!
 *  Função de hash.
 *
 *      @param [in,out] chave 
 *
 *      @return 
 */
int IndiceHash(char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAMTABELA;
}

// Função Auxiliar para inserir na RAM durante o carregamento de ficheiro
bool InserirNoSistema(SistemaCartoes* sistema, char* cod, int cacifo, char* nome) {
    //testes para return false
    int idx = IndiceHash(cod);
    Cacifo* novo = (Cacifo*)malloc(sizeof(Cacifo));
    if (novo == NULL) return;

    strcpy(novo->codigoCartao, cod);
    novo->numeroCacifo = cacifo;
    strcpy(novo->nomeUtente, nome);
    novo->proximo = sistema->corredor[idx]; // Insere à cabeça no slot correspondente
    sistema->corredor[idx] = novo;
    return true;
}

/*!
 *  b) Localizar cacifo.
 *
 *      @param [in,out] sistema     
 *      @param [in,out] codigo      //codigo do cacifo
 *      @param [in,out] nomeUtente 
 *
 *      @return 
 */
int LocalizarCacifo(SistemaCartoes* sistema, char* codigo, char* nomeUtente) {
    // 1. Calcular a entrada direta na tabela
    int indice = IndiceHash(codigo);

    // 2. Apontar para o início da lista de colisões desse slot
    Cacifo* atual = sistema->corredor[indice];

    // 3. Percorrer a lista ligada associada ao slot
    while (atual != NULL) {
        if (strcmp(atual->codigoCartao, codigo) == 0) {
            strcpy(nomeUtente, atual->nomeUtente); //devolve o nome do utente
            return atual->numeroCacifo;           // devolve o código do cacifo
        }
        atual = atual->proximo;
    }

    return -1; // Não encontrado
}
