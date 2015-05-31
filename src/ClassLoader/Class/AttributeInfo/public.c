#include "attributeinfo.h"
#include "private.c"

static void addAttribute(ATTRIBUTE_POOL* this, int ordem, DADOS* d) {
	// TODO
}

ATTRIBUTE_POOL* initATTRIBUTE_POOL(int tamanho) {
	ATTRIBUTE_POOL* toReturn = (ATTRIBUTE_POOL*)malloc(sizeof(ATTRIBUTE_POOL));

	toReturn->attributes = (struct _attribute_info*)malloc(tamanho*sizeof(struct _attribute_info));
	toReturn->addAttribute = addAttribute;
	return toReturn;
}
