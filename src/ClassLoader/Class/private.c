#include "class.h"

static int verifyCAFEBABE(uint32_t magic) {
	return (0xCAFEBABE == magic) ? E_SUCCESS : E_CAFEBABE;
}

static int verifyVersion(uint16_t minor_version, uint16_t major_version) {
	if (!(major_version > 48 || major_version < 45)) {
		if (major_version == 48) {
			if (minor_version == 0){
				return E_SUCCESS;
			}
		}else{
			return E_SUCCESS;
		}
	}
	return E_VERSION;
}

static uint32_t getMagicNumber(DADOS* d) {
	return (int)d->le4Bytes(d);
}

static uint16_t getMinorVersion(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getMajorVersion(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getConstantPoolCount(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getAccessFlags(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getThisClass(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getSuperClass(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getInterfacesCount(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getFieldsCount(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getMethodsCount(DADOS* d) {
	return d->le2Bytes(d);
}

static uint16_t getAttributesCount(DADOS* d) {
	return d->le2Bytes(d);
}

static void addExtended(CONSTANT_POOL* cp, int ordem) {
    cp->constants[ordem].tag = 0;
}

static CONSTANT_POOL* populateConstantPool(CLASS* this, DADOS* d){
	CONSTANT_POOL* toReturn = initCONSTANT_POOL(this->constant_pool_count);
	int returnContinued = 0;
	
	for (int i = 0; i < this->constant_pool_count - 1; i++) {
		if(toReturn->addConstant(toReturn, i, d) == 1){
			addExtended(toReturn,++i);
		}
	}

	return toReturn;
}

static int populateInterfaces(CLASS* this, DADOS* d) {
	this->interfaces = (uint16_t*)malloc(this->interfaces_count*sizeof(uint16_t));
	for (int i = 0; i < this->interfaces_count; i++) {
		this->interfaces[i] = d->le2Bytes(d); 
		// TODO: verificar validade do indice
	}
	return E_SUCCESS;
}


static FIELD_POOL* populateFieldPool(CLASS* this, DADOS* d){
	FIELD_POOL* toReturn = initFIELD_POOL(this->fields_count);
	
	for (int i = 0; i < this->fields_count; i++) {
		toReturn->addField(toReturn,this->constant_pool, i, d);
	}

	return toReturn;
}


static METHOD_POOL* populateMethodsPool(CLASS* this, DADOS* d){
	METHOD_POOL* toReturn = initMETHOD_POOL(this->methods_count);
	
	for (int i = 0; i < this->methods_count; i++) {
		toReturn->addMethods(toReturn,this->constant_pool, i, d);
	}

	return toReturn;
}

static ATTRIBUTE_POOL* populateAttributePool(CLASS* this, DADOS* d) {
	ATTRIBUTE_POOL* toReturn = initATTRIBUTE_POOL(this->attributes_count);

	for (int i = 0; i < this->attributes_count; i++) {
		toReturn->addAttribute(toReturn, this->constant_pool, i, d);
	}

	return toReturn;
}

