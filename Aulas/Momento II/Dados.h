/*!
 * EDA - 2025-2026
*  @file Dados.h
 *  @author mustl
 *  @date 2026-06-16
 *  @project Momento II
 *
 *  Declarar dados.
 */

#pragma once

/* Questão 1
	FIFO - Queue

*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXID 20
#define MAXMORADA 100
#define MAXNOME 50

// Pedido de entrega
typedef struct {
    char id[MAXID];           // identificador único do pedido
    char morada[MAXMORADA];   // destino da entrega
    char cliente[MAXNOME];    // nome do cliente
    float peso;               // peso da encomenda (kg)
    int prioridade;           // ex: 1-normal, 2-urgente
} Pedido;

// Nodo da lista ligada
typedef struct NoPedido {
    Pedido pedido;
    struct NoPedido* proximo;
} NoPedido;

// Fila (Queue) — gestão FIFO dos pedidos
typedef struct {
    NoPedido* inicio;   // próximo a ser processado
    NoPedido* fim;      // último a entrar
    int total;          // número de pedidos em fila
} FilaPedidos;


//alinea 2
//Lista Ligada

// Nodo do histórico
typedef struct NoHistorico {
    Pedido pedido;
    struct NoHistorico* proximo;
} NoHistorico;

// Histórico
typedef struct {
    NoHistorico* inicio;
    int total;
} Historico;


//Questão 3
//Estrutura de Daos que agrupe múltiplas filas, uma por empresa
//Lista ligada de empresas, cada uma com a sua própria FilaPedidos :
#define MAXEMPRESA 50

// Entidade Empresa
typedef struct NoEmpresa {
    char nome[MAXEMPRESA];
    FilaPedidos fila;           // cada empresa tem a sua fila de pedidos
    struct NoEmpresa* proxima;
} NoEmpresa;

// Lista de empresas
typedef struct {
    NoEmpresa* inicio;
    int total;
} ListaEmpresas;
