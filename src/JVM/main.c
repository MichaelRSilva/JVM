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

void imprimeHelper();

/*!
	cria o executavel da maquina virtual, e chama todas as funcoes para finalmente executar os codes (bytecode)
*/
int main(int argc, char **argv) {
	int flag;
	UTIL util = getUTILInstance();

	if((flag = util.VerificaJVMCMDArgs(argc, argv)) >= 0) {
		if (flag > 0) {
			CLASS_LOADER* cl = initCLASS_LOADER();
			cl->load(cl, argv[1]);	

			switch (flag) {
				case 1:
					imprimeHelper(); 
					return 0;
					break;
				case 2: {
					FILE* fp = fopen("output.txt","w");
					PrintClass(cl->class, stdout);
					PrintClass(cl->class, fp);
					fclose(fp);
					break;
				}
				case 3: {
					PrintClass(cl->class, stdout);
					break;
				}
				case 4: {
					FILE* fp = fopen("output.txt","w");
					PrintClass(cl->class, fp);
					fclose(fp);
					break;
				}
			}
		}

		maquina = initJVM(); // inicializa a heap, o method_area, o stack e o current_frame com valores padrões
		maquina.loadClass(argv[1]); // conduz o load, o link e o initialize da classe passada por linha de comando
		maquina.run(); // executa a classe passada por linha de comando, a partir de seu metodo main (se existir)

	}
	
	printf("%s", (flag<0)?errordesc[abs(flag)].message:"");
	return 0;
}

void imprimeHelper() {
	printf("JVM - Abilio, Marcus e Michael @ UnB\n");
	printf("----------\n");
	printf("\nUSO Geral: JVM.exe <input> [opcoes]\n\n");
	printf("OPCOES:\n");
	printf("\t--help\t\t\t\t'lista as linhas de comando disponiveis'\n" );
	printf("\t-p [both|tela|arquivo]\t\tc'indica querer exibir Leitor/Exibidor de Bytecode'\n" );
	printf("----------\n\n");
}
