#ifndef MODULE_FIELD_INFO
	#define MODULE_FIELD_INFO
	#include "../../../Common/common.h"

	
	struct _field_info {
		
		uint16_t access_flags;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		//TODO:  Ponteiro para tabela

	};


	typedef struct _fields {
		struct _field_info* fields;
		int (*addField)(struct _fields*, int, DADOS* d);
	} FIELD_POOL;
	
	FIELD_POOL* initFIELD_POOL();

#endif