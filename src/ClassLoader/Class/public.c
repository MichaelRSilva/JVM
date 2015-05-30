#include "class.h"
#include "private.c"

// funcoes somente acessiveis pela struct _dot_class
static int parseDotClass(CLASS* this, DADOS d) {
	int flag = 0, contador = 0, cp_size = 0;

	if (!(flag = verifyCAFEBABE(d))) {

		//Add first informations to class struct
		this->magic = getMagicNumber(d,&contador);
		this->minor_version = getMinorVersion(d,&contador);
		this->major_version = getMajorVersion(d,&contador); // TODO: verificar minorversion <= majorversion
		this->constant_pool_count = getConstantPoolCount(d,&contador);
		this->constant_pool = populateConstantPool(this, d, &contador);

		// for(; contador < d.tamanho; contador++) {
			// if (d[contador] == 0x20) {
			// 	monta_metodo(this->class, d, &contador); 
			// }
		// }
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

		toReturn->constant_pool = NULL;
		toReturn->fields = NULL; 
		toReturn->methods = NULL;
		toReturn->attributes = NULL;

	// inicializacao das funcoes
		toReturn->parseDotClass = parseDotClass;

	return toReturn;
}
