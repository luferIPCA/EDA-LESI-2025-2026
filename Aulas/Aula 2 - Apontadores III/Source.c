/*!
 *  @file Source.c
 *  @author mustl
 *  @date 2026-02-25
 *  @project Project1
 *
 *  Implements the source.
 */
#include <stdio.h>
#include <conio.h>
#include "Header.h"
#include <stdbool.h>

#pragma warning (disable: 4996)

int main(int argc, char* argv[]) {

#pragma region ARGS

	//External parameters

	printf("Args; %d\n", argc);
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

#pragma endregion

#pragma region A

	int a = 7;
	int b = 16;

	Troca(a, b);

	printf("Depois:");
	printf("a= %d | b=%d\n", a, b);

	BoaTroca(&a, &b);

	printf("Boa Depois:");
	printf("a= %d | b=%d\n", a, b);

	int sum;
	int sub = SumAndSubOperations(a, b, &sum);

	printf("Sub: %d - Sum: %d\n", sub, sum);

#pragma endregion

#pragma region B

	Person p;
	p.age = 23;
	strcpy(p.name, "Ola");

	Person* q;
	
	q = &p;

	q->age = 23;
	strcpy(q->name, "Ole");

#pragma endregion

#pragma region C

	double v[] = { 12.5,34.3,-5-4 };

	double* d = v;

	int size = sizeof(v) / sizeof(double);
	printf("Size=%d\n", size);

	for (int i = 0; i<size; i++) {
		//printf("v[%d]=%.1f\n",i,v[i]);
		printf("v[%d]=%.1f\n", i, *(d++));
	}

#pragma endregion

	getche();
}