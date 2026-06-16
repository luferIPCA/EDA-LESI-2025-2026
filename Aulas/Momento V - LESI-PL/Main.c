/*!
 * EDA - 2025-2026
*  @file Main.c
 *  @author mustl
 *  @date 2026-06-08
 *  @project Momento V - LESI-PL
 *
 *  Main (Questão 4 c)
 */
#include "Dados.h"
#include <stdio.h>

int main() {
    SistemaBancario bancoOriginal;
    // Inicialização da Hash
    for (int i = 0; i < TAMTABELA; i++) 
        bancoOriginal.tabelaTerminais[i] = NULL;

    // Inserção manual de dados para teste
    bool aux = false;
    aux=inserirNoSistemaParaCarregamento(&bancoOriginal, "ATM-PT-01", "Lisboa", 45000);
    if (!aux) return 0;
    aux=inserirNoSistemaParaCarregamento(&bancoOriginal, "ATM-PT-02", "Porto", 12500);
    if (!aux) return 0;

    // Guardar dados
    if (guardarSistemaBancario(&bancoOriginal, "dadosATM.dat")) {
        printf("Sucesso\n");
    }

    // Carregar dados do ficheiro
    SistemaBancario bancoRecuperado;
    if (carregarSistemaBancario(&bancoRecuperado, "dadosATM.dat")) {
        printf("Sucesso\n");
    }

    return 0;
}
