/*!
 * EDA - 2025-2026
*  @file Questao4.c
 *  @author mustl
 *  @date 2026-06-03
 *  @project Momento V
 *
 *  Implementa a Questao 4
 */
#include "Dados.h"

//Cacifos Automatizados do Complexo Desportivo
//Tabela de Hash com tratamento de colisões com Lista Ligada.


/*!
 *  Guarda tudo em ficheiro
 *
 *      @param [in,out] sistema      
 *      @param [in,out] nomeFicheiro 
 *
 *      @return 
 */
bool GuardarSistemaFicheiro(SistemaCartoes* sistema, char* nomeFicheiro) {
    FILE* f = fopen(nomeFicheiro, "wb");
    if (f == NULL) return false;

    // Percorrer todos os corredores da Tabela de Hash
    for (int i = 0; i < TAMTABELA; i++) {
        Cacifo* atual = sistema->corredor[i];

        // Percorrer a lista ligada de colisões de cada corredor
        while (atual != NULL) {
            CacifoFicheiro aux;
            strcpy(aux.codigoCartao, atual->codigoCartao);
            aux.numeroCacifo = atual->numeroCacifo;
            strcpy(aux.nomeUtente, atual->nomeUtente);

            // Escrever o bloco de dados no ficheiro binário
            fwrite(&aux, sizeof(CacifoFicheiro), 1, f);

            atual = atual->proximo; 
        }
    }

    fclose(f);
    return true; // Feito!
}

/*!
 *  Carregae sistema do ficheiro.
 *
 *      @param [in,out] sistema      
 *      @param [in,out] nomeFicheiro 
 *
 *      @return 
 */
bool CarregarSistemaFicheiro(SistemaCartoes* sistema, char* nomeFicheiro) {
    FILE* f = fopen(nomeFicheiro, "rb");
    if (f == NULL) return false;

    // Inicializar a tabela de hash
    for (int i = 0; i < TAMTABELA; i++) {
        sistema->corredor[i] = NULL;
    }

    CacifoFicheiro aux;
    // Passo 2: Ler em bloco do ficheiro até chegar ao fim (EOF)
    int i;
    while (fread(&aux, sizeof(CacifoFicheiro), 1, f) == 1) {
        // Re-inserir dinamicamente gerando o novo índice e alocação em memória
        //Melhor código:  chamar aqui o metodo CriaCacifo(...)
        //Cacifo* novo = CriaCacifo(aux.codigoCartao, aux.numeroCacifo, aux.nomeUtente);
        //i= InserirNoSistema(sistema, novo);
        i=InserirNoSistema(sistema, aux.codigoCartao, aux.numeroCacifo, aux.nomeUtente);
        if (i == 0) return false;
    }

    fclose(f);
    return true; // Feito!
}
