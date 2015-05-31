#include "constantpool.h"
#include "private.c"

static int addConstant(CONSTANT_POOL* this, int ordem, DADOS* d) {
	int toReturn = 0;
	
	this->constants[ordem].tag = d->le1Byte(d);
	switch(this->constants[ordem].tag) {
		case tUtf8:
			populateUtf8(this->constants, ordem, d);
			break;
		case tInteger:
			populateInteger(this->constants, ordem, d);
			break;
		case tFloat:
			populateFloat(this->constants, ordem, d);
			break;
		case tLong:
			populateLong(this->constants, ordem, d);
			toReturn = 1;
			break;
		case tDouble:
			populateDouble(this->constants, ordem, d);
			toReturn = 1;
			break;
		case tClass:
			populateClassRef(this->constants, ordem, d);
			break;		
		case tString:
			populateStringRef(this->constants, ordem, d);
			break;		
		case tFieldRef:
			populateFieldRef(this->constants, ordem, d);
			break;		
		case tMethodRef:
			populateMethodRef(this->constants, ordem, d);
			break;		
		case tInterfaceMethodRef:
			populateInterfaceMehodRef(this->constants, ordem, d);
			break;		
		case tNameType:
			populateNameType(this->constants, ordem, d);
			break;
		default:
			break;	
	}
	return toReturn;
}

CONSTANT_POOL* initCONSTANT_POOL(int* count) {
	CONSTANT_POOL* toReturn = (CONSTANT_POOL*)malloc(sizeof(CONSTANT_POOL));

	toReturn->constants = (struct _constant_info*)malloc((*count)*sizeof(struct _constant_info));
	toReturn->addConstant = addConstant;
	toReturn->constant_pool_count = count;

	return toReturn;
}
