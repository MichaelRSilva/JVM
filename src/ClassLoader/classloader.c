#include "classloader.h"
UTIL _MUTIL;
CONSTANT_POOL _MCONSTANTP;

/*!
	verifica se eh um .class valido, para isso os primeiros 32bits tem que ser 0xCAFEBABE
*/
static int verifyCAFEBABE(uint32_t magic) {
	return (0xCAFEBABE == magic) ? E_SUCCESS : E_CAFEBABE;
}

/*!
	verifica se eh um .class valido, para isso verifica se temos um .class na versa 1.2
*/
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
	error(E_NOTSUPPORTED_VERSION);
	return E_NOTSUPPORTED_VERSION;
}

/*!
	para indicar os doubles
*/
static void addExtended(CONSTANT_POOL* cp, int ordem) {
    cp->constants[ordem].tag = 0;
}

/*!
	carrega o constant pool na class
*/
static CONSTANT_POOL* populateConstantPool(CLASS* this, DADOS* d){
	CONSTANT_POOL* toReturn = initCONSTANT_POOL(this->constant_pool_count);
	
	for (int i = 0; i < this->constant_pool_count - 1; i++) {
		if(toReturn->addConstant(toReturn, i, d) == 1){
			addExtended(toReturn,++i);
		}
	}

	return toReturn;
}

/*!
	carrega as interfaces na class
*/
static int populateInterfaces(CLASS* this, DADOS* d) {
	this->interfaces = (uint16_t*)malloc(this->interfaces_count*sizeof(uint16_t));
	for (int i = 0; i < this->interfaces_count; i++) {
		this->interfaces[i] = d->le2Bytes(d); 
		// TODO: verificar validade do indice
	}
	return E_SUCCESS;
}

/*!
	carrega o field pool na class
*/
static FIELD_POOL* populateFieldPool(CLASS* this, DADOS* d){
	FIELD_POOL* toReturn = initFIELD_POOL(this->fields_count);
	
	for (int i = 0; i < this->fields_count; i++) {
		toReturn->addField(toReturn,this->constant_pool, i, d);
	}

	return toReturn;
}

/*!
	carrega o ponto de metodos na class
*/
static METHOD_POOL* populateMethodsPool(CLASS* this, DADOS* d){
	METHOD_POOL* toReturn = initMETHOD_POOL(this->methods_count);
	
	for (int i = 0; i < this->methods_count; i++) {
		toReturn->addMethods(toReturn,this->constant_pool, i, d);
	}

	return toReturn;
}

/*!
	recebe o ponto de atributs na class
*/
static ATTRIBUTE_POOL* populateAttributePool(CLASS* this, DADOS* d) {
	ATTRIBUTE_POOL* toReturn = initATTRIBUTE_POOL(this->attributes_count);

	for (int i = 0; i < this->attributes_count; i++) {
		toReturn->addAttribute(toReturn, this->constant_pool, i, d);
	}

	return toReturn;
}


/*!
	carrega uma classe na memoria, eh dado o nome de um arquivo .class
*/
// funcoes somente visiveis a struct classloader
static CLASS* load(CLASS_LOADER* this, char* fileName) {
	DADOS d = _MUTIL.LeArquivo(fileName);
	int flag = 0;
	uint8_t* base_pointer = d.bytes;

	this->class->magic = d.le4Bytes(&d);
	if (!(flag = verifyCAFEBABE(this->class->magic))) {
		this->class->minor_version = d.le2Bytes(&d);
		this->class->major_version = d.le2Bytes(&d);
		if (!(flag = verifyVersion(this->class->minor_version, this->class->major_version))) {
			this->class->constant_pool_count = d.le2Bytes(&d);
			this->class->constant_pool = populateConstantPool(this->class, &d);
			this->class->access_flags = d.le2Bytes(&d);
			this->class->this_class = d.le2Bytes(&d);
			this->class->super_class = d.le2Bytes(&d);
			this->class->interfaces_count = d.le2Bytes(&d);
			if (!(flag = populateInterfaces(this->class, &d))) {
				this->class->fields_count = d.le2Bytes(&d);
				this->class->fields_pool = populateFieldPool(this->class,&d);
				this->class->methods_count = d.le2Bytes(&d);
				this->class->methods_pool = populateMethodsPool(this->class, &d);
				this->class->attributes_count = d.le2Bytes(&d);
				this->class->attribute_pool = populateAttributePool(this->class, &d);
			}
		}
	}

	return ((int)(d.bytes - base_pointer) != d.tamanho)?NULL:this->class;
}

// funcoes visiveis publicamente
CLASS_LOADER* initCLASS_LOADER() {
	CLASS_LOADER* toReturn = (CLASS_LOADER*)malloc(sizeof(CLASS_LOADER));

	// inicializacao dos campos
		toReturn->class = initCLASS();

	// inicializacao dos metodos
		toReturn->load = load;

	return toReturn;
}
