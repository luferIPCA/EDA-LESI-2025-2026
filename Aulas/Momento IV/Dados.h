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

 
 // R1: TRIAGEM (Fila / Lista Ligada Simples)
typedef struct Componente {
    int idComponente;              // ID único
    char nome[SIZENAME];
    struct Componente* prox;
} Componente;


// R2: ARQUIVO DE LOGS DE QUALIDADE (BST - Árvore Binária de Procura)
typedef struct LogQualidade LogQualidade;
struct LogQualidade {
    int idComponente;              // ID único
    bool aprovado;                 // true = Aprovado, false = Rejeitado
    LogQualidade* esquerda;
    LogQualidade* direita;
};

// R3: LOCALIZADOR DE FERRAMENTAS (Tabela de Hash)
typedef struct ElementoHash ElementoHash;
struct ElementoHash {
    char codigoFerramenta[SIZENAME]; // Para a chave hash
    int idPosto;                     // ID único (Onde a ferramenta está)
    ElementoHash* prox;       // Resolução de colisões
};

// R4: INFRAESTRUTURA FÍSICA (Grafo por Lista de Adjacências)
typedef struct AdjListNode AdjListNode;

struct AdjListNode {
    int idPostoDestino;            // ID único (Posto destino)
    float distanciaMetros;
    AdjListNode* next;
};

typedef struct PostoTrabalho PostoTrabalho;
struct PostoTrabalho {
    int idPosto;                   // ID único
    char nomePosto[SIZENAME];
    AdjListNode* head;             // Cabeça da lista de adjacentes  (arestas)
};

typedef struct GrafoFabrica {
    int totalPostos;
    PostoTrabalho* arrayPostos;    // Array vertices
} GrafoFabrica;

