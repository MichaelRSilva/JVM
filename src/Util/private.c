#include "util.h"


static void printScreenConstantValue(struct _attribute_info attr, char *tab, CONSTANT_POOL* cp, int ordem, FILE* output) {
	fprintf(output,"%s[%d]%s\n", tab, ordem,cp->constants[attr.attributeNameIndex-1].type.Utf8.bytes);
	fprintf(output,"%s\tAttribute name index: %d\n", tab,attr.attributeNameIndex);
	fprintf(output,"%s\tAttribute length: %d\n", tab,attr.attributeLength);
	fprintf(output,"%s\tConstant value index: %d\n", tab,attr.info.ConstantValueAttribute.constantvalue_index);
}

static void printScreenCode(struct _attribute_info attr, char *tab, CONSTANT_POOL* cp, int ordem, FILE* output) {
	int k = 0;

	fprintf(output,"%s[%d]%s\n", tab, ordem,cp->constants[attr.attributeNameIndex-1].type.Utf8.bytes);
	fprintf(output,"%s\tAttribute name index: %d\n", tab,attr.attributeNameIndex);
	fprintf(output,"%s\tAttribute length: %d\n", tab,attr.attributeLength);
	fprintf(output,"%s\tBytecode: \n", tab);

	for (int i = 0; i < attr.info.CodeAttribute.code_length; i++)
	{
		fprintf(output,"\t\t\t\t\t%s",instructions[attr.info.CodeAttribute.code[i]].nome);
		for(k = 0; k<instructions[attr.info.CodeAttribute.code[i]].qtd_operandos; k++){
			if(attr.info.CodeAttribute.code[i+k+1] !=0 ){
				fprintf(output," %d",attr.info.CodeAttribute.code[i+k+1]);
			}
		}
		i = i+k;
		fprintf(output,"\n");
	}

	for (int i = 0; i < attr.info.CodeAttribute.attributes_count; i++) {

		fprintf(output, "%s\t[%d]LineNumberTable:\n", tab, i);
		fprintf(output, "%s\t\tAttribute name index:\t%d\n", tab, attr.info.CodeAttribute.attributes[i].attributeNameIndex);
		fprintf(output, "%s\t\tAttribute length:\t%d\n\n", tab, attr.info.CodeAttribute.attributes[i].attributeLength);
		fprintf(output, "%s\t\t\t|Nr.\t|start_pc\t|line_number\t|\n", tab);

		for (int j = 0; j < attr.info.CodeAttribute.attributes[i].info.LineNumberTableAttribute.liner_number_table_length; j++) {
			struct _line_number_table* var = attr.info.CodeAttribute.attributes[i].info.LineNumberTableAttribute.line_number_table;
			fprintf(output, "%s\t\t\t|%d\t|%d\t\t|%d\t\t|\n", tab, j, var[j].start_pc, var[j].line_number);
		}
	}
	//TODO: imprimir tambem: Bytecode,exception , misc e LineNumberTable

}

static void printScreenExceptions(struct _attribute_info attr, char *tab, FILE* output) {
//TODO: MARCUS
}

static void printScreenInnerClasses(struct _attribute_info attr, char *tab, FILE* output) {
//NOT PRINT IN JCLASSLIB
}

static void printScreenSynthetic(struct _attribute_info attr, char *tab, FILE* output) {
//NOTHING
}

static void printScreenSourceFile(struct _attribute_info attr, char *tab, FILE* output) {
	fprintf(output,"%s\tSource file index: %d\n", tab,attr.info.SourceFileAttribute.sourcefile_index);
}

static void printScreenLineNumberTable(struct _attribute_info attr, char *tab, FILE* output) {
//TODO: MARCUS
}

static void printScreenLocalVariableTable(struct _attribute_info attr, char *tab, FILE* output) {
//NOT PRINT IN JCLASSLIB
}

static void printScreenDeprecated(struct _attribute_info attr, char *tab, FILE* output) {
//NOTHING
}

static void printScreenAttribute(struct _attribute_info attr, CONSTANT_POOL* cp, char* tab, int ordem, FILE* output){
	char* tipoNome = (char*)malloc(cp->constants[attr.attributeNameIndex - 1].type.Utf8.tam * sizeof(char));
	strcpy(tipoNome, (char*)cp->constants[attr.attributeNameIndex - 1].type.Utf8.bytes);

	if (strcmp(tipoNome, "ConstantValue") == 0) {
		printScreenConstantValue(attr, tab,cp,ordem,output);
	} else if (strcmp(tipoNome, "Code") == 0) {
		printScreenCode(attr, tab,cp,ordem,output);
	} else if (strcmp(tipoNome, "Exceptions") == 0) {
		printScreenExceptions(attr, tab, output);
	} else if (strcmp(tipoNome, "InnerClasses") == 0) {
		printScreenInnerClasses(attr, tab, output);
	} else if (strcmp(tipoNome, "Synthetic") == 0) {
		printScreenSynthetic(attr, tab, output);
	} else if (strcmp(tipoNome, "SourceFile") == 0) {
		printScreenSourceFile(attr, tab,output);
	} else if (strcmp(tipoNome, "LineNumberTable") == 0) {
		printScreenLineNumberTable(attr, tab, output);
	} else if (strcmp(tipoNome, "LocalVariableTable") == 0) {
		printScreenLocalVariableTable(attr, tab, output);
	} else { // Deprecated
		
		printScreenDeprecated(attr, tab, output);

	}
}
