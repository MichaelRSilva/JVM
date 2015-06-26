#include "maquina.h"

/*!
	inicializa a area de metodos
*/
METHOD_AREA* initMETHOD_AREA() {
	METHOD_AREA* toReturn = (METHOD_AREA*)malloc(sizeof(METHOD_AREA));

	toReturn->classes = (CLASS**)malloc(sizeof(CLASS*));
	toReturn->interfaces = (CLASS**)malloc(sizeof(CLASS*));
	toReturn->classes_count = 0;
	toReturn->interfaces_count = 0;

	return toReturn;
}
