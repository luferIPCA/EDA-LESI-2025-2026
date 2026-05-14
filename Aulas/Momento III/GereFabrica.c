/*!
 * EDA - 2025-2026
*  @file GereFabrica.c
 *  @author mustl
 *  @date 2026-04-30
 *  @project Momento III
 *
 *  Gere fabrica.
 */
#include "SmartFactory.h"

int main() {
    
    HashTable fabrica;
    //ou
    //HashTable *fabrica;

    if (!Inicializar(&fabrica)) {
        printf("Erro ao inicializar a fábrica.\n");
        return 1;
    }

    Maquina m1 = { 701, 10.5, 1 };

    if (Inserir(&fabrica, 5, m1)) {
        printf("Maquina inserida com sucesso na linha 5.\n");
    }
    else {
        printf("Falha ao inserir maquina (ID duplicado ou Linha invalida).\n");
    }

    if (!VerificarLinha(&fabrica, 5)) {
        printf("Linha 5 vazia ou inexistente.\n");
    }

    printf("\n--- Inventario Global Ordenado (ABP) ---\n");
    ListarInventarioOrdenado(fabrica.inventario);

    if (GravarDados(&fabrica, "backup.dat")) {
        printf("Dados preservados no disco.\n");
    }

    return 0;
}