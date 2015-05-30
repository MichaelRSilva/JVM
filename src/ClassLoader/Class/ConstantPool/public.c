#include "constantpool.h"
#include "private.c"

static void addConstant(CONSTANT_POOL* this, int ordem, DADOS d, int* contador) {
	this->constants[ordem].tag = d.bytes[(*contador)++];
	switch(this->constants[ordem].tag) {
		case tUtf8:
			populateUtf8(this->constants, ordem, d, contador);
			break;
		case tInteger:
			break;
		case tFloat:
			break;
		case tLong:
			break;
		case tDouble:
			break;
		case tClass:
			break;		
		case tString:
			break;		
		case tFieldRef:
			break;		
		case tMethodRef:
			populateMethodRef(this->constants, ordem, d, contador);
			break;		
		case tInterfaceMethodRef:
			break;		
		case tNameType:
			break;
		default:
			break;	
	}
}

CONSTANT_POOL* initCONSTANT_POOL(int count) {
	CONSTANT_POOL* toReturn = (CONSTANT_POOL*)malloc(sizeof(CONSTANT_POOL));

	toReturn->constants = (struct _constant_info*)malloc(count*sizeof(struct _constant_info));
	toReturn->addConstant = addConstant;

	return toReturn;
}
