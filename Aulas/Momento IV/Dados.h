/*!
 * EDA - 2025-2026
*  @file Dados.h
 *  @author mustl
 *  @date 2026-05-21
 *  @project Momento IV
 *
 *  Declaração the dados.
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZENAME 50
#define TAMANHO_HASH 101

 // ============================================================================
 // R1: PASSADEIRA DE TRIAGEM (Fila / Lista Ligada Simples)
 // ============================================================================
typedef struct Componente {
    int idComponente;              // ID único
    char nome[SIZENAME];
    struct Componente* prox;
} Componente;

// ============================================================================
// R2: ARQUIVO DE LOGS DE QUALIDADE (BST - Árvore Binária de Procura)
// ============================================================================
typedef struct LogQualidade {
    int idComponente;              // ID único
    bool aprovado;                 // true = Aprovado, false = Rejeitado
    struct LogQualidade* esquerda;
    struct LogQualidade* direita;
} LogQualidade;

// ============================================================================
// R3: LOCALIZADOR DE FERRAMENTAS (Tabela de Hash)
// ============================================================================
typedef struct ElementoHash {
    char codigoFerramenta[SIZENAME]; // Para a chave hash
    int idPosto;                     // ID único (Onde a ferramenta está)
    struct ElementoHash* prox;       // Resolução de colisões
} ElementoHash;

// ============================================================================
// R4: INFRAESTRUTURA FÍSICA (Grafo por Lista de Adjacências)
// ============================================================================
typedef struct AdjListNode {
    int idPostoDestino;            // ID único (Posto destino)
    float distanciaMetros;
    struct AdjListNode* next;
} AdjListNode;

typedef struct PostoTrabalho {
    int idPosto;                   // ID único
    char nomePosto[SIZENAME];
    AdjListNode* head;             // Cabeça da lista de adjacentes  (arestas)
} PostoTrabalho;

typedef struct GrafoFabrica {
    int totalPostos;
    PostoTrabalho* arrayPostos;    // Array de postos (vertices)
} GrafoFabrica;

