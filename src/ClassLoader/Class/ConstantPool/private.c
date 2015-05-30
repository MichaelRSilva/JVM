#include "constantpool.h"

static void populateUtf8(struct _constant_info* constants, int ordem, DADOS d, int* contador) {
	int i = 0;
	uint16_t tam = d.bytes[(*contador)++];

	tam = tam << 8 | d.bytes[(*contador)++];
	constants[ordem].type.Utf8.tam = tam;
	constants[ordem].type.Utf8.bytes = (uint8_t*)malloc((tam+1)*sizeof(uint8_t));

	for (; i < constants[ordem].type.Utf8.tam; i++) {
		constants[ordem].type.Utf8.bytes[i] = d.bytes[(*contador)++];
	}
	constants[ordem].type.Utf8.bytes[i] = '\0';
} 

static void populateMethodRef(struct _constant_info* constants, int ordem, DADOS d, int* contador) {
	uint16_t classIndex = d.bytes[(*contador)++], nameTypeIndex = 0;

	classIndex =  classIndex << 8 | d.bytes[(*contador)++];
	nameTypeIndex = d.bytes[(*contador)++];
	nameTypeIndex = nameTypeIndex << 8  | d.bytes[(*contador)++];

	constants[ordem].type.MethodRef.classIndex = classIndex;
	constants[ordem].type.MethodRef.nameTypeIndex = nameTypeIndex;
}

static void populateInteger(struct _constant_info* constants, int ordem, DADOS d, int* contador) {
	constants[ordem].type.Integer.bytes = d.bytes[(*contador)++];

	for (int i = 0; i < 4; i ++) {
		constants[ordem].type.Integer.bytes = constants[ordem].type.Integer.bytes << 8 | d.bytes[(*contador)++];	
	}
}

static void populateFloat(struct _constant_info* constants, int ordem, DADOS d, int* contador) {
	constants[ordem].type.Float.bytes = d.bytes[(*contador)++];

	for (int i = 0; i < 4; i ++) {
		constants[ordem].type.Float.bytes = constants[ordem].type.Float.bytes << 8 | d.bytes[(*contador)++];	
	}
}

static void populateLong(struct _constant_info* constants, int ordem, DADOS d, int* contador){
	constants[ordem].type.Long.highBytes = d.bytes[(*contador)++];

	for (int i = 0; i < 4; i ++) {
		constants[ordem].type.Long.highBytes = constants[ordem].type.Long.highBytes << 8 | d.bytes[(*contador)++]; 
	}

	constants[ordem].type.Long.lowBytes = d.bytes[(*contador)++];
	for (int i = 0; i < 4; i ++) {
		constants[ordem].type.Long.lowBytes = constants[ordem].type.Long.lowBytes << 8 | d.bytes[(*contador)++]; 
	}	
}

static void populateDouble(struct _constant_info* constants, int ordem, DADOS d, int* contador){
	constants[ordem].type.Double.highBytes = d.bytes[(*contador)++];
	for (int i = 0; i < 4; i++) {
		constants[ordem].type.Double.highBytes = constants[ordem].type.Double.highBytes << 8 | d.bytes[(*contador)++]; 
	}
	printf("highBytes: %x", constants[ordem].type.Double.highBytes);
	constants[ordem].type.Double.lowBytes = d.bytes[(*contador)++];
	for (int i = 0; i < 4; i++) {
		constants[ordem].type.Double.lowBytes = constants[ordem].type.Double.lowBytes << 8 | d.bytes[(*contador)++]; 
	}	
}

static void addContinued(CONSTANT_POOL* this, int ordem) {
	this->constants = realloc(this->constants, ((*this->constant_pool_count)+1)*sizeof(struct _constant_info));
	ordem++;
	(*this->constant_pool_count)++;

    this->constants[ordem].tag = 0;
    strcpy (this->constants[ordem].type.Continued.bytes, "(large numeric continued)");
}

static void populateNameType(struct _constant_info* constants, int ordem, DADOS d, int* contador) {
	uint16_t nameIndex = d.bytes[(*contador)++], descriptorIndex = 0;

	nameIndex =  nameIndex << 8 | d.bytes[(*contador)++];
	descriptorIndex = d.bytes[(*contador)++];
	descriptorIndex = descriptorIndex << 8  | d.bytes[(*contador)++];

	constants[ordem].type.NameType.nameIndex = nameIndex;
	constants[ordem].type.NameType.descriptorIndex = descriptorIndex;
}

static void populateInterfaceMehodRef(struct _constant_info* constants, int ordem, DADOS d, int* contador) {
	uint16_t classIndex = d.bytes[(*contador)++], nameTypeIndex = 0;

	classIndex =  classIndex << 8 | d.bytes[(*contador)++];
	nameTypeIndex = d.bytes[(*contador)++];
	nameTypeIndex = nameTypeIndex << 8  | d.bytes[(*contador)++];

	constants[ordem].type.InterfaceMethodRef.classIndex = classIndex;
	constants[ordem].type.InterfaceMethodRef.nameTypeIndex = nameTypeIndex;
}

static void populateFieldRef(struct _constant_info* constants, int ordem, DADOS d, int* contador) {
	uint16_t classIndex = d.bytes[(*contador)++], nameTypeIndex = 0;

	classIndex =  classIndex << 8 | d.bytes[(*contador)++];
	nameTypeIndex = d.bytes[(*contador)++];
	nameTypeIndex = nameTypeIndex << 8  | d.bytes[(*contador)++];

	constants[ordem].type.FieldRef.classIndex = classIndex;
	constants[ordem].type.FieldRef.nameTypeIndex = nameTypeIndex;
}

static void populateStringRef(struct _constant_info* constants, int ordem, DADOS d, int* contador) {
	uint16_t stringIndex = d.bytes[(*contador)++];

	stringIndex =  stringIndex << 8 | d.bytes[(*contador)++];

	constants[ordem].type.String.stringIndex = stringIndex;
}

static void populateClassRef(struct _constant_info* constants, int ordem, DADOS d, int* contador) {
	uint16_t nameIndex = d.bytes[(*contador)++];

	nameIndex =  nameIndex << 8 | d.bytes[(*contador)++];

	constants[ordem].type.Class.nameIndex = nameIndex;
}


