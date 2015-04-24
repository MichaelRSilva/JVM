/*
Abilio Esteves Calegario de Oliveira - 10/0006132
Marcus da Silva Ferreira - 10/0056881
Michael Rodrigues - 09/0126432

JVM - Software Basico 1/2015

common.h: definicoes de funcoes e inicializadores comuns a todos os modulos
*/
#ifndef MODULE_COMMON
	#define MODULE_COMMON
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdint.h>
	#include <inttypes.h>
	#include <string.h>

	/*estruturas de erros*/
		enum _config_error {
			E_SUCCESS = 0,
			E_INVALID_NUM_ARGS = -1,
			E_ARGV1_FILE_NOT_EXISTENT = -2
		};

		typedef struct _errordesc {
			int code;
			char *message;
		} ERRORS;

		extern ERRORS errordesc[];

	/*estrutura para dados de arquivos*/
		typedef struct _dados {
			unsigned long int tamanho;
			uint8_t *bytes;
		} DADOS;

	/*funcoes comuns a todos os modulos*/
		DADOS initDADOS(); // initDADOS(nome do arquivo) retorna uma estrutura DADOS
#endif