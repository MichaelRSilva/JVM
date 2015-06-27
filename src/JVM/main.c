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
#include "misc.c"

UTIL MUTIL;
void imprimeHelper();

/*!
	cria o executavel da maquina virtual, e chama todas as funcoes para finalmente executar os codes (bytecode)
*/
int main(int argc, char **argv) {
	int flag;
	MUTIL = initUTIL();
	maquina = initJVM();

	if((flag = MUTIL.VerificaJVMCMDArgs(argc, argv, &maquina.basePath)) >= 0) {
		if (flag > 0) {
			switch (flag) {
				case 1:
					imprimeHelper(); 
					return 0;
					break;
				case 2: {
					CLASS_LOADER* cl = initCLASS_LOADER();
					cl->load(cl, MUTIL.getClassPath(maquina.basePath,argv[1]));
					FILE* fp = fopen("output.txt","w");
					PrintClass(cl->class, stdout);
					PrintClass(cl->class, fp);
					fclose(fp);
					return 0;
					break;
				}
				case 3: {
					CLASS_LOADER* cl = initCLASS_LOADER();
					cl->load(cl, MUTIL.getClassPath(maquina.basePath,argv[1]));
					PrintClass(cl->class, stdout);
					return 0;
					break;
				}
				case 4: {
					FILE* fp = fopen("output.txt","w");
					CLASS_LOADER* cl = initCLASS_LOADER();
					cl->load(cl, MUTIL.getClassPath(maquina.basePath,argv[1]));
					PrintClass(cl->class, fp);
					fclose(fp);
					return 0;
					break;
				}
				default: {
					break;
				}	
			}
		}

		maquina.loadClass(argv[1]); // conduz o load, o link e o initialize da classe passada por linha de comando
		maquina.run(); // executa a classe passada por linha de comando, a partir de seu metodo main (se existir)

	}
	
	printf("%s", (flag<0)?errordesc[abs(flag)].message:"");
	return 0;
}

void imprimeHelper() {
	printf("JVM - Abilio, Marcus e Michael @ UnB\n");
	printf("----------\n");
	printf("\nUSO Geral: JVM.exe <nome da classe>.class [opcoes]\n\n");
	printf("OPCOES:\n");
	printf("  --help\t\t\t'lista as linhas de comando disponiveis'\n" );
	printf("  -p <[both|tela|arquivo]>\t'indica querer ler e exibir Bytecode'\n" );
	printf("  -b <base path>\t\t'indica o diretorio onde a classe se encontra'\n");
	printf("\t\t\t\t (caso vazio, assume a pasta de execucao da JVM)\n");
	printf("\t\t\t\t (c.c., nome da classe nao pode conter path)\n");
	printf("----------\n");
}
