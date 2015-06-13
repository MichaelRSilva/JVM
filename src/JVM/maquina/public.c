/*! \file
	\brief Main entry point da Máquina Virtual

	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "maquina.h"
#include "private.c"

static int loadParentClasses(JVM* maquina, CLASS* class, UTIL* util) {
	char* parentName = class->getParentName(class);
	CLASS_LOADER *cl = initCLASS_LOADER();
	int flag = 0;

	// adiciona parent a maquina->classes caso parent nao exista 
	if (getClassIndex(maquina->classes, parentName) == -1) {
		expandClassArray(maquina->classes, maquina->classes_size);
		cl->load(cl, util->LeArquivo(getClassPath(parentName)));

		maquina->classes[maquina->classes_size++] = cl->class;
		if (maquina->classes[maquina->classes_size-1]->super_class != 0) {
			flag = loadParentClasses(maquina, maquina->classes[maquina->classes_size-1], util);
		}
	}

	return flag;
}

static int loadInterfaces(JVM* maquina, CLASS* class, UTIL* util) {
	int interfacesCount = class->interfaces_count;
	CLASS_LOADER *cl = initCLASS_LOADER();

	for(int i=0; i<interfacesCount; i++){
		maquina->interfaces = (CLASS**)realloc(maquina->interfaces,(maquina->interfaces_size+1)*sizeof(CLASS*));
		char* name = class->getInterfaceName(class, i);
		
		if (getClassIndex(maquina->interfaces, name) == -1) {
			expandClassArray(maquina->interfaces, maquina->interfaces_size);
			cl->load(cl, util->LeArquivo(getClassPath(name)));
			maquina->interfaces[maquina->interfaces_size++] = cl->class;
		}
		
	}

	return E_SUCCESS;
}

JVM initJVM() {
	JVM toReturn;

	toReturn.classes_size = 0;
	toReturn.interfaces_size = 0;
	
	toReturn.classes = (CLASS**)malloc(sizeof(CLASS*));
	toReturn.interfaces = NULL;

	toReturn.loadParentClasses = loadParentClasses;
	toReturn.loadInterfaces = loadInterfaces; 
	return toReturn;
}


