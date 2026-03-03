/*!
 *  @file Source.c
 *  @author mustl
 *  @date 2026-02-25
 *  @project Project1
 *
 *  Signatur functions and Data types
 */
#pragma once

#ifndef X
#define X

#define N 50

void Troca(int x, int y);

void BoaTroca(int *x, int *y);

int SumAndSubOperations(int x, int y, int* sum);

typedef struct Person {
	int age;
	char name[N];
}Person;

#endif // !X

