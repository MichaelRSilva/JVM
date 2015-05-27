#include "class.h"

// funcoes somente acessiveis pela struct _dot_class
static CLASS* parseDotClass(CLASS* this, DADOS d) {
	
	for (int i = 0; i < 4; i++) {
		printf("%x", d.bytes[i]);
	}

	return NULL;
}

// funcoes acessiveis publicamente
CLASS* initCLASS() {
	CLASS* toReturn = (CLASS*)malloc(sizeof(CLASS));

	// inicializacao dos campos
		toReturn->class_file = (char*)malloc(sizeof(char));
		toReturn->magic = 0;
		toReturn->minor_version = 0;
		toReturn->major_version = 0;
		toReturn->access_flags = 0;
		toReturn->this_class = 0;
		toReturn->super_class = 0;
		toReturn->interfaces_count = 0;
		toReturn->interfaces = NULL;

		toReturn->constant_pool_count = 0;
		toReturn->fields_count = 0;
		toReturn->methods_count = 0;
		toReturn->attributes_count = 0;

		toReturn->constant_pool = initCONSTANT_POOL();
		toReturn->fields = initFIELD_INFO(); 
		toReturn->methods = initMETHOD_INFO();
		toReturn->attributes = initATTRIBUTE_INFO();

	// inicializacao das funcoes
		toReturn->parseDotClass = parseDotClass;

	return toReturn;
}