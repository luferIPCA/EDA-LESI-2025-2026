/*!
 * EDA - 2025-2026
*  @file Questao 1.c
 *  @author mustl
 *  @date 2026-06-08
 *  @project Momento V - LESI-PL
 *
 *  Implementa a Questao 1
 */

#include "Dados.h"

/*!
 *  cálculo do total de vezes que o artista foi ouvido
 *
 *      @param [in,out] raiz        
 *      @param [in,out] nomeAlvo    
 *      @param [in,out] totalOuvido 
 *
 *      @return 
 */
bool calcularTotalReproducoes(Artista* raiz, char* nomeAlvo, int* totalOuvido) {
    if (raiz == NULL) {
        return false; // Artista não consta no catálogo
    }

    int comp = strcmp(nomeAlvo, raiz->nomeArtista);

    // Artista localizado árove!
    if (comp == 0) {
        int somatorioPlays = 0;
        Musica* musicaAtual = raiz->listaMusicas;

        // Percorre o conjunto de músicas acumulando os valores
        while (musicaAtual != NULL) {
            somatorioPlays += musicaAtual->reproducoes;
            musicaAtual = musicaAtual->seguinte;
        }

        *totalOuvido = somatorioPlays; 
        return true;                   
    }

    // Recursividade para procurar no resto da árvore
    if (comp < 0) {
        return calcularTotalReproducoes(raiz->esquerda, nomeAlvo, totalOuvido);
    }
    else {
        return calcularTotalReproducoes(raiz->direita, nomeAlvo, totalOuvido);
    }
}

