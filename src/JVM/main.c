/*! \file
	\brief Define entry point da maquina virtual java

	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "../Common/common.h"
#include "../Util/util.h"
#include "maquina/maquina.h"

/*!
	cria o executavel da maquina virtual, e chama todas as funcoes para finalmente executar os codes (bytecode)
*/
int main(int argc, char **argv) {
	int flag;
	UTIL util = getUTILInstance();

	if(!(flag = util.VerificaLeitorExibidorCMDArgs(argc, argv))) {
		maquina = initJVM();

		/*!
			carrega o .class passado por argumento
		*/
		maquina.loadClass(argv[1]);
		maquina.run();
	}
	
	printf("%s", errordesc[abs(flag)].message);
	return 0;
}
