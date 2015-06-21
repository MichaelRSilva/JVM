#include "private.c"

/*!
	coloca um dado de um tipo no ponto de constante
*/
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

/*!
	entra o ponto de constantes e um index, devolve um dado em utf8
*/
static char* getUtf8String(CONSTANT_POOL* this, int index) {
	if (index == 0) return NULL;
	return (char*)this->constants[index - 1].type.Utf8.bytes;
}

/*!
	entra o ponto de constantes e um index, o nome de uma classe
*/
static char* getClassName(CONSTANT_POOL* this, int index) {
	if (index == 0) return NULL;
	return getUtf8String(this, this->constants[index - 1].type.Class.nameIndex);
}

/*!
	entra o ponto de constantes e um index, devolve o tipo de um atributo
*/
static char* getAttributeType(CONSTANT_POOL* this, int index) {
	if (index == 0) return NULL;
	return (char*)this->constants[index - 1].type.Utf8.bytes;
}

/*!
	inicia o ponto de constante
*/
CONSTANT_POOL* initCONSTANT_POOL(int count) {
	CONSTANT_POOL* toReturn = (CONSTANT_POOL*)malloc(sizeof(CONSTANT_POOL));

	toReturn->constants = (struct _constant_info*)malloc((count - 1)*sizeof(struct _constant_info));
	toReturn->addConstant = addConstant;
	toReturn->getClassName = getClassName;
	toReturn->getUtf8String = getUtf8String;
	toReturn->getAttributeType = getAttributeType;

	return toReturn;
}
