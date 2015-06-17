
#ifndef MODULE_FIELD_INFO
	#define MODULE_FIELD_INFO
	#include "../../../Common/common.h"
	#include "../AttributeInfo/attributeinfo.h"
	
	struct _field_info {
		
		uint16_t access_flags;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;
		struct _attribute_info* attributes;

	};

	typedef struct _fields {
		struct _field_info* fields;

		int (*addField)(struct _fields*, CONSTANT_POOL*,int, DADOS*);
	} FIELD_POOL;
	
	FIELD_POOL* initFIELD_POOL(int);

#endif