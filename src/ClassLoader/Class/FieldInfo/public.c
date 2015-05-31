#include "fieldinfo.h"
#include "private.c"


static int addField(FIELD_POOL* this, int ordem, DADOS* d) {
	int toReturn = 0, count = 0;
	
	//TODO: 
	printf("Access: (((%x)))\n", d->le2Bytes(d));
	printf("Name Index: (((%x)))\n", d->le2Bytes(d));
	printf("Descriptor Index: (((%x)))\n", d->le2Bytes(d));
	count = d->le2Bytes(d);
	printf("Attribute Count: (((%x)))\n", count);

	for(int i =0; i<count; i++){

		d->le4Bytes(d);
		d->le4Bytes(d);

	}


	return toReturn;
}

FIELD_POOL* initFIELD_POOL(int *count) {
	FIELD_POOL* toReturn = (FIELD_POOL*)malloc(sizeof(FIELD_POOL));

	toReturn->fields = (struct _field_info*)malloc((*count - 1)*sizeof(struct _field_info));
	toReturn->addField = addField;

	return toReturn;
}
