/*! \file
	\brief Define funcoes associadas a uma "instancia" da maquina virtual java

	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "maquina.h"
#include "private.c"

static int loadParentClasses(JVM* maquina) {
	CLASS* class = maquina->classes.array[maquina->classes.size-1];
	char* parentName = class->getParentName(class);
	CLASS_LOADER *cl = initCLASS_LOADER();
	int flag = 0;

	// insere parent em maquina->classes caso parent ainda nao esteja carregado 
	if (getClassIndex(parentName, maquina->classes) == -1) {
		expandClassArray(maquina);
		cl->load(cl, getClassPath(parentName));

		maquina->classes.array[maquina->classes.size++] = cl->class;
		if (maquina->classes.array[maquina->classes.size-1]->super_class != 0) {
			flag = loadParentClasses(maquina);
		}
	}

	return flag;
}

static int loadInterfaces(JVM* maquina, CLASS* class) {
	int interfacesCount = class->interfaces_count;
	CLASS_LOADER *cl = initCLASS_LOADER();

	for(int i=0; i<interfacesCount; i++){
		char* name = class->getInterfaceName(class, i);
		
		if (getClassIndex(name, maquina->interfaces) == -1) {
			expandInterfaceArray(maquina);
			cl->load(cl, getClassPath(name));
			maquina->interfaces.array[maquina->interfaces.size++] = cl->class;
		}
		
	}

	return E_SUCCESS;
}

JVM initJVM() {
	JVM toReturn;

	toReturn.classes.size = 0;
	toReturn.interfaces.size = 0;
	
	toReturn.classes.array = (CLASS**)malloc(sizeof(CLASS*));
	toReturn.interfaces.array = NULL;

	toReturn.loadParentClasses = loadParentClasses;
	toReturn.loadInterfaces = loadInterfaces; 
	return toReturn;
}


