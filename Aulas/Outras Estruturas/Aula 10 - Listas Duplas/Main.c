/*!
 * EDA - 2025-2026
*  @file Main.c
 *  @author mustl
 *  @date 2026-04-06
 *  @project Aula 9 - Listas Duplas
 *
 *  Implements the problem solution.
 */

#include "Dados.h"

int main() {

    Node* lista = NULL;
    bool ok;

    // Cria um nodo
    Node* n1 = CriarNodo(14);

    // Insere
    lista = InserirOrdenado(lista, n1, &ok);

    if (ok) {
        printf("Nodo %d inserido!\n", n1->data);
    }

    //NOTA: Alterar para evitar repetidos
    lista = InserirOrdenado(lista, n1, &ok);

    if (ok) {
        printf("Nodo %d inserido!\n", n1->data);
    }

#pragma region LISTA_CONTROLADA

    // Inicialização da lista (Header)
    List* listaHeader = (List*)malloc(sizeof(List));
    if (!listaHeader) return 0;
    listaHeader->head = NULL;
    listaHeader->totalNodes = 0;

    // Cria um nodo
    Node* n2 = CriarNodo(43);

    // Inserindo
    listaHeader = InserirOrdenadoControlado(listaHeader, n2, &ok);

    if (ok) {
        printf("Elemento inserido! Total de elementos: %d\n", listaHeader->totalNodes);
    }
#pragma endregion

#pragma region TAIL

    // Inicialização da Lista com tail
    List* lista3 = (List*)malloc(sizeof(List));
    if (!lista3) return 0;
    lista3->head = NULL;
    lista3->tail = NULL;
    lista3->totalNodes = 0;

    int valores[] = { 20, 5, 15, 10 };

    for (int i = 0; i < 4; i++) {
        Node* novo = CriarNodo(valores[i]);
        lista3 = InserirOrdenadoControladoTail(lista3, novo, &ok);
    }

    // Mostrar do fim para o início: 20 <-> 15 <-> 10 <-> 5
    printf("Lista (Inversa) [%d elementos]: \n", lista3->totalNodes);
    MostrarInverso(lista3);

#pragma endregion


    return 0;
}