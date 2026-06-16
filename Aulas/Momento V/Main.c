/*!
 * EDA - 2025-2026
*  @file main.c
 *  @author mustl
 *  @date 2026-06-03
 *  @project Momento V
 *
 *  Demonstrar 4
 */
#include "Dados.h"

int main() {
    // 1. Criar e inicializar a Hash
    SistemaCartoes complexoDesportivo;
    for (int i = 0; i < TAMTABELA; i++) {
        complexoDesportivo.corredor[i] = NULL;
    }

    // 2. Inserir dados fictícios de teste
    //int suc=
    InserirNoSistema(&complexoDesportivo, "SOC-4512B", 104, "Carlos Silva");
    InserirNoSistema(&complexoDesportivo, "SOC-9911A", 215, "Ana Rodrigues");

    // 3. Testar a função de Gravação em ficheiro
    if (GuardarSistemaFicheiro(&complexoDesportivo, "cacifos.dat")) {
        printf("Sucesso: Dados dos cacifos preservados em disco.\n");
    }
    else {
        printf("Erro ao guardar dados.\n");
    }

    // 4. Criar uma nova instância vazia para testar o Carregamento)
    SistemaCartoes sistemaRestaurado;
    if (CarregarSistemaFicheiro(&sistemaRestaurado, "cacifos.dat")) {
        printf("Sucesso: Dados carregados de disco e Hash reconstruida em RAM.\n");

        // Pequena verificação visual de teste para o primeiro slot que tenha dados
        for (int i = 0; i < TAMTABELA; i++) {
            if (sistemaRestaurado.corredor[i] != NULL) {
                printf("Cartao Lido: %s -> Cacifo: %d (Utente: %s)\n",
                    sistemaRestaurado.corredor[i]->codigoCartao,
                    sistemaRestaurado.corredor[i]->numeroCacifo,
                    sistemaRestaurado.corredor[i]->nomeUtente);
                break;
            }
        }
    }
    else {
        printf("Erro ao carregar dados do ficheiro.\n");
    }

    return 0;
}