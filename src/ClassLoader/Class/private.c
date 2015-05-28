#include "class.h"

static int verifyCAFEBABE(DADOS d, int* contador) {
	int cafebabe = 0xCAFEBABE, buffer = 0, i;
	for (i = 0; i < 4; i++) {
		buffer = (buffer << 8) | d.bytes[i];
	}

	*contador = 3;
	return (cafebabe == buffer) ? E_SUCCESS : E_CAFEBABE;
}

static int getMagicNumber(DADOS d, int* contador) {
	int buffer = 0, i;
	for (i = 0; i < 4; i++) {
		buffer = (buffer << 8) | d.bytes[i];
	}

	*contador = 3;
	
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

	for (i = *contador; i < (*contador+2); i++) {
		buffer = (buffer << 8) | d.bytes[i];
	}

	*contador = *contador+qtdBitsRead;
	
	return buffer;
}
