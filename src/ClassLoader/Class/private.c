#include "class.h"

static int verifyCAFEBABE(DADOS d, int* contador) {
	int cafebabe = 0xCAFEBABE, buffer = 0, i;
	for (i = 0; i < 4; i++) {
		buffer = (buffer << 8) | d.bytes[i];
	}

	*contador = i + 1;
	return (cafebabe == buffer) ? E_SUCCESS : E_CAFEBABE;
}
