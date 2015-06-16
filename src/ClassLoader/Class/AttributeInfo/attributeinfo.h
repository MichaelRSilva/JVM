/*! \file
	\brief Definicoes de campos, funcoes e inicializadores de estruturas do tipo AttributeInfo de um arquivo .class

	Autores: 
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#ifndef MODULE_ATTRIBUTE_INFO
	#define MODULE_ATTRIBUTE_INFO
	#include "../../../Common/common.h"
	#include "../ConstantPool/constantpool.h"

	struct _exception_table {
		uint16_t start_pc;
		uint16_t end_pc;
		uint16_t handler_pc;
		uint16_t catch_type;
	};

	struct _classes {
		uint16_t inner_class_info_index;
		uint16_t outer_class_info_index;
		uint16_t inner_name_index;
		uint16_t inner_class_access_flags;
	};

	struct _local_variable_table {
		uint16_t start_pc;
		uint16_t length;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t index;
	};

	struct _line_number_table {
		uint16_t start_pc;
		uint16_t line_number;
	};
	
	struct _code_attribute {
		uint16_t max_stack;
		uint16_t max_locals;
		uint32_t code_length;
		uint8_t* code;
		uint16_t exception_table_length;
		struct _exception_table *exception_table;
		uint16_t attributes_count;
		struct _attribute_info* attributes; 
	};
	
	struct _attribute_info {
		uint16_t attributeNameIndex;
		uint32_t attributeLength;
		union {
			struct {
				uint16_t constantvalue_index;
			} ConstantValueAttribute;
			struct _code_attribute CodeAttribute;
			struct {
				uint16_t number_of_exceptions;
				uint16_t* exception_index_table;
			} ExeceptionsAttribute;
			struct {
				uint16_t number_of_classes;
				struct _classes *classes;
			} InnerClassesAttribute;
			struct {} SyntheticAttribute;
			struct {
				uint16_t sourcefile_index;
			} SourceFileAttribute;
			struct {
				uint16_t liner_number_table_length;
				struct _line_number_table *line_number_table;
			} LineNumberTableAttribute;
			struct {
				uint16_t local_variable_table_length;
				struct _local_variable_table *local_variable_table;
			} LocalVariableTableAttribute;
			struct {} DeprecatedAttribute;
		} info;
	};

	typedef struct _attributes {
		struct _attribute_info* attributes;
		void (*addAttribute)(struct _attributes*, CONSTANT_POOL*, int, DADOS*);
	} ATTRIBUTE_POOL;

	ATTRIBUTE_POOL* initATTRIBUTE_POOL(int);
#endif