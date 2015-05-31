#include "class.h"
#include "private.c"

// funcoes somente acessiveis pela struct _dot_class
static int parseDotClass(CLASS* this, DADOS d) {
	int flag = 0, contador = 0, cp_size = 0;

	this->magic = getMagicNumber(&d);
	if (!(flag = verifyCAFEBABE(this->magic))) {

		this->minor_version = getMinorVersion(&d);
		this->major_version = getMajorVersion(&d);
		if (!(flag = verifyVersion(this->minor_version, this->major_version))) {
			this->constant_pool_count = getConstantPoolCount(&d);
			this->constant_pool = populateConstantPool(this, &d);
			this->access_flags = getAccessFlags(&d);
			this->this_class = getThisClass(&d);
			this->super_class = getSuperClass(&d);
			this->interfaces_count = getInterfacesCount(&d);
			if (!(flag = populateInterfaces(this, &d))) {

				this->fields_count = getFieldsCount(&d);


				
			}
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

		toReturn->constant_pool = NULL;
		toReturn->fields = NULL; 
		toReturn->methods = NULL;
		toReturn->attributes = NULL;

	// inicializacao das funcoes
		toReturn->parseDotClass = parseDotClass;

	return toReturn;
}
