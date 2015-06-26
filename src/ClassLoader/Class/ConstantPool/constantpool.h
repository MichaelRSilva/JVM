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

	/*!
		Enum com os atribuicao de nome de tipo com o numero do bytecode que representa esse nome (traduzindo para portugues)
	*/

	enum _tags {
		tExtended = 0,
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

	/*!
		estrutura do constant_info, separada por tipo e sub-structs
	*/
	struct _constant_info {
		uint8_t tag;
		union {
			struct {} Extended;
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

	/*!
		estrutura do constant pool e declaracoes das funcoes internas que podederao ser usadas quando tiver uma variavel desse tipo
	*/
	typedef struct _constant_pool {
		struct _constant_info* constants;

		int (*addConstant)(struct _constant_pool*, int, DADOS* d);
		char* (*getUtf8String)(struct _constant_pool*, int);
		char* (*getClassName)(struct _constant_pool*, int);
		char* (*getAttributeType)(struct _constant_pool*, int);
	} CONSTANT_POOL;
	
	CONSTANT_POOL* initCONSTANT_POOL(int);
	extern CONSTANT_POOL Mconstantpool;
#endif
