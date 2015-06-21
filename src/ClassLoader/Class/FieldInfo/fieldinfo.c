#include "fieldinfo.h"

/*!
	devolve as flags de acesso do field
*/
static uint16_t getAccessFlags(DADOS* d) {
	return d->le2Bytes(d);
}

/*!
	devolve o indice de um nome do field
*/
static uint16_t getNameIndex(DADOS* d) {
	return d->le2Bytes(d);
}

/*!
	devolve o indice da descricao do field
*/
static uint16_t getDescriptorIndex(DADOS* d) {
	return d->le2Bytes(d);
}

/*!
	devolve a quantidade de atributos do field
*/
static uint16_t getAttributesCount(DADOS* d) {
	return d->le2Bytes(d);
}

/*!
	carrega um field na memoria
*/
static int addField(FIELD_POOL* this, CONSTANT_POOL* cp, int ordem, DADOS* d) {
	
	this->fields[ordem].access_flags = getAccessFlags(d);
	this->fields[ordem].name_index = getNameIndex(d);
	this->fields[ordem].descriptor_index = getDescriptorIndex(d);
	this->fields[ordem].attributes_count = getAttributesCount(d);
	this->fields[ordem].value = 0;

	ATTRIBUTE_POOL* field_attributes = initATTRIBUTE_POOL(this->fields[ordem].attributes_count);
	for(int i =0; i<this->fields[ordem].attributes_count; i++){
		field_attributes->addAttribute(field_attributes, cp, i, d);
	}
	this->fields[ordem].attributes = field_attributes->attributes;

	return E_SUCCESS;
}

/*!
	inicia o ponto de fields
*/
FIELD_POOL* initFIELD_POOL(int count) {
	FIELD_POOL* toReturn = (FIELD_POOL*)malloc(sizeof(FIELD_POOL));

	toReturn->fields = (struct _field_info*)malloc((count)*sizeof(struct _field_info));
	toReturn->addField = addField;
	return toReturn;
}
