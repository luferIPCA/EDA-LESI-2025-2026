/*!
 * EDA - 2025-2026
*  @file Main.c
 *  @author mustl
 *  @date 2026-06-16
 *  @project Momento I
 *
 *  Usa as funções
 */

#include "Dados.h"
#include "Funcoes.h"

int main() {
    int a = 10, b = 20;
    bool res=false;

    //Questão 1
    res = Atualiza(&a, &b, 5);

    if (res) {
        printf("a = %d, b = %d\n", a, b);
    }
    else {
        printf("Função não executada\n");
    }


    //Quesrão 2
    int v[] = { 4, 7, 12, 3, 8, 5, 10 };
    int total = 0;

    res = ContaPares(v, 7, 6, &total);

    if (res == false) printf("Array vazio inválido ou com tamanho incomportável\n");
    else printf("Total de pares > 6: %d\n", total);  // 3 (12, 8, 10)



    //Questão 3
    //b) Criar um carro
    Carro c1;
    if (!CriaFichaCarro(&c1, "AA-12-BB", "João Silva")) {
        printf("Erro ao criar carro\n");
        return 1;
    }
    //b) opção 2

    Carro* novo = CriaFichaCarroII("AA-12-BB", "João Silva", &res);
    if (res)
    {
        printf("Matricula: %s\n", novo->matricula);
        MostraCarro(novo);
    }

    // a) Apresentar informação
    if (MostraCarro(&c1) == -1) {
        printf("Dados de carro inválidos\n");
    }

    // c) Procurar condutor no parque
    Parque p;
    p.total = 0;

    // Adicionar carro ao parque
    p.carros[p.total] = c1;
    p.total++;
    //ou
    res=CriaFichaCarro(&p.carros[p.total], "CC-34-DD", "Maria Costa");
    if(res) p.total++;

    Carro* condutor = EncontraCondutor(&p, "CC-34-DD");
    if (condutor != NULL) {
        printf("Carro está no parque:\n");
        MostraCarro(condutor);
    }
    else {
        printf("Matrícula não encontrada no parque\n");
    }

    free(novo);
    return 0;
}