#include "methodinfo.h"
#include "private.c"

static int addMethods(METHOD_POOL* this, CONSTANT_POOL* cp, int ordem, DADOS* d) {
	
	//this->method[ordem].access_flags = getAccessFlags(d);
	//this->method[ordem].name_index = getNameIndex(d);
	//this->method[ordem].descriptor_index = getDescriptorIndex(d);
	//this->method[ordem].attributes_count = getAttributesCount(d);

	printf("1: %x \n",d->le2Bytes(d));
	printf("2: %x \n",d->le2Bytes(d));
    printf("3: %x \n",d->le2Bytes(d));
	printf("4: %x \n",d->le2Bytes(d));


	/*ATTRIBUTE_POOL* method_attributes = initATTRIBUTE_POOL(this->method[ordem].attributes_count);
	for(int i =0; i<this->method[ordem].attributes_count; i++){
		method_attributes->addAttribute(method_attributes, cp, i, d);
	}
	this->method[ordem].attributes = method_attributes->attributes; */

	return E_SUCCESS; 
}

METHOD_POOL* initMETHOD_POOL(int *count) {
	METHOD_POOL* toReturn = (METHOD_POOL*)malloc(sizeof(METHOD_POOL));

	toReturn->method = (struct _method_info*)malloc((*count - 1)*sizeof(struct _method_info));
	toReturn->addMethods = addMethods;

	return toReturn;
}