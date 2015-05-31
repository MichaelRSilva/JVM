#ifndef MODULE_FIELD_INFO
	#define MODULE_FIELD_INFO
	#include "../../../Common/common.h"
	
	typedef struct _field_info {
		
		uint16_t access_flags;
		uint16_t name_index;
		uint16_t descriptor_index;
		uint16_t attributes_count;

	} FIELD_INFO;

	FIELD_INFO** initFIELD_INFO();
#endif
