/*
@file:Calc.c | Calc.lib
@author: lufer
@email: lufer@ipca.pt
@date: 12-02-2026
@version: 1.0
@description: library for mathematic calculus
*/

/*
@author: lufer
@date: 12-02-2026
@version: 1.0
@description: Calculate the average of the values in an array
@
*/
float CalcAverage(int vals[], int size){
	int sum=0;  //acumulador da soma dos vários valores
	float aver;	//valor da média

    if (size<=0) return 0.0f; //ERRO: não é possível calcular a média
	
	for(int i=0; i<size; i++){
		sum = sum + vals[i];
	}

	// operafor "/" é uma divisão inteira; 
    // (float) força-a a ser divisão real
	aver= (float)sum/size; 
    return aver;
}