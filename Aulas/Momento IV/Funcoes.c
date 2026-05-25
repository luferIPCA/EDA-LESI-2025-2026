/*!
 * EDA - 2025-2026
*  @file Funcoes.c
 *  @author mustl
 *  @date 2026-05-21
 *  @project Momento IV
 *
 *  Resolução Momento de Avaliação IV.
 */
#include "Dados.h"

/*
* a)
* Inserir no Fim: Queue
Respeita SOLID?
*/
Componente* RegistarComponente(Componente* cabeca, Componente* novo) {
 
    if (cabeca == NULL) {
        cabeca = novo;
    }
    else {
        Componente* aux = cabeca;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo; // Inserção no fim garante a política de uma Queue: FIFO
    }
    return true;
}

/*
b) Procura numa árvore binárida de procura
*/
int VerificarQualidade(LogQualidade* raiz, int idProcurado) {
    if (raiz == NULL) return -1;
    if (raiz->idComponente == idProcurado) {
        return raiz->aprovado ? 1 : 0; // 1 = Aprovado, 0 = Rejeitado
        if (idProcurado < raiz->idComponente) {
            return VerificarQualidade(raiz->esquerda, idProcurado);
        }
        else {
            return VerificarQualidade(raiz->direita, idProcurado);
        }
    }
}

/*
Alinea C
Lida com uma Hash
*/
int CalcularIndiceHash(char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAMANHO_HASH; // Condicionado ao tamanho do array da hash
}

int LocalizarPostoFerramenta(ElementoHash* tabela[], char* codigoProcurado) {
    int indice = CalcularIndiceHash(codigoProcurado);
    ElementoHash* atual = tabela[indice];
    while (atual != NULL) {
        int i = 0;
        bool iguais = true;
        //Podia usar função que procura numa Lista
        while (codigoProcurado[i] != '\0' || atual->codigoFerramenta[i] != '\0') {
            if (codigoProcurado[i] != atual->codigoFerramenta[i]) {
                iguais = false;
                break;
            }
            i++;
        }
        if (iguais) return atual->idPosto; // Sucesso: Devolve o ID do Posto
        atual = atual->prox; // Avança na lista de colisões
    }
    return -1; // Ferramenta não exsite
}

/*
Alinea d)
Grafo com a estrutura da Facbrica
*/
bool MostrarPostosAlcancaveis(GrafoFabrica* g, int idInicio) {
    if (!g || idInicio < 0 || idInicio >= g->totalPostos) return false;

    bool* visitados = (bool*)malloc(g->totalPostos* sizeof(bool));
    int* fila = (int*)malloc(g->totalPostos * sizeof(int));
    int frente = 0, tras = 0;
    if (!visitados || !fila) return false;
    visitados[idInicio] = true;
    fila[tras++] = idInicio;

    printf("Postos : ");
    while (frente < tras) {
        int u = fila[frente++];
        printf("%d ", u);
        AdjListNode* aux = g->arrayPostos[u].head;
        while (aux != NULL) {
            if (!visitados[aux->idPostoDestino]) {
                visitados[aux->idPostoDestino] = true; // Impede ciclos infinitos
                fila[tras++] = aux->idPostoDestino;
            }
            aux = aux->next;
        }
    }
    printf("\n");
    free(visitados); free(fila);
    return true;
}

