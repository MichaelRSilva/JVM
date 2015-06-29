#include "maquina.h"

/*!
	adiciona um objeto no array de objetos para um possível Garbage Collector
*/
static struct _object* addObject(struct _object* obj) {
	maquina.heap->objects = realloc(maquina.heap->objects, (maquina.heap->object_count+1)*sizeof(struct _object*));
	maquina.heap->objects[maquina.heap->object_count++] = obj;
	return obj;
}

/*!
	adiciona um array na no array de arrays para um possível Garbage Collector
*/
static struct _array* addArray(struct _array* arr) {
	maquina.heap->arrays = realloc(maquina.heap->arrays, (maquina.heap->array_count+1)*sizeof(struct _array*));
	maquina.heap->arrays[maquina.heap->array_count++] = arr;
	return arr;
}

/*!
	cria um novo objeto, alocando espaco na memoria para ele
*/
static struct _object* newObject(CLASS* class) {
	if (!class) return NULL;

	struct _object* newObj = (struct _object*)malloc(sizeof(struct _object));	
	newObj->class = class;
	newObj->fields = (uint64_t*)malloc(class->fields_count*sizeof(uint64_t));

	int index = maquina.loadClass(_MCLASS.getParentName(class));

	if(index > -1 ){
		CLASS* parentClass = maquina.method_area->classes[index];		
		newObj->super = newObject(parentClass);
	}else{
		return NULL;
	}

	return addObject(newObj);
}

/*!
	devolve uma instancia de um array, do tipo passado por parametro
*/
static struct _array* newArray(uint32_t count, uint32_t tipo) {
	struct _array* newArr = (struct _array*)malloc(sizeof(struct _array));
	
	newArr->quantidade = count;
	newArr->tipo = tipo;
	switch(tipo) {
		case tREFERENCIA:
			newArr->element_size = sizeof(uint32_t);
			break;
		case tBOOLEAN:
			newArr->element_size = sizeof(uint8_t);
			break;
		case tCHAR:
			newArr->element_size = sizeof(uint16_t);
			break;
		case tFLOAT:
			newArr->element_size = sizeof(uint32_t);
			break;
		case tDOUBLE:
			newArr->element_size = sizeof(uint64_t);
			break;
		case tBYTE:
			newArr->element_size = sizeof(uint8_t);
			break;
		case tSHORT:
			newArr->element_size = sizeof(uint16_t);
			break;
		case tINT:
			newArr->element_size = sizeof(uint32_t);
			break;
		case tLONG:
			newArr->element_size = sizeof(uint64_t);
			break;
		default:
			break;
	}
	newArr->values = malloc(count* newArr->element_size);

	return addArray(newArr);
}

static struct _array* newRefArray(uint32_t count, char* className) {
	struct _array* newArr = newArray(count, tREFERENCIA);

	maquina.loadClass(className);

	return newArr;
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
	toReturn->newRefArray = newRefArray;
	return toReturn;
}
