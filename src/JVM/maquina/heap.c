#include "maquina.h"

/*!
	adiciona um objeto na heap
*/
// static struct _object* addObject(struct _object* obj) {
// 	maquina.heap->objects = realloc(maquina.heap->objects, (maquina.heap->object_count+1)*sizeof(struct _object*));
// 	maquina.heap->objects[maquina.heap->object_count++] = obj;
// 	return obj;
//}

/*!
	adiciona um array na heap
*/
// static struct _array* addArray(struct _array* arr) {
// 	maquina.heap->arrays = realloc(maquina.heap->arrays, (maquina.heap->array_count+1)*sizeof(struct _array*));
// 	maquina.heap->arrays[maquina.heap->array_count++] = arr;
// 	return arr;
// }

/*!
	cria um novo objeto, alocando espaco na memoria para ele
*/
static struct _object* newObject(CLASS* class) {
	if (!class) return NULL;

	struct _object* toReturn = (struct _object*)malloc(sizeof(struct _object));
	toReturn->class = class;
	toReturn->super = newObject(maquina.method_area->classes[maquina.loadClass(class->getParentName(class))]);
	maquina.heap->object_count++;

	return toReturn;
}

/*!
	devolve uma instancia de um array, do tipo passado por parametro
*/
static struct _array* newArray(uint32_t count, uint32_t tipo) {
	struct _array* toReturn = (struct _array*)malloc(2*sizeof(struct _array));
	
	toReturn->quantidade = count;
	toReturn->tipo = tipo;
	switch(tipo) {
		case tREFERENCIA:
			toReturn->element_size = sizeof(uint32_t);
			break;
		case tBOOLEAN:
			toReturn->element_size = sizeof(uint8_t);
			break;
		case tCHAR:
			toReturn->element_size = sizeof(uint16_t);
			break;
		case tFLOAT:
			toReturn->element_size = sizeof(uint32_t);
			break;
		case tDOUBLE:
			toReturn->element_size = sizeof(uint64_t);
			break;
		case tBYTE:
			toReturn->element_size = sizeof(uint8_t);
			break;
		case tSHORT:
			toReturn->element_size = sizeof(uint16_t);
			break;
		case tINT:
			toReturn->element_size = sizeof(uint32_t);
			break;
		case tLONG:
			toReturn->element_size = sizeof(uint64_t);
			break;
		default:
			break;
	}
	toReturn->values = malloc(count* toReturn->element_size);
	maquina.heap->array_count++;

	// printf("\nnew array: %p; TIPO: %d; COUNT: %d; values: %p", toReturn,tipo,count, toReturn->values);
	return toReturn;
}

/*!
	incicia e aloca o heap inicial na memoria
*/
HEAP* initHEAP() {
	HEAP* toReturn = (HEAP*)malloc(sizeof(HEAP));

	// campos
	toReturn->object_count = 0;
	toReturn->array_count = 0;
	toReturn->objects = (struct _object**)malloc(sizeof(struct _object*));
	toReturn->arrays = (struct _array**)malloc(sizeof(struct _array*));

	// funcoes
	toReturn->newObject = newObject;
	toReturn->newArray = newArray;
	return toReturn;
}
