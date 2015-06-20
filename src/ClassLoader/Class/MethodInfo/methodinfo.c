#include "methodinfo.h"

static uint16_t getAccessFlags(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getNameIndex(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getDescriptorIndex(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getAttributesCount(DADOS* d) {
	return d->le2Bytes(d);
}

static int addMethods(METHOD_POOL* this, CONSTANT_POOL* cp, int ordem, DADOS* d) {
	
	this->methods[ordem].access_flags = getAccessFlags(d);
	this->methods[ordem].name_index = getNameIndex(d);
	this->methods[ordem].descriptor_index = getDescriptorIndex(d);
	this->methods[ordem].attributes_count = getAttributesCount(d);

	ATTRIBUTE_POOL* method_attributes = initATTRIBUTE_POOL(this->methods[ordem].attributes_count);
	for(int i =0; i < this->methods[ordem].attributes_count; i++){
		method_attributes->addAttribute(method_attributes, cp, i, d);
	}
	this->methods[ordem].attributes = method_attributes->attributes;

	return E_SUCCESS;
}

METHOD_POOL* initMETHOD_POOL(int count) {
	METHOD_POOL* toReturn = (METHOD_POOL*)malloc(sizeof(METHOD_POOL));

	toReturn->methods = (struct _method_info*)malloc((count)*sizeof(struct _method_info));
	toReturn->addMethods = addMethods;

	return toReturn;
}
