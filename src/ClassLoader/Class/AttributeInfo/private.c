#include "attributeinfo.h"

static uint16_t getAttributeNameIndex(DADOS* d) {
	return d->le2Bytes(d);
}

static uint32_t getAttributeLength(DADOS* d ) {
	return d->le4Bytes(d);
}

static void populateConstantValueAttribute(struct _attribute_info* a, DADOS* d) {

	a->info.ConstantValueAttribute.constantvalue_index = d->le2Bytes(d);
}

static void populateCodeAttribute(struct _attribute_info* a, CONSTANT_POOL* cp, DADOS* d) {
	a->info.CodeAttribute.max_stack = d->le2Bytes(d);
	a->info.CodeAttribute.max_locals = d->le2Bytes(d);
	a->info.CodeAttribute.code_length = d->le4Bytes(d);
	a->info.CodeAttribute.code = (uint8_t*)malloc(a->info.CodeAttribute.code_length * sizeof(uint8_t));
	for (int i = 0; i < a->info.CodeAttribute.code_length; i++) {
		a->info.CodeAttribute.code[i] = d->le1Byte(d);
	}
	a->info.CodeAttribute.exception_table_length = d->le2Bytes(d);
	a->info.CodeAttribute.exception_table = (struct _exception_table*)malloc(a->info.CodeAttribute.exception_table_length * sizeof(struct _exception_table));
	for (int i = 0; i < a->info.CodeAttribute.exception_table_length; i++) {
		a->info.CodeAttribute.exception_table[i].start_pc = d->le2Bytes(d);
		a->info.CodeAttribute.exception_table[i].end_pc = d->le2Bytes(d);
		a->info.CodeAttribute.exception_table[i].handler_pc = d->le2Bytes(d);
		a->info.CodeAttribute.exception_table[i].catch_type = d->le2Bytes(d);
	}
	a->info.CodeAttribute.attributes_count = d->le2Bytes(d);

	ATTRIBUTE_POOL* code_atts = initATTRIBUTE_POOL(a->info.CodeAttribute.attributes_count);
	for (int i = 0; i < a->info.CodeAttribute.attributes_count; i++) {
		code_atts->addAttribute(code_atts, cp, i, d);
	}
	a->info.CodeAttribute.attributes = code_atts->attributes;
}

static void populateExceptions(struct _attribute_info* a, DADOS* d) {
	a->info.ExeceptionsAttribute.number_of_exceptions = d->le2Bytes(d);
	a->info.ExeceptionsAttribute.exception_index_table = malloc (a->info.ExeceptionsAttribute.number_of_exceptions * sizeof(struct _exception_table));

	for(int i=0; i < a->info.ExeceptionsAttribute.number_of_exceptions ; i++){
		a->info.ExeceptionsAttribute.exception_index_table[i] = d->le2Bytes(d);
	}
}

static void populateInnerClasses(struct _attribute_info* a, DADOS* d) {
	a->info.InnerClassesAttribute.number_of_classes = d->le2Bytes(d);
	a->info.InnerClassesAttribute.classes = malloc (a->info.InnerClassesAttribute.number_of_classes * sizeof(struct _classes));

	for(int i=0; i < a->info.InnerClassesAttribute.number_of_classes ; i++){
		a->info.InnerClassesAttribute.classes[i].inner_class_info_index = d->le2Bytes(d);
		a->info.InnerClassesAttribute.classes[i].outer_class_info_index = d->le2Bytes(d);
		a->info.InnerClassesAttribute.classes[i].inner_name_index = d->le2Bytes(d);
		a->info.InnerClassesAttribute.classes[i].inner_class_access_flags = d->le2Bytes(d);
	}
}

static void populateSynthetic(struct _attribute_info* a, DADOS* d) {
	//NOTHING
}

static void populateSourceFile(struct _attribute_info* a, DADOS* d) {
	a->info.SourceFileAttribute.sourcefile_index = d->le2Bytes(d);
}

static void populateLineNumberTable(struct _attribute_info* a, DADOS* d) {
	a->info.LineNumberTableAttribute.liner_number_table_length = d->le2Bytes(d);
	a->info.LineNumberTableAttribute.line_number_table = (struct _line_number_table*) malloc (a->info.LineNumberTableAttribute.liner_number_table_length * sizeof(struct _line_number_table));

	for(int i=0; i < a->info.LineNumberTableAttribute.liner_number_table_length ; i++){
		a->info.LineNumberTableAttribute.line_number_table[i].start_pc = d->le2Bytes(d);
		a->info.LineNumberTableAttribute.line_number_table[i].line_number = d->le2Bytes(d);
	}
}

static void populateLocalVariableTable(struct _attribute_info* a, DADOS* d) {
	
	a->info.LocalVariableTableAttribute.local_variable_table_length = d->le2Bytes(d);
	a->info.LocalVariableTableAttribute.local_variable_table = malloc (a->info.LocalVariableTableAttribute.local_variable_table_length * sizeof(struct _local_variable_table));

	for(int i=0; i < a->info.InnerClassesAttribute.number_of_classes ; i++){
		a->info.LocalVariableTableAttribute.local_variable_table[i].start_pc = d->le2Bytes(d);
		a->info.LocalVariableTableAttribute.local_variable_table[i].length = d->le2Bytes(d);
		a->info.LocalVariableTableAttribute.local_variable_table[i].name_index = d->le2Bytes(d);
		a->info.LocalVariableTableAttribute.local_variable_table[i].descriptor_index = d->le2Bytes(d);
		a->info.LocalVariableTableAttribute.local_variable_table[i].index = d->le2Bytes(d);
	}
}


static void populateDeprecated(struct _attribute_info* a, DADOS* d) {
	//NOTHING
}
