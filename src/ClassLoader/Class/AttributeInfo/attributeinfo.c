#include "private.c"

/*!
	Adiciona um atributo no constant pool passador por parametro
*/
static void addAttribute(ATTRIBUTE_POOL* this, CONSTANT_POOL* cp, int ordem, DADOS* d) {
	this->attributes[ordem].attributeNameIndex = d->le2Bytes(d);
	this->attributes[ordem].attributeLength = d->le4Bytes(d);

	char* tipoNome = (char*)malloc((cp->constants[this->attributes[ordem].attributeNameIndex - 1].type.Utf8.tam + 1) * sizeof(char));
	strcpy(tipoNome, (char*)cp->constants[this->attributes[ordem].attributeNameIndex - 1].type.Utf8.bytes);
	
	/*!
		verifica do tipo de atributo, e para cada tipo, chama uma funcao que esta no private.c
	*/
	if (strcmp(tipoNome, "ConstantValue") == 0) {
		populateConstantValueAttribute(&this->attributes[ordem], d);
	} else if (strcmp(tipoNome, "Code") == 0) {
		populateCodeAttribute(&this->attributes[ordem], cp, d);
	} else if (strcmp(tipoNome, "Exceptions") == 0) {
		populateExceptions(&this->attributes[ordem], d);
	} else if (strcmp(tipoNome, "InnerClasses") == 0) {
		populateInnerClasses(&this->attributes[ordem], d);
	} else if (strcmp(tipoNome, "Synthetic") == 0) {
		populateSynthetic(&this->attributes[ordem], d);
	} else if (strcmp(tipoNome, "SourceFile") == 0) {
		populateSourceFile(&this->attributes[ordem], d);
	} else if (strcmp(tipoNome, "LineNumberTable") == 0) {
		populateLineNumberTable(&this->attributes[ordem], d);
	} else if (strcmp(tipoNome, "LocalVariableTable") == 0) {
		populateLocalVariableTable(&this->attributes[ordem], d);
	} else { // Deprecated
		populateDeprecated(&this->attributes[ordem], d);
	}
}

/*!
	inicial o ponto de atributos de acordo com a struct _attribute_info
*/
ATTRIBUTE_POOL* initATTRIBUTE_POOL(int tamanho) {
	ATTRIBUTE_POOL* toReturn = (ATTRIBUTE_POOL*)malloc(sizeof(ATTRIBUTE_POOL));

	toReturn->attributes = (struct _attribute_info*)malloc(tamanho*sizeof(struct _attribute_info));
	toReturn->addAttribute = addAttribute;
	return toReturn;
}
