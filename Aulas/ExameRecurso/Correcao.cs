

//Questão 1: Árvore de Hubs (BST+Lista) - Multinacional Logidtica
//---------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// a) Structs (1.5 valores)
typedef struct Encomenda
{
    int idEncomenda;
    float pesoKg;
    struct Encomenda* seguinte;
}
Encomenda;

typedef struct Hub
{
    char nomeHub[50];
    Encomenda* listaEncomendas; // Cabeça da sublista ligada de encomendas
    struct Hub* esquerda;
    struct Hub* direita;
}
Hub;

// b) Função de Procura e Acumulação (3.5 valores)
bool calcularPesoHub(iHub* raiz, char* nomeAlvo, float* pesoTotal)
{
    if (raiz == NULL)
    {
        return false; // Caso Base 1: Cidade não encontrada
    }

    int comp = strcmp(nomeAlvo, raiz->nomeHub);

    // Caso Base 2: Encontrado na BST!
    if (comp == 0)
    {
        float somatorio = 0.0f;
        Encomenda* atualEnc = raiz->listaEncomendas;

        // Varre a lista linear de encomendas somando o peso
        while (atualEnc != NULL)
        {
            somatorio += atualEnc->pesoKg;
            atualEnc = atualEnc->seguinte;
        }

        *pesoTotal = somatorio; // Atribuição por referência
        return true;
    }

    if (comp < 0)
    {
        return calcularPesoHub(raiz->esquerda, nomeAlvo, pesoTotal);
    }
    else
    {
        return calcularPesoHub(raiz->direita, nomeAlvo, pesoTotal);
    }
}


//QUESTÃO 2 — Cais de Empilhamento (Pilha Dinâmica)
//---------------------------------------------------

 // a) Structs (1.0 valor)
typedef struct Contentor
{
    int idContentor;
    struct Contentor* abaixo;
}
Contentor;

typedef struct Cais
{
    Contentor* topoAcessivel;
}
Cais;

// b) Empilhamento sem duplicados (2.0 valores)
int empilharContentor(Cais* cais, int idNovo)
{
    Contentor* atual = cais->topoAcessivel;
    int total = 0;
    bool duplicado = false;

    while (atual != NULL)
    {
        if (atual->idContentor == idNovo) duplicado = true;
        total++;
        atual = atual->abaixo;
    }

    if (duplicado) return total; // Se duplicado, ignora inserção

    Contentor* novo = (Contentor*)malloc(sizeof(Contentor));
    if (novo == NULL) return total;

    novo->idContentor = idNovo;
    novo->abaixo = cais->topoAcessivel;
    cais->topoAcessivel = novo;
    total++;

    return total;
}

// c) Remoção respeitando a restrição de Pilha (2.0 valores)
bool removerUrgente(Cais* caisOriginal, int idAlvo)
{
    Cais caisAux;
    caisAux.topoAcessivel = NULL;
    bool encontrado = false;

    // Desempilha para a pilha auxiliar até expor o alvo
    while (caisOriginal->topoAcessivel != NULL)
    {
        if (caisOriginal->topoAcessivel->idContentor == idAlvo)
        {
            encontrado = true;
            break;
        }
        Contentor* temp = caisOriginal->topoAcessivel;
        caisOriginal->topoAcessivel = temp->abaixo;
        temp->abaixo = caisAux.topoAcessivel;
        caisAux.topoAcessivel = temp;
    }

    // Se achou, elimina o nó alvo
    if (encontrado)
    {
        Contentor* alvo = caisOriginal->topoAcessivel;
        caisOriginal->topoAcessivel = alvo->abaixo;
        free(alvo);
    }

    // Repõe os contentores retirados temporariamente
    while (caisAux.topoAcessivel != NULL)
    {
        Contentor* repor = caisAux.topoAcessivel;
        caisAux.topoAcessivel = repor->abaixo;
        repor->abaixo = caisOriginal->topoAcessivel;
        caisOriginal->topoAcessivel = repor;
    }

    return encontrado;
}

//QUESTÃO 3 — Portão de Segurança (Tabela de Hash)
//------------------------------------------------

