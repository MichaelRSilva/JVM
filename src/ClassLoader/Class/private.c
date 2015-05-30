#include "class.h"

static int verifyCAFEBABE(DADOS d) {
	int cafebabe = 0xCAFEBABE, buffer = 0, i;
	for (i = 0; i < 4; i++) {
		buffer = (buffer << 8) | d.bytes[i];
	}

	return (cafebabe == buffer) ? E_SUCCESS : E_CAFEBABE;
}

static int getMagicNumber(DADOS d, int* contador) {
	int buffer = 0, i;
	for (i = 0; i < 4; i++) {
		buffer = (buffer << 8) | d.bytes[i];
	}

	*contador = i;
	
	return buffer;
}

static int getMinorVersion(DADOS d, int* contador) {
	int buffer = 0, i = 0, qtdBitsRead = 2;

	for (i = *contador; i < (*contador+qtdBitsRead); i++) {
		buffer = (buffer << 8) | d.bytes[i];
	}

	*contador = *contador+qtdBitsRead;
	
	return buffer;
}

static int getMajorVersion(DADOS d, int* contador) {
	int buffer = 0, i=0, qtdBitsRead = 2;

	for (i = *contador; i < (*contador+qtdBitsRead); i++) {
		buffer = (buffer << 8) | d.bytes[i];
	}

	*contador = *contador+qtdBitsRead;
	
	return buffer;
}

static int getConstantPoolCount(DADOS d, int* contador) {
	int buffer = 0, i=0, qtdBitsRead = 2;

	for (i = *contador; i < (*contador+qtdBitsRead); i++) {
		buffer = (buffer << 8) | d.bytes[i];
	}

	*contador = *contador+qtdBitsRead;
	
	return buffer;
}

static void addContinued(CONSTANT_POOL* this, int ordem, int *contador) {

    this->constants[ordem].tag = 0;
    strcpy (this->constants[ordem].type.Continued.bytes, "(large numeric continued)");
}


static CONSTANT_POOL* populateConstantPool(CLASS* this, DADOS d, int* contador){
	CONSTANT_POOL* toReturn = initCONSTANT_POOL((int*)&(this->constant_pool_count));
	int i = 0, returnContinued = 0;
	
	for (; i < this->constant_pool_count - 1; i++) {
		toReturn->addConstant(toReturn, i, d, contador,&returnContinued);

		if(returnContinued == 1){
			i++;
			addContinued(toReturn,i,contador);
		}

	}

	return toReturn;
}
