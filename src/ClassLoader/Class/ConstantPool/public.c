#include "constantpool.h"
#include "private.c"


CONSTANT_POOL* initCONSTANT_POOL(int count) {
	CONSTANT_POOL* toReturn = (CONSTANT_POOL*)malloc(sizeof(CONSTANT_POOL));

	toReturn->constants = (struct _constant_info*)malloc(count*sizeof(struct _constant_info));
	toReturn->addConstant = addConstant;
	
	return toReturn;
}
