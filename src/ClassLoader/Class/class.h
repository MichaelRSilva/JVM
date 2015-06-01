/*! \file
	\brief Definicoes de funcoes e inicializadores relacionados a classe associada ao arquivo .class

	Autores: 
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#ifndef MODULE_CLASS
	#define MODULE_CLASS
	#include "../../Common/common.h"
	#include "ConstantPool/constantpool.h"
	#include "FieldInfo/fieldinfo.h"
	#include "MethodInfo/methodinfo.h"
	#include "AttributeInfo/attributeinfo.h"

	typedef struct _class {
		// estrutura estatica do arquivo .class
			char* class_file;
			uint32_t magic;
			uint16_t minor_version;
			uint16_t major_version;
			uint16_t access_flags;
			uint16_t this_class;
			uint16_t super_class;
			uint16_t interfaces_count;
			uint16_t* interfaces;

			// quantidade e conteudo do pool de constantes
			uint16_t constant_pool_count;
			CONSTANT_POOL* constant_pool;

			// quantidade e conteudo dos fields
			uint16_t fields_count;
			FIELD_POOL* fields_pool;

			// quantidade e conteudo dos methods
			uint16_t methods_count;
			METHOD_POOL* methods;

			// quantidade e conteudo dos methods
			uint16_t attributes_count;
			ATTRIBUTE_POOL* attribute_pool;

		// funcoes somente visiveis a estrutura _dot_class
			int (*parseDotClass)(struct _class*, DADOS);

	} CLASS;

	CLASS* initCLASS();

#endif