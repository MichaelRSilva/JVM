#include "classloader.h"
#include "private.c"

// funcoes somente visiveis a struct classloader
static int load(CLASS_LOADER* this, DADOS d) {
	return this->class->parseDotClass(this->class, d);
}

static int print(CLASS_LOADER* this) {

	return 0;
}

// funcoes visiveis publicamente
CLASS_LOADER* initCLASS_LOADER() {
	CLASS_LOADER* toReturn = (CLASS_LOADER*)malloc(sizeof(CLASS_LOADER));

	// inicializacao dos campos
		toReturn->class = initCLASS();

	// inicializacao dos metodos
		toReturn->load = load;
		toReturn->print = print;

	return toReturn;
}
