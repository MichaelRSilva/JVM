#include "maquina.h"

static int getClassIndex(char* class_name, JVM* maquina) {
	CLASS** array = maquina->classes;
	if (array == NULL) return -1;

	for(int i=0; i < maquina->classes_size; i++){
		char *aux = array[i]->getName(array[i]);
		if(!strcmp(class_name,aux)){
			return i;
		}
	}

	return -1;
}

static int getInterfaceIndex(char* interface_name, JVM* maquina) {
	CLASS** array = maquina->classes;
	if (array == NULL) return -1;

	for(int i=0; i < maquina->classes_size; i++){
		char *aux = array[i]->getName(array[i]);
		if(!strcmp(interface_name,aux)){
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

static void expandClassArray(JVM* maquina) {
	maquina->classes = (CLASS**)realloc(maquina->classes,(maquina->classes_size+1)*sizeof(CLASS*));
}

static void expandInterfaceArray(JVM* maquina) {
	maquina->interfaces = (CLASS**)realloc(maquina->interfaces,(maquina->interfaces_size+1)*sizeof(CLASS*));
}
