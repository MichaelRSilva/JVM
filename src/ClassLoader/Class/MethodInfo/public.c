#include "methodinfo.h"
#include "private.c"

// static funcao(METHOD_INFO**, DADOS, int*);

METHOD_INFO** initMETHOD_INFO() {
	METHOD_INFO** toReturn = (METHOD_INFO**)malloc(sizeof(METHOD_INFO));
	*(toReturn) = (METHOD_INFO*)malloc(sizeof(METHOD_INFO));

	// TODO

	// toReturn->funcao = funcao
	return toReturn;
}