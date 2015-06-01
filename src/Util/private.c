#include "util.h"


static void printScreenConstantValue(struct _attribute_info attr, char *tab, CONSTANT_POOL* cp, int ordem) {
	printf("%s[%d]%s\n", tab, ordem,cp->constants[attr.attributeNameIndex-1].type.Utf8.bytes);
	printf("%s\tAttribute name index: %d\n", tab,attr.attributeNameIndex);
	printf("%s\tAttribute length: %d\n", tab,attr.attributeLength);
	printf("%s\tConstant value index: %d\n", tab,attr.info.ConstantValueAttribute.constantvalue_index);
}

static void printScreenCode(struct _attribute_info attr, char *tab, CONSTANT_POOL* cp, int ordem) {
	
	printf("%s[%d]%s\n", tab, ordem,cp->constants[attr.attributeNameIndex-1].type.Utf8.bytes);
	printf("%s\tAttribute name index: %d\n", tab,attr.attributeNameIndex);
	printf("%s\tAttribute length: %d\n", tab,attr.attributeLength);

	//TODO: imprimir tambem: Bytecode,exception , misc e LineNumberTable

}

static void printScreenExceptions(struct _attribute_info attr, char *tab) {
//TODO: MARCUS
}

static void printScreenInnerClasses(struct _attribute_info attr, char *tab) {
//NOT PRINT IN JCLASSLIB
}

static void printScreenSynthetic(struct _attribute_info attr, char *tab) {
//NOTHING
}

static void printScreenSourceFile(struct _attribute_info attr, char *tab) {
	printf("%s\tSource file index: %d\n", tab,attr.info.SourceFileAttribute.sourcefile_index);
}

static void printScreenLineNumberTable(struct _attribute_info attr, char *tab) {
//TODO: MARCUS
}

static void printScreenLocalVariableTable(struct _attribute_info attr, char *tab) {
//NOT PRINT IN JCLASSLIB
}

static void printScreenDeprecated(struct _attribute_info attr, char *tab) {
//NOTHING
}

static void printScreenAttribute(struct _attribute_info attr, CONSTANT_POOL* cp, char* tab, int ordem){

	char* tipoNome = (char*)malloc(cp->constants[attr.attributeNameIndex - 1].type.Utf8.tam * sizeof(char));
	strcpy(tipoNome, (char*)cp->constants[attr.attributeNameIndex - 1].type.Utf8.bytes);

	if (strcmp(tipoNome, "ConstantValue") == 0) {
		printScreenConstantValue(attr, tab,cp,ordem);
	} else if (strcmp(tipoNome, "Code") == 0) {
		printScreenCode(attr, tab,cp,ordem);
	} else if (strcmp(tipoNome, "Exceptions") == 0) {
		printScreenExceptions(attr, tab);
	} else if (strcmp(tipoNome, "InnerClasses") == 0) {
		printScreenInnerClasses(attr, tab);
	} else if (strcmp(tipoNome, "Synthetic") == 0) {
		printScreenSynthetic(attr, tab);
	} else if (strcmp(tipoNome, "SourceFile") == 0) {
		printScreenSourceFile(attr, tab);
	} else if (strcmp(tipoNome, "LineNumberTable") == 0) {
		printScreenLineNumberTable(attr, tab);
	} else if (strcmp(tipoNome, "LocalVariableTable") == 0) {
		printScreenLocalVariableTable(attr, tab);
	} else { // Deprecated
		
		printScreenDeprecated(attr, tab);

	}
}
