#include "maquina.h"

static int getClassIndex(CLASS** array, char* class_name) {

	for(int i=0; array[i]; i++){
		char *aux = array[i]->getName(array[i]);
		if(!strcmp(class_name,aux)){
			return i;
		}
	}

	return -1;
}

static char* getClassPath(char* className) {
	char* path = (char*)malloc(strlen(className) + 7);
	sprintf(path, "%s.class", className);
	return path;
}

static void expandClassArray(CLASS** array, int size) {
	array = realloc(array, (size+1)*sizeof(CLASS*));
}
