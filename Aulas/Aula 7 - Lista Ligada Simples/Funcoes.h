/*!
 *  @file Funcoes.h
 *  @author mustl
 *  @date 2026-03-14
 *  @project Aula 7
 *
 *  Descreve assinatura de Funções.
 */

#pragma once

#include "Dados.h"

Element* CriaElement(int v);

Element* InsereInicio(Element* inicio, Element* novo);

Element* InsereFim(Element* inicio, Element* novo);

Element* InsereOrdenado(Element* inicio, Element* novo);

Element* ProcuraElemento(Element* h, int v);
bool ExisteElementRecursivo(Element* h, int v);

#pragma region A

Element* CriaElemento(int v, char nome[]);
int MostraLista(Element* h);


Element* InsereOrdenadoII(Element* inicio, Element* novo);

bool InsereOrdenadoIII(Element** inicio, Element* novo);
Element* InsereOrdenadoIV(Element* inicio, Element* novo, bool* inserido);
Resultado InsereOrdenadoV(Element* inicio, Element* novo);

//Auxiliares
int PercorreListaOperacao(Element* h, int (*f)(void *x));
int Dobro(void *x);
int Show(void* x);


//Outra versão
int PercorreListaOperacaoII(Element* h, void (*f)(void* x));
void OpDobro(void* x);
void OpMostrar(void* x);
void OpMaiusculas(void* x);

#pragma endregion



