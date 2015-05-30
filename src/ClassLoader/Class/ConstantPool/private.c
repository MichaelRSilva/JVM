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


