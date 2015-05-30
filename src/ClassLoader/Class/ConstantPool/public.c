#include "constantpool.h"
#include "private.c"

static void addConstant(CONSTANT_POOL* this, int ordem, DADOS d, int* contador) {
	this->constants[ordem].tag = d.bytes[(*contador)++];
	switch(this->constants[ordem].tag) {
		case tUtf8:
			populateUtf8(this->constants, ordem, d, contador);
			break;
		case tInteger:
			populateInteger(this->constants, ordem, d, contador);
			break;
		case tFloat:
			populateFloat(this->constants, ordem, d, contador);
			break;
		case tLong:
			populateLong(this->constants, ordem, d, contador);
			addContinued(this, ordem);
			break;
		case tDouble:
			populateDouble(this->constants, ordem, d, contador);
			addContinued(this, ordem);
			break;
		case tClass:
			populateClassRef(this->constants, ordem, d, contador);
			break;		
		case tString:
			populateStringRef(this->constants, ordem, d, contador);
			break;		
		case tFieldRef:
			populateFieldRef(this->constants, ordem, d, contador);
			break;		
		case tMethodRef:
			populateMethodRef(this->constants, ordem, d, contador);
			break;		
		case tInterfaceMethodRef:
			populateInterfaceMehodRef(this->constants, ordem, d, contador);
			break;		
		case tNameType:
			populateNameType(this->constants, ordem, d, contador);
			break;
		default:
			break;	
	}
}

CONSTANT_POOL* initCONSTANT_POOL(int* count) {
	CONSTANT_POOL* toReturn = (CONSTANT_POOL*)malloc(sizeof(CONSTANT_POOL));

	toReturn->constants = (struct _constant_info*)malloc((*count)*sizeof(struct _constant_info));
	toReturn->addConstant = addConstant;
	toReturn->constant_pool_count = count;

	return toReturn;
}
