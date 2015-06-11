#include "jvm.h"
#include "private.c"

int loadParentClasses(JVM* maquina, CLASS* class, UTIL* util) {
	char* parentName = getParentName(class);
	CLASS_LOADER *cl = initCLASS_LOADER();
	int flag;

	if ((flag = classIndex(parentName, maquina->classes)) > -1) {
		// adiciona classe pai a maquina->classes
		
		cl->load(cl, util->LeArquivo(getParentPath(class, parentName)));
		maquina->classes[maquina->class_array_size++] = cl->class;
	}

	// TODO: chamada recursiva para loadParentClasses

	return E_SUCCESS;
}

JVM initJVM() {
	JVM toReturn;

	toReturn.class_array_size = 0;
	toReturn.classes = (CLASS**)malloc(sizeof(CLASS));
	toReturn.classes[0] = (CLASS*)malloc(sizeof(CLASS));

	toReturn.loadParentClasses = loadParentClasses;
	return toReturn;
}

