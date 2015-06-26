#include "public.c"

// funcoes visiveis publicamente
CLASS_LOADER* initCLASS_LOADER() {
	CLASS_LOADER* toReturn = (CLASS_LOADER*)malloc(sizeof(CLASS_LOADER));

	// inicializacao dos campos
		toReturn->class = initCLASS();

	// inicializacao dos metodos
		toReturn->load = load;

	return toReturn;
}