#define TAM_TABELA 31

// a) Structs (1.5 valores)
typedef struct NoMotorista
{
    char codigoCartao[20];
    char transportadora[50];
    int viagensAutorizadas;
    struct NoMotorista* proximo; // Gerir colisões por encadeamento
}
NoMotorista;

typedef struct SistemaSeguranca
{
    NoMotorista* slots[TAM_TABELA];
}
SistemaSeguranca;

// Função Hash Auxiliar
int calcularHash(char* chave)
{
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) soma += chave[i];
    return soma % TAM_TABELA;
}

// b) Função de Validação e Consulta (3.5 valores)
int consultarMotorista(SistemaSeguranca* sistema, char* codAlvo, char* transpDestino, int* viagensDestino)
{
    int idx = calcularHash(codAlvo);
    NoMotorista* atual = sistema->slots[idx];

    while (atual != NULL)
    {
        if (strcmp(atual->codigoCartao, codAlvo) == 0)
        {
            strcpy(transpDestino, atual->transportadora);
            *viagensDestino = atual->viagensAutorizadas;
            return 1; // Sucesso
        }
        atual = atual->proximo;
    }
    return -1; // Não registado
}

//QUESTÃO 4 — Persistência da Tabela de Hash
//--------------------------------------------

// Estrutura espelho estática para gravação limpa em ficheiro
typedef struct RegistoFicheiro
{
    char codigoCartao[20];
    char transportadora[50];
    int viagensAutorizadas;
}
RegistoFicheiro;

// Função auxiliar de inserção durante o carregamento
void inserirSeguranca(SistemaSeguranca* sistema, char* cod, char* transp, int viagens)
{
    int idx = calcularHash(cod);
    NoMotorista* novo = (NoMotorista*)malloc(sizeof(NoMotorista));
    if (novo == NULL) return;
    strcpy(novo->codigoCartao, cod);
    strcpy(novo->transportadora, transp);
    novo->viagensAutorizadas = viagens;
    novo->proximo = sistema->slots[idx];
    sistema->slots[idx] = novo;
}

// a) Preservar (2.0 valores)
bool guardarSistema(SistemaSeguranca* sistema, char* path)
{
    FILE* f = fopen(path, "wb");
    if (f == NULL) return false;

    for (int i = 0; i < TAM_TABELA; i++)
    {
        NoMotorista* atual = sistema->slots[i];
        while (atual != NULL)
        {
            RegistoFicheiro aux;
            strcpy(aux.codigoCartao, atual->codigoCartao);
            strcpy(aux.transportadora, atual->transportadora);
            aux.viagensAutorizadas = atual->viagensAutorizadas;

            fwrite(&aux, sizeof(RegistoFicheiro), 1, f);
            atual = atual->proximo;
        }
    }
    fclose(f);
    return true;
}

// b) Carregar (2.0 valores)
bool carregarSistema(SistemaSeguranca* sistema, char* path)
{
    FILE* f = fopen(path, "rb");
    if (f == NULL) return false;

    // Inicializa a RAM limpa
    for (int i = 0; i < TAM_TABELA; i++) sistema->slots[i] = NULL;

    RegistoFicheiro lido;
    while (fread(&lido, sizeof(RegistoFicheiro), 1, f) == 1)
    {
        inserirSeguranca(sistema, lido.codigoCartao, lido.transportadora, lido.viagensAutorizadas);
    }
    fclose(f);
    return true;
}

// c) Demonstração Main (1.0 valor)
int main()
{
    SistemaSeguranca portaria;
    for (int i = 0; i < TAM_TABELA; i++) portaria.slots[i] = NULL;

    inserirSeguranca(&portaria, "DRV-PT-9012", "TransGlobal", 15);

    if (guardarSistema(&portaria, "seguranca.dat"))
    {
        printf("Ficheiro gravado.\n");
    }

    SistemaSeguranca portariaBackup;
    if (carregarSistema(&portariaBackup, "seguranca.dat"))
    {
        printf("RAM restaurada com sucesso.\n");
    }
    return 0;
}
i
