/*! \file
	\brief Implementação das funções comuns a todos os modulos.

	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "common.h"

// inicialização dos erros
const ERRORS errordesc[] = {
	{ E_SUCCESS, ""},
	{ E_INVALID_NUM_ARGS, "ERRO: numero de argumentos invalido"},
	{ E_ARGV1_FILE_NOT_EXISTENT, "ERRO: arquivo nao existente"},
	{ E_CAFEBABE, "ERRO: Isso nao eh uma classe java"},
	{ E_VERSION, "ERRO: minor_version precisa ser menor que major_version"}
};

// funcoes globais
long getLong(uint32_t highBytes, uint32_t lowBytes) {
	return ((long)highBytes) << 32 | lowBytes;
}

double getDouble(uint32_t highBytes, uint32_t lowBytes) {
	uint64_t var = 0;
	int s = 0, e = 0;

	var = var | (uint64_t)highBytes;
	var = var << 32;
	var = var | (uint64_t)lowBytes;

	s = ((var >> 63) == 0) ? 1 : -1;
	e = ((var >> 52) & 0x7ffL);

	long m = (e == 0) ? (var & 0xfffffffffffffL) << 1 : (var & 0xfffffffffffffL) | 0x10000000000000L;
	
	return s*m*(pow(2,(e-1075)));
}

// funcoes do objeto DADOS
static uint8_t le1Byte(DADOS* this) {
	if (this->bytes)
		return *(this->bytes++);
	return 0;
}

static uint16_t le2Bytes(DADOS* this) {
	uint16_t buffer = 0;

	for (int i = 0; i < 2 && this->bytes; i++) {
		buffer = buffer << 8 | *(this->bytes++);
	}

	return buffer;
}

static uint32_t le4Bytes(DADOS* this) {
	uint32_t buffer = 0;

	for (int i = 0; i < 4 && this->bytes; i++) {
		buffer = buffer << 8 | *(this->bytes++);
	}

	return buffer;
}

/// inicializa uma estrutura do tipo DADOS.
DADOS initDADOS(){
	DADOS d;
	d.tamanho = 0l;
	d.bytes = (uint8_t*)malloc(sizeof(uint8_t));
	d.le1Byte = le1Byte;
	d.le2Bytes = le2Bytes;
	d.le4Bytes = le4Bytes;
	return d;
}

const JVM_INSTRUCTIONS instructions[] = {
	{0, 0, NULL, "nop"}, {1, 0, NULL, "aconst_null"}
};





