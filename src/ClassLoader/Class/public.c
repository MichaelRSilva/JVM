#include "class.h"
#include "private.c"

// funcoes somente acessiveis pela struct _dot_class
static int parseDotClass(CLASS* this, DADOS d) {
	int flag = 0, contador = 0;

	if (!(flag = verifyCAFEBABE(d, &contador))) {

		//Add first informations to class struct
		this->magic = getMagicNumber(d,&contador);
		this->minor_version = getMinorVersion(d,&contador);
		this->major_version = getMajorVersion(d,&contador);



		for(; contador < d.tamanho; contador++) {
			// if (d[contador] == 0x20) {
			// 	monta_metodo(this->class, d, &contador);
			// }

		}
	}
	return flag;
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
