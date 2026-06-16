/*!
 * EDA - 2025-2026
*  @file smartfactory.c
 *  @author mustl
 *  @date 2026-04-39
 *  @project Momento III
 *
 *      Implementação
 */

#include "SmartFactory.h"

int Inicializar(HashTable* ht) {
    if (!ht) return 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->linhas[i] = NULL;
    }
    ht->inventario = NULL;
    return 1;
}

int Inserir(HashTable* ht, int produtoID, Maquina m) {
    if (!ht || produtoID < 0 || produtoID >= TABLE_SIZE) return 0;

    //hash indexada pelo produtoId
    ListaMaquinas* atual = ht->linhas[produtoID];

    // Procura o fim e verifica duplicados
    while (atual != NULL) {
        if (atual->maquina.num == m.num) return 0; // Erro: Código repetido
        atual = atual->prox;
    }
    // 1. Criar a máquina na memória (Dinâmica para ser apontada pela ABP e Lista)
    ListaMaquinas* novo = (ListaMaquinas*)malloc(sizeof(ListaMaquinas));
    if (!novo) return 0; // Falha de memória!!!
    novo->maquina = m;
    novo->prox = NULL;

    // Caso se considere a ABP
    // 2. Tentar inserir na ABP (Inventário Global)
    // Passamos o endereço da máquina que está dentro do nó da lista
    //if (inserirNaABP(ht->inventario, novo->maquina)) {
    //    ht->linhas[produtoID] = novo; // Só insere na linha se for única na fábrica
    //    return 1;
    //}
    //free(novo); // Se já existia no inventário, aborta inserção
    return 1;
}

/*!
 *  2 b) - Pode ter outra implementação
 *
 *      @param [in,out] ht        
 *      @param [in]     produtoID 
 *
 *      @return 
 */
float VerificarLinha(HashTable* ht, int produtoID) {
    if (!ht || produtoID < 0 || produtoID >= TABLE_SIZE || ht->linhas[produtoID] == NULL)
        return 0;
    ListaMaquinas *aux = ht->linhas[produtoID];
    double tempoTotal = 0;
    
    while (aux != NULL) {
        //debug: printf(" -> [%d] : tempo: %0,2f\n", aux->maquina.num, aux->maquina.tempo);
        if (aux->maquina.estado == 0) {
            //debug: printf("\tMaquina %d AVARIADA\n", aux->maquina.num);
            continue;
        }
        else {      
            tempoTotal += aux->maquina.tempo;
        }
        aux = aux->prox;
    }
    
    return tempoTotal;
}

int AtualizarMaquina(HashTable* ht, int numAntigo, Maquina nova) {
    if (!ht) return 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ListaMaquinas *aux = ht->linhas[i];
        while (aux != NULL) {
            if (aux->maquina.num == numAntigo) {
                aux->maquina = nova;
                return 1; // Sucesso na substituição
            }
            aux = aux->prox;
        }
    }
    return 0; // Máquina não encontrada em nenhuma linha
}

int GravarDados(HashTable* ht, const char* nomeFicheiro) {
    if (!ht) return 0;
    FILE* f = fopen(nomeFicheiro, "wb");
    if (!f) return 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        ListaMaquinas *aux = ht->linhas[i];
        while (aux != NULL) {
            //ou criar uma struct para ficheiro sem apontadores
            fwrite(&i, sizeof(int), 1, f);
            fwrite(&(aux->maquina), sizeof(Maquina), 1, f);
            aux = aux->prox;
        }
    }
    fclose(f);
    return 1;
}

int CarregarDados(HashTable* ht, const char* nomeFicheiro) {
    if (!ht) return 0;
    FILE* f = fopen(nomeFicheiro, "rb");
    if (!f) return 0;

    int produtoID;
    int r;
    Maquina m;
    while (fread(&produtoID, sizeof(int), 1, f) && fread(&m, sizeof(Maquina), 1, f)) {
        r=Inserir(ht, produtoID, m);
        if (r == 0) return 0;
    }
    fclose(f);
    return 1;
}

