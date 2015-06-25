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
	{ E_OPCAO_NAO_EXISTENTE, "ERRO: opcao nao existente (ou 'tela' ou 'arquivo' ou 'both')"},
	{ E_DOLAR_NOT_SUPPORTED, "ERRO: This JVM does not support file names with the character $. ABORT."},
	{ E_EMPTY_FRAME_STACK, "ERRO: Stack de Frames VAZIA!"},
	{ E_STACK_OVERFLOW, "ERRO: Stack Overflow!"},
	{ E_NO_MAIN_FOUND, "ERRO: Nao foi encontrado nenhuma main!"},
	{ E_EMPTY_STACK, "ERRO: Operand Stack vazio!"},
	{ E_NOTSUPPORTED_VERSION, "ERRO: Versao Java nao suportada!"}
};

void error(int errorcode) {
	printf("\n\n%s\n\n", errordesc[abs(errorcode)].message);
	exit(errorcode);
}

void debug(char* msg) {
	#ifdef DEBUG
		printf("%s", msg);
	#endif
}

/*!
	dado um hexadecimal, devolve uma string com o nome do acesso, principalmente para exibir no leitor-exibidor
*/
const char *returnAccessFlagsName(uint16_t hexadecimal){

	uint16_t imask_public, imask_private, imask_protected, imask_static, imask_final, imask_interface, imask_abstract;


	char *retorno = (char *) malloc(sizeof(char) * 50);

	strcpy(retorno, "");

	imask_public = mask_public & hexadecimal;
	imask_private = mask_private & hexadecimal;
	imask_protected = mask_protected & hexadecimal;
	imask_static = mask_static & hexadecimal;
	imask_final = mask_final & hexadecimal;
	imask_interface = mask_interface & hexadecimal;
	imask_abstract = mask_abstract & hexadecimal;

	if(imask_public > 0){
		strcat(retorno, " public");
	}
	if(imask_private > 0){
		strcat(retorno, " private");
	}
	if(imask_protected > 0){
		strcat(retorno, " protected");
	}
	if(imask_static > 0){
		strcat(retorno, " static");
	}
	if(imask_final > 0){
		strcat(retorno, " final");
	}
	if(imask_interface > 0){
		strcat(retorno, " interface");
	}
	if(imask_abstract > 0){
		strcat(retorno, " abstract");
	}

	return retorno;
}

// funcoes globais
long getLong(uint32_t highBytes, uint32_t lowBytes) {
	return ((uint64_t)highBytes) << 32 | lowBytes;
}

/*!
	pega e trata um double que esta na class, principalmente para exibir e tratar operacoes
*/
double getDouble(uint32_t highBytes, uint32_t lowBytes) {
	
	uint64_t var = 0, auxVar;
	int sinal = 0, expoente = 0;
	uint64_t mantissa = 0;
	double toReturn;

	var = var | (uint64_t)highBytes;
	var = var << 32;
	var = var | (uint64_t)lowBytes;


	double *double_value = malloc(sizeof(double));


	auxVar = (uint64_t)highBytes;
	auxVar = auxVar << 32;
	auxVar |= (uint64_t)lowBytes;

	memcpy(double_value, &auxVar, sizeof(double));

	toReturn = *double_value;
	return toReturn;
}

// funcoes do objeto DADOS
static uint8_t le1Byte(DADOS* this) {
	if (this->bytes)
		return *(this->bytes++);
	return 0;
}

/*!
	leh dois bytes de um objeto do tipo dados
*/
static uint16_t le2Bytes(DADOS* this) {
	uint16_t buffer = 0;

	for (int i = 0; i < 2 && this->bytes; i++) {
		buffer = buffer << 8 | *(this->bytes++);
	}

	return buffer;
}

/*!
	leh 4 bytes de um objeto do tipo dados
*/
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
