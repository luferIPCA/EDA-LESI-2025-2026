/*!
 *  @file Funcoes.c
 *  @author mustl
 *  @date 2026-02-25
 *  @project Project1
 *
 *  Implements the funcoes.
 * 
 */

#include "Header.h"

/*!
 *  
 *
 *      @param [in] x 
 *      @param [in] y 
 */
void Troca(int x, int y) {
	int temp = x;
	x = y;
	y = x;
}


void BoaTroca(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

/*!
 *  Sums the and sub operations.
 *
 *      @param [in]     x   
 *      @param [in]     y   
 *      @param [in,out] sum 
 *
 *      @return 
 */
int SumAndSubOperations(int x, int y, int* sum) {

	*sum = x + y;
	return (x - y);
}