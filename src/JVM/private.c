#include "jvm.h"

int classIndex(char* name, CLASS** classes) {
	// TODO
	return 0;
}

char* getParentName(CLASS* class) {
	return (char*)class->constant_pool->constants[class->constant_pool->constants[class->super_class - 1].type.Class.nameIndex - 1].type.Utf8.bytes;
}

char* getParentPath(CLASS* class, char* parentName) {
	char* path = (char*)malloc(strlen(parentName) + 7);
	strcpy(path, parentName);
	strcat(path, ".class");
	return path;
}
