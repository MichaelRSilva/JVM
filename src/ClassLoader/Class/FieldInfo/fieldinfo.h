
#ifndef MODULE_FIELD_INFO
	#define MODULE_FIELD_INFO
	#include "../../../Common/common.h"
	#include "../AttributeInfo/attributeinfo.h"
	
	/*!
		estrutura _field_info (criacao de tipo para novas variaveis)
	*/
	struct _field_info {
		
		uint16_t access_flags;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		uint64_t value;
		struct _attribute_info* attributes;

	};

	/*!
		fields tem um array de field
	*/
	typedef struct _fields {
		struct _field_info* fields;

		int (*addField)(struct _fields*, CONSTANT_POOL*,int, DADOS*);
	} FIELD_POOL;
	
	FIELD_POOL* initFIELD_POOL(int);
	extern FIELD_POOL Mfieldpool;
#endif