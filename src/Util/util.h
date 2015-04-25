/*
Abilio Esteves Calegario de Oliveira - 10/0006132
Marcus da Silva Ferreira - 10/0056881
Michael Rodrigues - 09/0126432

JVM - Software Basico 1/2015

util.h: definicoes das funcoes utilitarias
*/
#ifndef MODULE_UTIL
	#define MODULE_UTIL
	#include "../common/common.h"
	
	/*definicoes*/
		#define JVMCMDARGCOUNT 1
		#define LEITOREXIBIDORCMDARGCOUNT 1

	// encapsulamento das funcoes do modulo util
	// simulando assim uma falsa orientacao a objetos
	typedef struct _util {
		int (*VerificaJVMCMDArgs)(int, char**); // VerificaJVMCMDArgs(numero de argumentos, vetor de argumentos) retorna codigo de erro ou sucesso
		int (*VerificaLeitorExibidorCMDArgs)(int, char**); // VerificaLeitorExibidorCMDArgs(numero de argumentos, vetor de argumentos) retorna codigo de erro ou sucesso
		DADOS (*LeArquivo)(char*); // lerArquivo(nome do arquivo) retorna array de bytes
		int (*EscreveArquivo)(DADOS, char*); // escreverArquivo(dados, nome do arquivo) retorna codigo de erro ou sucesso
	} UTIL;

	UTIL getUTILInstance(void);
#endif