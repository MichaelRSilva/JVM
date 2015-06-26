#include "class.h"
ATTRIBUTE_POOL Mattributepool;
CONSTANT_POOL Mconstantpool;
FIELD_POOL Mfieldpool;
METHOD_POOL Mmethodpool;

/*!
	devolve o nome de uma classe recebida
*/
static char* getName(CLASS* this) {
	return this->constant_pool->getClassName(this->constant_pool, this->this_class);
}

/*!
	devolve o nome de uma classe pai
*/
static char* getParentName(CLASS* this) {
	return this->constant_pool->getClassName(this->constant_pool, this->super_class);
}

/*!
	devolve o nome de uma interface recebida
*/
static char* getInterfaceName(CLASS* this, int interface_index) {
	return this->constant_pool->getClassName(this->constant_pool, this->interfaces[interface_index]);
}

/*!
	inicia o tipo de class
*/
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
		toReturn->fields_pool = NULL; 
		toReturn->methods_pool = NULL;
		toReturn->attribute_pool = NULL;

	// inicializacao das funcoes
		toReturn->getParentName = getParentName;
		toReturn->getName = getName;
		toReturn->getInterfaceName = getInterfaceName;

	return toReturn;
}