/*
ALinea e)
*/
bool DeterminarRotaDijkstra(GrafoFabrica* g, int origem, int destino) {
    float* dist = (float*)malloc(g->totalPostos * sizeof(float));
    int* prev = (int*)malloc(g->totalPostos * sizeof(int));
    bool* visitados = (bool*)malloc(g->totalPostos* sizeof(bool));
    if (!visitados || !dist) return false;

    //iniciazar
    for (int i = 0; i < g->totalPostos; i++) {
        dist[i] = -1.0f; // só para controlo
        prev[i] = -1;
    }

    dist[origem] = 0.0f;
    for (int count = 0; count < g->totalPostos - 1; count++) {
        int u = -1;
        float min = -1;

        for (int v = 0; v < g->totalPostos; v++) {
            if (!visitados[v] && dist[v] < min) {
                min = dist[v];
                u = v;
            }
        }
        if (u == -1 || u == destino) break;
        visitados[u] = true;
        // Relaxamento de arestas vizinhas
        AdjListNode* aux = g->arrayPostos[u].head;
        while (aux != NULL) {
            int v = aux->idPostoDestino;
            if (!visitados[v] && dist[u] + aux->distanciaMetros < dist[v]) {
                dist[v] = dist[u] + aux->distanciaMetros;
                prev[v] = u;
            }
            aux = aux->next;
        }
    }

    // Output sequencial 
    printf("Sequencia de Postos (destino para origem): %d", destino);
    int curr = prev[destino];
    while (curr != -1) {
        printf(" <- %d", curr);
        curr = prev[curr];
    }
    printf("\n");

    free(dist); free(prev); free(visitados);
}

/*
Alinea f
*/
GrafoFabrica* CriarGrafoBase(int total) {
    GrafoFabrica* g = (GrafoFabrica*)malloc(sizeof(GrafoFabrica));
    if (!g) return NULL;
    g->totalPostos = total;

    //Conjunto de vértices (postos)
    g->arrayPostos = (PostoTrabalho*)malloc(total * sizeof(PostoTrabalho));
    for (int i = 0; i < total; i++) {
        g->arrayPostos[i].idPosto = i;
        g->arrayPostos[i].head = NULL;
    }
    return g;
}

bool AdicionarAresta(GrafoFabrica* g, int src, int dest, float dist) {
    AdjListNode* novo = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (!novo) return false;
    novo->idPostoDestino = dest;
    novo->distanciaMetros = dist;
    novo->next = g->arrayPostos[src].head;
    //insere à cabeça
    g->arrayPostos[src].head = novo;
    return true;
}

/*
Ficheiro terá:
-------------
totalVertices
-------------
origem;destino;distancia
origem;destino;distancia
origem;destino;distancia

*/
GrafoFabrica* CarregarDadosInfraestrutura(char* nomeFicheiro) {
    FILE* fp = fopen(nomeFicheiro, "r");
    if (!fp) return NULL;

    int totalPostos = 0;
    int c;

    // 1. Ler cabeçalho (número total de postos) até '\n'
    while ((c = fgetc(fp)) != EOF && c != '\n') {
        if (c >= '0' && c <= '9') {
            totalPostos = totalPostos * 10 + (c - '0');
        }
    }

    if (totalPostos <= 0) { fclose(fp); return NULL; }
    GrafoFabrica* g = CriarGrafoBase(totalPostos);

    // 2. Processamento por delimitadores: origem;destino;distancia
    while (true) {
        int origem = 0, destino = 0;
        float distancia = 0.0, fator_decimal = 0.1;
        bool algarismo_decimal = false;

        // Ler ID da Origem
        while ((c = fgetc(fp)) != EOF && c != ';') {
            if (c >= '0' && c <= '9') origem = origem * 10 + (c - '0');
        }
        if (c == EOF) break;

        // Ler ID do Destino
        while ((c = fgetc(fp)) != EOF && c != ';') {
            if (c >= '0' && c <= '9') destino = destino * 10 + (c - '0');
        }

        // Ler Distância (float)
        while ((c = fgetc(fp)) != EOF && c != '\n') {
            if (c >= '0' && c <= '9') {
                if (!algarismo_decimal) {
                    distancia = distancia * 10 + (c - '0');
                }
                else {
                    distancia += (c - '0') * fator_decimal;
                    fator_decimal /= 10;
                }
            }
            else if (c == '.' || c == ',') {
                algarismo_decimal = true;
            }
        }

        if (origem < totalPostos && destino < totalPostos) {
            AdicionarAresta(g, origem, destino, distancia);
        }

        if (c == EOF) break;
    }

    fclose(fp);
    return g;
}


