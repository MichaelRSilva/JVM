/*! \file
	\brief Main entry point da Máquina Virtual

	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "../util/util.h"

int main(int argc, char **argv) {
	int flag;
	UTIL util = getUTILInstance();

	if(!(flag = util.VerificaJVMCMDArgs(argc, argv))) {
		// TODO
	} else {
		printf("%s", errordesc[abs(flag)].message);
	}

	return 0;
}