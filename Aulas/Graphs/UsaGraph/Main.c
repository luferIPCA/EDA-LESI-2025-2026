
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#pragma warning( disable : 4996 )
#pragma comment (lib,"GraphLib.lib")

int main() {

	struct Cidade* c = (struct Cidade*)malloc(sizeof(struct Cidade));
	if (c != NULL) {
		strcpy(c->nome, "Braga");
	}

}