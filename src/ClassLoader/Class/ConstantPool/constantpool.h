/*! \file
	\brief Definicoes de campos, funcoes e inicializadores do ConstantPool de um arquivo .class

	Autores: 
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#ifndef MODUDLE_CONSTANT_POOL
	#define MODUDLE_CONSTANT_POOL
	#include "../../../Common/common.h"

	enum _tags {
		tContinued = 0,
		tUtf8 = 1,
		tInteger = 3,
		tFloat = 4,
		tLong = 5,
		tDouble = 6,
		tClass = 7,
		tString = 8,
		tFieldRef = 9,
		tMethodRef = 10,
		tInterfaceMethodRef = 11,
		tNameType = 12
	};

	struct _constant_info {
		uint8_t tag;
		union {
			struct {
				char bytes[26]; /*"(large numeric continued)"*/
			} Continued;

			struct {
				uint16_t tam;
				uint8_t* bytes;
			} Utf8;

			struct {
				uint32_t bytes;
			} Integer, Float;

			struct {
				uint32_t lowBytes;
				uint32_t highBytes;
			} Long, Double;

			struct {
				uint16_t nameIndex;
			} Class;

			struct {
				uint16_t stringIndex;
			} String;

			struct {
				uint16_t classIndex;
				uint16_t nameTypeIndex;
			} FieldRef, MethodRef, InterfaceMethodRef;

			struct {
				uint16_t nameIndex;
				uint16_t descriptorIndex;
			} NameType;
		} type;
	};

	typedef struct _constant_pool {
		int* constant_pool_count;
		struct _constant_info* constants;
		void (*addConstant)(struct _constant_pool*, int, DADOS d, int* contador);
	} CONSTANT_POOL;
	
	CONSTANT_POOL* initCONSTANT_POOL(int*);
#endif
