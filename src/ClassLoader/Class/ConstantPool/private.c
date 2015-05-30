#include "constantpool.h"

// declaracoes
static void populateUtf8(struct _constant_info*, int ordem, DADOS d, int* contador);
static void populateMethodRef(struct _constant_info* constants, int ordem, DADOS d, int* contador);

static void addConstant(CONSTANT_POOL* this, int ordem, DADOS d, int* contador) {
	this->constants[ordem].tag = d.bytes[(*contador)++];
	switch(this->constants[ordem].tag) {
		case tUtf8:
			populateUtf8(this->constants, ordem, d, contador);
			break;
		case tInteger:
			break;
		case tFloat:
			break;
		case tLong:
			break;
		case tDouble:
			break;
		case tClass:
			break;		
		case tString:
			break;		
		case tFieldRef:

			break;		
		case tMethodRef:
			populateMethodRef(this->constants, ordem, d, contador);
			break;		
		case tInterfaceMethodRef:
			break;		
		case tNameType:
			break;
		default:
			break;	
	}
}

static void populateUtf8(struct _constant_info* constants, int ordem, DADOS d, int* contador) {
	int i = 0;
	uint16_t tam = d.bytes[*contador++];

	tam = tam << 8 | d.bytes[*contador++];
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

