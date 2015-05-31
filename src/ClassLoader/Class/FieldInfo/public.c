#include "fieldinfo.h"
#include "private.c"

FIELD_POOL* initFIELD_POOL() {
	FIELD_POOL* toReturn = (FIELD_POOL*)malloc(sizeof(FIELD_POOL));

	// TODO

	return toReturn;
}


/*CONSTANT_POOL* initCONSTANT_POOL(int* count) {
	CONSTANT_POOL* toReturn = (CONSTANT_POOL*)malloc(sizeof(CONSTANT_POOL));

	toReturn->constants = (struct _constant_info*)malloc((*count - 1)*sizeof(struct _constant_info));
	toReturn->addConstant = addConstant;

	return toReturn;
}*/