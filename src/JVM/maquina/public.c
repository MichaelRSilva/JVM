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

JVM maquina;

static int loadClass(char* name) {
	int toReturn = -1;
	if ((toReturn = getClassIndex(name, maquina.classes)) == -1) {
		CLASS_LOADER* cl = initCLASS_LOADER();

		cl->load(cl, getClassPath(name));
		toReturn = maquina.classes.size;
		expandClassArray();
		maquina.classes.array[maquina.classes.size++] = cl->class;

 		loadParentClasses(); // insere em maquina.classes todas as classes pai ainda nao carregadas em maquina.clasess
 		loadInterfaces(cl->class); // insere em maquinas.interfaces todas as interfaces ainda nao carregadas em maquina.interfaces

		free(cl);
	}

	return toReturn;
}

JVM initJVM() {
	JVM toReturn;

	toReturn.classes.size = 0;
	toReturn.interfaces.size = 0;
	
	toReturn.classes.array = (CLASS**)malloc(sizeof(CLASS*));
	toReturn.interfaces.array = NULL;

	toReturn.loadClass = loadClass;
	return toReturn;
}


