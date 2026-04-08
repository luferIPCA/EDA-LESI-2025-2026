
#include "Dados.h"



Node* CriarNodo(int valor) {
    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo == NULL) return NULL; // Falha na alocação
    novo->data = valor;
    novo->prev = NULL;
    novo->next = NULL;
    return novo;
}

/**
 * Insere um nó ainda não existente numa lista duplamente, de forma ordenada.
 */
Node* InserirOrdenado(Node* head, Node* novoNo, bool* sucesso) {
    // Se o nó passado for inválido, sinaliza falha
    if (novoNo == NULL) {
        if (sucesso) *sucesso = false;
        return head;
    }

    // Garante que o novo nó esteja isolado antes de inserir
    novoNo->next = NULL;
    novoNo->prev = NULL;

    // H1: Lista vazia ou novo nó deve ser a nova Head da lista
    if (head == NULL || head->data >= novoNo->data) {
        novoNo->next = head;
        if (head != NULL) {
            head->prev = novoNo;
        }
        if (sucesso) *sucesso = true;
        return novoNo;
    }

    // H2: Percorrer para encontrar a posição correta
    Node* atual = head;
    while (atual->next != NULL && atual->next->data < novoNo->data) {
        atual = atual->next;
    }

    // Ajuste os apontadores para inserção (Meio ou Fim)
    novoNo->next = atual->next;
    novoNo->prev = atual;

    if (atual->next != NULL) {
        atual->next->prev = novoNo;
    }
    atual->next = novoNo;

    if (sucesso) *sucesso = true;
    return head;
}


#pragma region LISTA_CONTROLADA

/**
 * Insere ordenado
 */
List* InserirOrdenadoControlado(List* lista, Node* novoNo, bool* sucesso) {
    // Validação básica
    if (lista == NULL || novoNo == NULL) {
        if (sucesso) *sucesso = false;
        return lista;
    }

    // Garante que o nó está isolado
    novoNo->next = NULL;
    novoNo->prev = NULL;

    // h1: Lista vazia ou inserção no início
    if (lista->head == NULL || lista->head->data >= novoNo->data) {
        novoNo->next = lista->head;
        if (lista->head != NULL) {
            lista->head->prev = novoNo;
        }
        lista->head = novoNo;
    }
    else {
        // h2: Percorrer para encontrar a posição
        Node* atual = lista->head;
        while (atual->next != NULL && atual->next->data < novoNo->data) {
            atual = atual->next;
        }

        // Inserção entre 'atual' e 'atual->next'
        novoNo->next = atual->next;
        novoNo->prev = atual;

        if (atual->next != NULL) {
            atual->next->prev = novoNo;
        }
        atual->next = novoNo;
    }

    // Atualiza header (metadados)
    lista->totalNodes++;
    if (sucesso) *sucesso = true;

    return lista;
}


/**
 * Insere um nodo de forma ordenada.
 * Atualiza head, tail e toalNodes.
 */
List* InserirOrdenadoControladoTail(List* lista, Node* novoNo, bool* sucesso) {
    if (lista == NULL || novoNo == NULL) {
        if (sucesso) *sucesso = false;
        return lista;
    }

    // Isolar o nó antes da inserção
    novoNo->next = NULL;
    novoNo->prev = NULL;

    // h1: Lista vazia
    if (lista->head == NULL) {
        lista->head = novoNo;
        lista->tail = novoNo;
    }
    // h2: Inserção no início (novoNo é o menor)
    else if (novoNo->data <= lista->head->data) {
        novoNo->next = lista->head;
        lista->head->prev = novoNo;
        lista->head = novoNo;
    }
    // h3: Inserção no fim (novoNo é maior ou igual ao tail)
    else if (novoNo->data >= lista->tail->data) {
        novoNo->prev = lista->tail;
        lista->tail->next = novoNo;
        lista->tail = novoNo;
    }
    // h4: Inserção no meio
    else {
        Node* atual = lista->head;
        while (atual->next != NULL && atual->next->data < novoNo->data) {
            atual = atual->next;
        }

        novoNo->next = atual->next;
        novoNo->prev = atual;
        if (atual->next != NULL) {
            atual->next->prev = novoNo;
        }
        atual->next = novoNo;
    }

    lista->totalNodes++;
    if (sucesso) *sucesso = true;
    return lista;
}

/**
 * Mostra a lista por ordem inversa (do fim para o início).
 */
bool MostrarInverso(List* lista) {
    if (lista == NULL || lista->tail == NULL) {
        return false;
    }

    Node* atual = lista->tail; // Começa no fim
    int aux = lista->totalNodes-1;
    while (atual != NULL) {
        printf("Pos %d = %d\n", aux, atual->data);
        atual = atual->prev; // Move-se para o anterior
        aux--;
    }
    return true;
}

#pragma endregion