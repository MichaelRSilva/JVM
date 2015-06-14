#include "maquina.h"

static int getClassIndex(char* class_name, struct _class_arr classes) {
	if (classes.array == NULL) return -1;

	for(int i=0; i < classes.size; i++){
		char *aux = classes.array[i]->getName(classes.array[i]);
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

static void expandClassArray(JVM* maquina) {
	maquina->classes.array = (CLASS**)realloc(maquina->classes.array,(maquina->classes.size+1)*sizeof(CLASS*));
}

static void expandInterfaceArray(JVM* maquina) {
	maquina->interfaces.array = (CLASS**)realloc(maquina->interfaces.array,(maquina->interfaces.size+1)*sizeof(CLASS*));
}
