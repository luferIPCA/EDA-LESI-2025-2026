/*!
 * EDA - 2025-2026
*  @file GereUber.c
 *  @author mustl
 *  @date 2026-03-03
 *  @project Aula 5 - Apontadores - Consolidação
 *
 *  Preparação para 1º Momento de Avaliação
 */
#include  "Funcoes.h"
#include <string.h>

int main() {
	
	Uber u;
	bool x;

	Uber *aux = DefineFicha(12, "ola", true, &u);
	//ou
	//u=*DefineFicha(12, "ola", true, &u);	//CUIDADO
	if (aux) {
		u = *aux;
		x = MostraUber(&u);
	}

	Uber condutores[N];	//array de Uber

	int numCondutores = 0;
	x = RegistaCondutor(&u, condutores, &numCondutores);


	u = *DefineFicha(13, "Ok", false, &u);
	x = RegistaCondutor(&u, condutores, &numCondutores);

	x = MostraCondutores(condutores, numCondutores);
}