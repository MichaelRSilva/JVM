#include "maquina.h"

struct _object* addObject(struct _object* obj) {
	maquina.heap->objects = realloc(maquina.heap->objects, (maquina.heap->object_count+1)*sizeof(struct _object*));
	maquina.heap->objects[maquina.heap->object_count++] = obj;
	return obj;
}

struct _array* addArray(struct _array* arr) {
	maquina.heap->arrays = realloc(maquina.heap->arrays, (maquina.heap->array_count+1)*sizeof(struct _array*));
	maquina.heap->arrays[maquina.heap->array_count++] = arr;
	return arr;
}

struct _object* newObject(CLASS* class) {
	if (!class) return NULL;

	struct _object* toReturn = (struct _object*)malloc(sizeof(struct _object));
	toReturn->class = class;
	toReturn->super = newObject(maquina.classes.array[maquina.loadClass(class->getParentName(class))]);
	
	return toReturn;
}

struct _array* newArray(uint32_t count, uint32_t tipo) {
	struct _array* toReturn = (struct _array*)malloc(sizeof(struct _array));
	
	toReturn->quantidade = count;
	toReturn->tipo = tipo;
	switch(tipo) {
		case tREFERENCIA:
			toReturn->element_size = 32;
			break;
		case tBOOLEAN:
			toReturn->element_size = 8;
			break;
		case tCHAR:
			toReturn->element_size = 16;
			break;
		case tFLOAT:
			toReturn->element_size = 32;
			break;
		case tDOUBLE:
			toReturn->element_size = 64;
			break;
		case tBYTE:
			toReturn->element_size = 8;
			break;
		case tSHORT:
			toReturn->element_size = 16;
			break;
		case tINT:
			toReturn->element_size = 32;
			break;
		case tLONG:
			toReturn->element_size = 64;
			break;
		default:
			break;
	}

	return toReturn;
}

HEAP* initHEAP() {
	HEAP* toReturn = (HEAP*)malloc(sizeof(HEAP));

	// campos
	toReturn->object_count = 0;
	toReturn->array_count = 0;
	toReturn->objects = (struct _object**)malloc(sizeof(struct _object*));
	toReturn->arrays = (struct _array**)malloc(sizeof(struct _array*));

	// funcoes
	toReturn->newObject = newObject;
	return toReturn;
}
