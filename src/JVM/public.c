/*! \file
	\brief Main entry point da Máquina Virtual

	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
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

int main(int argc, char **argv) {
	int flag;
	UTIL util = getUTILInstance();
	CLASS_LOADER* cl = initCLASS_LOADER();

	if(!(flag = util.VerificaLeitorExibidorCMDArgs(argc, argv))) {
		if (!(flag = cl->load(cl, util.LeArquivo(argv[1])))) {
			JVM maquina = initJVM();
			maquina.classes[maquina.class_array_size++] = cl->class;
			flag = maquina.loadParentClasses(&maquina, cl->class, &util);

		}
	}
	
	printf("%s", errordesc[abs(flag)].message);
	return 0;
}


