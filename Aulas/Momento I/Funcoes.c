/*!
 * EDA - 2025-2026
*  @file Funcoes.c
 *  @author mustl
 *  @date 2026-06-16
 *  @project Momento I
 *
 *  Implementa funcoes.
 */
#include "Dados.h"

/*!
 *  Questão 1
 *
 *      @param [in,out] x 
 *      @param [in,out] y 
 *      @param [in]     z 
 *
 *      @return 
 */
bool Atualiza(int* x, int* y, int z) {
    // a) Verificar condições — apontadores não podem ser NULL
    if (x == NULL || y == NULL) {
        return false;
    }

    // b) Se z < *x, atualizar x
    if (z < *x) {
        *x = z;
    }

    // c) Se z > *y, atualizar y
    if (z > *y) {
        *y = z;
    }

    return true;
}


/*!
 *  Questão 2
 *
 *      @param [in,out] v       
 *      @param [in]     tamanho 
 *      @param [in]     x       
 *      @param [in,out] total   
 *
 *      @return 
 */
bool ContaPares(int* valores, int tamanho, int x, int* total) {

    // b) Array sem valores
    if (valores == NULL || tamanho == 0) {
        return false;
    }

    // b) Tamanho jncomportável
    if (tamanho < 0 || tamanho > MAXSIZE) {
        return false;
    }

    *total = 0;
    int* ptr = valores;
    int i = 0;
    while (i < tamanho) {
        if (*ptr % 2 == 0 && *ptr > x) {
            (*total)++;
        }
        ptr++;      // aritmética de apontadores
        i++;
    }

    return true;  // = 1 em C
}

/*!
 *  Questão 3 - a)
 *
 *      @param [in,out] c 
 *
 *      @return 
 */
int MostraCarro(Carro* c) {
    if (c == NULL) return -1;

    printf("Matrícula: %s\n", c->matricula);
    printf("Dono: %s\n", c->dono);

    return 0;
}

/*!
 *  Questão 3 b) - Opção 1
 *
 *      @param [in,out] c         
 *      @param [in,out] matricula 
 *      @param [in,out] nome      
 *
 *      @return 
 */
bool CriaFichaCarro(Carro* c, char* matricula, char* nome) {
    if (c == NULL || matricula == NULL || nome == NULL) return false;

    //importante para controlar o tamnhap de entrada das strings
    strncpy(c->matricula, matricula, MAXMATRICULA - 1);
    c->matricula[MAXMATRICULA - 1] = '\0';  // pode ser critico

    strncpy(c->dono, nome, MAXNOME - 1);
    c->dono[MAXNOME - 1] = '\0';

    return true;
}
/*!
 *  Questão 3 b) - Opção 2
 *
 *      @param [in,out] c         
 *      @param [in,out] matricula 
 *      @param [in,out] nome      
 *
 *      @return 
 */
Carro* CriaFichaCarroII(char* matricula, char* nome, bool *res) {
    *res = false;
    //debug: printf("matricula = %p\n", matricula);
    //debug: printf("nome = %p\n", nome);
    if (matricula == NULL || nome == NULL) {
        //*res = false;
        return NULL;
    }

    Carro* novo = (Carro*)malloc(sizeof(Carro));
    if (novo == NULL) return NULL;
    strcpy(novo->matricula, matricula);
    strcpy(novo->dono, nome);

    *res = true;
    return novo;
}

/*!
 *  Questão 3 - c)
 *
 *      @param [in,out] p   
 *      @param [in,out] mat 
 *
 *      @return 
 */
Carro* EncontraCondutor(Parque* p, char* mat) {
    if (p == NULL || mat == NULL) return NULL;

    for (int i = 0; i < p->total; i++) {
        if (strcmp(p->carros[i].matricula, mat) == 0) {
            return &p->carros[i];
        }
    }

    return NULL;  // não encontrado
}