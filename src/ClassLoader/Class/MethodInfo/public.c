#include "methodinfo.h"
#include "private.c"

METHOD_INFO** initMETHOD_INFO() {
	METHOD_INFO** toReturn = (METHOD_INFO**)malloc(sizeof(METHOD_INFO));
	*(toReturn) = (METHOD_INFO*)malloc(sizeof(METHOD_INFO));

	// TODO

	return toReturn;
}
