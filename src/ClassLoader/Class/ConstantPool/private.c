#include "constantpool.h"

static void populateUtf8(struct _constant_info* constants, int ordem, DADOS* d) {
	int i = 0;
	constants[ordem].type.Utf8.tam = d->le2Bytes(d);;
	constants[ordem].type.Utf8.bytes = (uint8_t*)malloc((constants[ordem].type.Utf8.tam+1)*sizeof(uint8_t));

	for (i = 0; i < constants[ordem].type.Utf8.tam; i++) {
		constants[ordem].type.Utf8.bytes[i] = d->le1Byte(d);
	}
	constants[ordem].type.Utf8.bytes[i] = '\0';
} 

static void populateMethodRef(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.MethodRef.classIndex = d->le2Bytes(d);
	constants[ordem].type.MethodRef.nameTypeIndex = d->le2Bytes(d);
}

static void populateInteger(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.Integer.bytes = d->le4Bytes(d);
}

static void populateFloat(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.Integer.bytes = d->le4Bytes(d);
}

static void populateLong(struct _constant_info* constants, int ordem, DADOS* d){
	constants[ordem].type.Long.highBytes = d->le4Bytes(d);
	constants[ordem].type.Long.lowBytes = d->le4Bytes(d);
}

static void populateDouble(struct _constant_info* constants, int ordem, DADOS* d){
	constants[ordem].type.Double.highBytes = d->le4Bytes(d);
	constants[ordem].type.Double.lowBytes = d->le4Bytes(d);
}

static void populateNameType(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.NameType.nameIndex = d->le2Bytes(d);
	constants[ordem].type.NameType.descriptorIndex = d->le2Bytes(d);
}

static void populateInterfaceMehodRef(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.InterfaceMethodRef.classIndex = d->le2Bytes(d);
	constants[ordem].type.InterfaceMethodRef.nameTypeIndex = d->le2Bytes(d);
}

static void populateFieldRef(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.FieldRef.classIndex = d->le2Bytes(d);
	constants[ordem].type.FieldRef.nameTypeIndex = d->le2Bytes(d);
}

static void populateStringRef(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.String.stringIndex = d->le2Bytes(d);
}

static void populateClassRef(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.Class.nameIndex = d->le2Bytes(d);
}


