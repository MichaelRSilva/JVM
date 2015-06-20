#include "maquina.h"

METHOD_AREA* initMETHOD_AREA() {
	METHOD_AREA* toReturn;

	toReturn->classes = (CLASS**)malloc(sizeof(CLASS*));
	toReturn->interfaces = (CLASS**)malloc(sizeof(CLASS*));
	toReturn->classes_count = 0;
	toReturn->interfaces_count = 0;

	return toReturn;
}
