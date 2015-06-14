/*! \file
	\brief Main entry point do Leitor/Exibidor de bytecode

	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "../ClassLoader/classloader.h"
#include "../util/util.h"

int main(int argc, char **argv) {
	int flag;
	UTIL util = getUTILInstance();
	CLASS_LOADER* cl = initCLASS_LOADER();

	if(!(flag = util.VerificaLeitorExibidorCMDArgs(argc, argv))) {
		cl->load(cl, argv[1]);
		if (argv[2] != NULL) {
			if (!strcmp(argv[2],"-tela")){
				util.PrintClass(cl->class, stdout);
			} else {
				FILE* fp = fopen("output.txt","w");
				util.PrintClass(cl->class, fp);
				fclose(fp);
			}
		} else {
			FILE* fp = fopen("output.txt","w");
			util.PrintClass(cl->class, stdout);
			util.PrintClass(cl->class, fp);
			fclose(fp);
		}
	}

	printf("%s", errordesc[abs(flag)].message);
	return 0;
}
