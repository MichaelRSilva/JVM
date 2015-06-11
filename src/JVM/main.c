/*! \file
	\brief Main entry point da Máquina Virtual

	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "jvm.h"

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
