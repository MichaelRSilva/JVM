#include "constantpool.h"

/*!
	coloca um dado to tipo Utf8 no constant pool (no lugar certo (do seu tipo))
*/
static void populateUtf8(struct _constant_info* constants, int ordem, DADOS* d) {
	int i = 0;
	constants[ordem].type.Utf8.tam = d->le2Bytes(d);;
	constants[ordem].type.Utf8.bytes = (uint8_t*)malloc((constants[ordem].type.Utf8.tam+1)*sizeof(uint8_t));

	for (i = 0; i < constants[ordem].type.Utf8.tam; i++) {
		constants[ordem].type.Utf8.bytes[i] = d->le1Byte(d);
	}
	constants[ordem].type.Utf8.bytes[i] = '\0';
} 

/*!
	coloca um dado do tipo referencia de metodo no constant pool (no lugar certo (do seu tipo))
*/
static void populateMethodRef(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.MethodRef.classIndex = d->le2Bytes(d);
	constants[ordem].type.MethodRef.nameTypeIndex = d->le2Bytes(d);
}

/*!
	coloca um dado do tipo inteiro no constant pool (no lugar certo (do seu tipo))
*/
static void populateInteger(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.Integer.bytes = d->le4Bytes(d);
}

/*!
	coloca um dado do tipo float no constant pool (no lugar certo (do seu tipo))
*/
static void populateFloat(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.Integer.bytes = d->le4Bytes(d);
}

/*!
	coloca um dado do tipo long no constant pool (no lugar certo (do seu tipo))
*/
static void populateLong(struct _constant_info* constants, int ordem, DADOS* d){
	constants[ordem].type.Long.highBytes = d->le4Bytes(d);
	constants[ordem].type.Long.lowBytes = d->le4Bytes(d);
}

/*!
	coloca um dado do tipo double no constant pool (no lugar certo (do seu tipo))
*/
static void populateDouble(struct _constant_info* constants, int ordem, DADOS* d){
	constants[ordem].type.Double.highBytes = d->le4Bytes(d);
	constants[ordem].type.Double.lowBytes = d->le4Bytes(d);
}

/*!
	coloca um dado do tipo nome_do_tipo constant pool (no lugar certo (do seu tipo))
*/
static void populateNameType(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.NameType.nameIndex = d->le2Bytes(d);
	constants[ordem].type.NameType.descriptorIndex = d->le2Bytes(d);
}

/*!
	coloca um dado do tipo referencia para um metodo no constant pool (no lugar certo (do seu tipo))
*/
static void populateInterfaceMehodRef(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.InterfaceMethodRef.classIndex = d->le2Bytes(d);
	constants[ordem].type.InterfaceMethodRef.nameTypeIndex = d->le2Bytes(d);
}

/*!
	coloca um dado do tipo referencia de um field no constant pool (no lugar certo (do seu tipo))
*/
static void populateFieldRef(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.FieldRef.classIndex = d->le2Bytes(d);
	constants[ordem].type.FieldRef.nameTypeIndex = d->le2Bytes(d);
}

/*!
	coloca um dado do tipo string no constant pool (no lugar certo (do seu tipo))
*/
static void populateStringRef(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.String.stringIndex = d->le2Bytes(d);
}

/*!
	coloca um dado do tipo referencia de uma classe no constant pool (no lugar certo (do seu tipo))
*/
static void populateClassRef(struct _constant_info* constants, int ordem, DADOS* d) {
	constants[ordem].type.Class.nameIndex = d->le2Bytes(d);
}


