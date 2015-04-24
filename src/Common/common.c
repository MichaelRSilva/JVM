/*
Abilio Esteves Calegario de Oliveira - 10/0006132
Marcus da Silva Ferreira - 10/0056881
Michael Rodrigues - 09/0126432

JVM - Software Basico 1/2015

common.c: funcoes e inicializadores comuns a todos os modulos
*/
#include "common.h"

// iniciliza os erros
ERRORS errordesc[] = {
	{ E_SUCCESS, ""},
	{ E_INVALID_NUM_ARGS, "ERRO: numero de argumentos invalido"},
	{ E_ARGV1_FILE_NOT_EXISTENT, "ERRO: arquivo nao existente"}
};

// inicializa uma estrutura do tipo DADOS
DADOS initDADOS(char *arqNome){
	DADOS d;
	d.tamanho = 0l;
	d.bytes = (uint8_t*)malloc(sizeof(uint8_t));
	return d;
}