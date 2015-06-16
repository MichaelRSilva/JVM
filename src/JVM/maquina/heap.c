#include "maquina.h"

struct _object* newObject(CLASS* class) {
	if (!class) return NULL;

	struct _object* toAdd = (struct _object*)malloc(sizeof(struct _object));
	toAdd->class = class;
	toAdd->super = newObject(maquina.classes.array[maquina.loadClass(class->getParentName(class))]);

	return toAdd;
}

HEAP* initHEAP() {
	HEAP* toReturn = (HEAP*)malloc(sizeof(HEAP));

	// campos
	toReturn->object_count = 0;
	toReturn->array_count = 0;
	toReturn->Objects = (struct _object**)malloc(sizeof(struct _object*));
	toReturn->arrays = (struct _array**)malloc(sizeof(struct _array*));

	// funcoes
	toReturn->newObject = newObject;
	return toReturn;
}
