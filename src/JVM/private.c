#include "jvm.h"

int classIndex(char* name, JVM* maquina) {

	for(int i=0; i < (maquina->class_array_size); i++){
		char *aux = (char*)maquina->classes[i]->constant_pool->constants[maquina->classes[i]->constant_pool->constants[maquina->classes[i]->this_class -1].type.Class.nameIndex-1].type.Utf8.bytes;
		if(strcmp(name,aux)){
			return i;
		}
	}
	return -1;
}


char* getParentName(CLASS* class) {
	return (char*)class->constant_pool->constants[class->constant_pool->constants[class->super_class - 1].type.Class.nameIndex - 1].type.Utf8.bytes;
}

char* getPath(char* name) {
	char* path = (char*)malloc(strlen(name) + 7);
	path[strlen(name)+6] = '\0';
	strcpy(path, name);
	strcat(path, ".class");
	return path;
}
