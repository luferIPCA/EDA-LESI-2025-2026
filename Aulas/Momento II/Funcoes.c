#pragma once

#include "Dados.h"

/*!
 *  2a - Enqueue — insere no fim da fila
 *
 *      @param [in,out] fila 
 *      @param [in]     p    
 *      @param [in,out] res  
 *
 *      @return 
 */
bool InserePedido(FilaPedidos* fila, Pedido p, bool* res) {
    *res = false;

    if (fila == NULL) return false;

    // Verificar pedido repetido (por id)
    NoPedido* ptr = fila->inicio;
    while (ptr != NULL) {
        if (strcmp(ptr->pedido.id, p.id) == 0) return false; // já existe
        ptr = ptr->proximo;
    }

    // Criar novo nodo
    NoPedido* novo = (NoPedido*)malloc(sizeof(NoPedido));
    if (novo == NULL) return false;

    novo->pedido = p;
    novo->proximo = NULL;

    // Inserir no fim
    if (fila->fim == NULL) {
        // Fila vazia
        fila->inicio = novo;
        fila->fim = novo;
    }
    else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }

    fila->total++;
    *res = true;
    return true;
}

/*!
 *  Processa pedido.
 *  Dequeue — remove do início e guarda no histórico
 *
 *      @param [in,out] fila 
 *      @param [in,out] hist 
 *
 *      @return 
 */
bool ProcessaPedido(FilaPedidos* fila, Historico* hist) {
    if (fila == NULL || hist == NULL) return false;
    if (fila->inicio == NULL) return false;  // fila vazia

    // Remover do início da fila
    NoPedido* removido = fila->inicio;
    fila->inicio = fila->inicio->proximo;

    if (fila->inicio == NULL) {
        fila->fim = NULL;  // fila ficou vazia
    }
    fila->total--;

    // Preservar no histórico
    NoHistorico* noHist = (NoHistorico*)malloc(sizeof(NoHistorico));
    if (noHist == NULL) {
        free(removido);
        return false;
    }
    // insere no início do histórico..mas pode ser ordenado!
    noHist->pedido = removido->pedido;
    noHist->proximo = hist->inicio;  
    hist->inicio = noHist;
    hist->total++;

    free(removido);
    return true;
}

/*!
 *  Guarda toda a informacao.
 *  Devia ser em ficheiros separados
 *
 *      @param [in,out] fila     
 *      @param [in,out] hist     
 *      @param [in,out] ficheiro 
 *
 *      @return 
 */
bool GuardaInformacao(FilaPedidos* fila, Historico* hist, char* ficheiro) {
    if (fila == NULL || hist == NULL || ficheiro == NULL) return false;

    FILE* f = fopen(ficheiro, "wb");
    if (f == NULL) return false;

    // Guardar Queue
    fwrite(&fila->total, sizeof(int), 1, f);
    NoPedido* ptr = fila->inicio;
    while (ptr != NULL) {
        fwrite(&ptr->pedido, sizeof(Pedido), 1, f);
        ptr = ptr->proximo;
    }

    // Guardar histórico
    fwrite(&hist->total, sizeof(int), 1, f);
    NoHistorico* ptrH = hist->inicio;
    while (ptrH != NULL) {
        fwrite(&ptrH->pedido, sizeof(Pedido), 1, f);
        ptrH = ptrH->proximo;
    }

    fclose(f);
    return true;
}
/*!
 *  Carregas toda a informacao.
 *  Devia ser em ficheiros separados
 *
 *      @param [in,out] fila     
 *      @param [in,out] hist     
 *      @param [in,out] ficheiro 
 *
 *      @return 
 */
bool CarregaInformacao(FilaPedidos* fila, Historico* hist, char* ficheiro) {
    if (fila == NULL || hist == NULL || ficheiro == NULL) return false;

    FILE* f = fopen(ficheiro, "rb");
    if (f == NULL) return false;

    // Carregar Queue
    int totalFila = 0;
    fread(&totalFila, sizeof(int), 1, f);
    bool r = false;
    for (int i = 0; i < totalFila; i++) {
        Pedido p;
        fread(&p, sizeof(Pedido), 1, f);
        bool res = false;
        r=InserePedido(fila, p, &res);
        if (r == false) break;
    }

    // Carregar histórico
    int totalHist = 0;
    fread(&totalHist, sizeof(int), 1, f);
    for (int i = 0; i < totalHist; i++) {
        Pedido p;
        fread(&p, sizeof(Pedido), 1, f);
        //Aqui era melhor chamar o método "InsereHistorico"
        NoHistorico* no = (NoHistorico*)malloc(sizeof(NoHistorico));
        if (no == NULL) { fclose(f); return false; }
        no->pedido = p;
        no->proximo = hist->inicio;
        hist->inicio = no;
        hist->total++;
    }

    fclose(f);
    return true;
}

//Questão 3

void MostraProximosPedidos(ListaEmpresas* lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("Não há empresas.\n");
        return;
    }

    NoEmpresa* ptr = lista->inicio;
    while (ptr != NULL) {
        printf("Empresa: %s\n", ptr->nome);

        if (ptr->fila.inicio == NULL) continue;
        else {
            // O próximo a processar é sempre o início da fila
            Pedido* p = &ptr->fila.inicio->pedido;
            printf("  Pedido: ID=%s | Cliente=%s | Morada=%s\n",
                p->id, p->cliente, p->morada);
        }
        ptr = ptr->proxima;
    }
}