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

}

static void populateInnerClasses(struct _attribute_info* a, DADOS* d) {

}

static void populateSynthetic(struct _attribute_info* a, DADOS* d) {

}

static void populateSourceFile(struct _attribute_info* a, DADOS* d) {

}

static void populateLineNumberTable(struct _attribute_info* a, DADOS* d) {

}

static void populateLocalVariableTable(struct _attribute_info* a, DADOS* d) {

}

static void populateDeprecated(struct _attribute_info* a, DADOS* d) {

}
