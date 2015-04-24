/*
Abilio Esteves Calegario de Oliveira - 10/0006132
Marcus da Silva Ferreira - 10/0056881
Michael Rodrigues - 09/0126432

JVM - Software Basico 1/2015

main.c: entry point da JVM
*/
#include "../util/util.h"

int main (int argc, char **argv) {
	int flag;
	UTIL util = getUTILInstance();

	if(!(flag = util.VerificaJVMCMDArgs(argc, argv))) {

	} else {
		printf("%s", errordesc[abs(flag)].message);
	}

	return 0;
}