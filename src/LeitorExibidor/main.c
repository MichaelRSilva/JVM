/*! \file
	\brief Main entry point do Leitor/Exibidor de bytecode

	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "../util/util.h"
#include "../ClassLoader/classloader.h"

int main(int argc, char **argv) {
	int flag;
	UTIL util = getUTILInstance();
	CLASS_LOADER* cl = initCLASS_LOADER();

	if(!(flag = util.VerificaLeitorExibidorCMDArgs(argc, argv)) && !(flag = cl->load(cl, util.LeArquivo(argv[1])))) {
		cl->print(cl);

		// TODO

	}

	printf("%s", errordesc[abs(flag)].message);
	return 0;
}
