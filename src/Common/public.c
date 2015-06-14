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
	{ E_VERSION, "ERRO: minor_version precisa ser menor que major_version"},
	{ W_NAOLIDOINTEIRO, "WARNING: bytecode nao lido completamente"},
	{ E_OPCAO_NAO_EXISTENTE, "ERRO: opcao nao existente (ou '-tela' ou 'arquivo')"}
};

const char *returnAccessFlagsName(uint16_t hexadecimal){

	uint16_t mask_public, mask_private, mask_protected, mask_static, mask_final, mask_interface, mask_abstract;

	mask_public = 0x0001;
	mask_private= 0x0002;
	mask_protected = 0x0004;
	mask_static = 0x0008;
	mask_final = 0x0010;
	mask_interface = 0x0200;
	mask_abstract = 0x0400;

	char *retorno = (char *) malloc(sizeof(char) * 50);

	strcpy(retorno, "");

	mask_public = mask_public & hexadecimal;
	mask_private = mask_private & hexadecimal;
	mask_protected = mask_protected & hexadecimal;
	mask_static = mask_static & hexadecimal;
	mask_final = mask_final & hexadecimal;
	mask_interface = mask_interface & hexadecimal;
	mask_abstract = mask_abstract & hexadecimal;

	if(mask_public > 0){
		strcat(retorno, " public");
	}
	if(mask_private > 0){
		strcat(retorno, " private");
	}
	if(mask_protected > 0){
		strcat(retorno, " protected");
	}
	if(mask_static > 0){
		strcat(retorno, " static");
	}
	if(mask_final > 0){
		strcat(retorno, " final");
	}
	if(mask_interface > 0){
		strcat(retorno, " interface");
	}
	if(mask_abstract > 0){
		strcat(retorno, " abstract");
	}

	return retorno;
}

// funcoes globais
long getLong(uint32_t highBytes, uint32_t lowBytes) {
	return ((uint64_t)highBytes) << 32 | lowBytes;
}

double getDouble(uint32_t highBytes, uint32_t lowBytes) {
	uint64_t var = 0, auxVar;
	int sinal = 0, expoente = 0;
	long mantissa = 0;

	var = var | (uint64_t)highBytes;
	var = var << 32;
	var = var | (uint64_t)lowBytes;

	auxVar = var >> 63;

	if(auxVar == 0){
		sinal = 1;
	}else{
		sinal = -1;
	}

	expoente = ((var >> 52) & 0x7ffL);

	if(expoente == 0){
		mantissa = (var & 0xfffffffffffffL) << 1;
	}else{
		mantissa = (var & 0xfffffffffffffL) | 0x10000000000000L;
	}
	
	return sinal*mantissa*(pow(2,(expoente-1075)));
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
