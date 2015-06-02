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
	{0, NULL, "nop"},
	{0, NULL, "aconst_null"},
	{0, NULL, "iconst_m1"},
	{0, NULL, "iconst_0"},
	{0, NULL, "iconst_1"},
	{0, NULL, "iconst_2"},
	{0, NULL, "iconst_3"},
	{0, NULL, "iconst_4"},
	{0, NULL, "iconst_5"},
	{0, NULL, "lconst_0"},
	{0, NULL, "lconst_1"},
	{0, NULL, "fconst_0"},
	{0, NULL, "fconst_1"},
	{0, NULL, "fconst_2"},
	{0, NULL, "dconst_0"},
	{0, NULL, "dconst_1"},
	{0, NULL, "bipush"},
	{0, NULL, "sipush"},
	{0, NULL, "ldc"},
	{0, NULL, "ldc_w"},
	{0, NULL, "ldc2_w"},
	{0, NULL, "iload"},
	{0, NULL, "lload"},
	{0, NULL, "fload"},
	{0, NULL, "dload"},
	{0, NULL, "aload"},
	{0, NULL, "iload_0"},
	{0, NULL, "iload_1"},
	{0, NULL, "iload_2"},
	{0, NULL, "iload_3"},
	{0, NULL, "lload_0"},
	{0, NULL, "lload_1"},
	{0, NULL, "lload_2"},
	{0, NULL, "lload_3"},
	{0, NULL, "fload_0"},
	{0, NULL, "fload_1"},
	{0, NULL, "fload_2"},
	{0, NULL, "fload_3"},
	{0, NULL, "dload_0"},
	{0, NULL, "dload_1"},
	{0, NULL, "dload_2"},
	{0, NULL, "dload_3"},
	{0, NULL, "aload_0"},
	{0, NULL, "aload_1"},
	{0, NULL, "aload_2"},
	{0, NULL, "aload_3"},
	{0, NULL, "iaload"},
	{0, NULL, "laload"},
	{0, NULL, "faload"},
	{0, NULL, "daload"},
	{0, NULL, "aaload"},
	{0, NULL, "baload"},
	{0, NULL, "caload"},
	{0, NULL, "saload"},
	{0, NULL, "istore"},
	{0, NULL, "lstore"},
	{0, NULL, "fstore"},
	{0, NULL, "dstore"},
	{0, NULL, "astore"},
	{0, NULL, "istore_0"},
	{0, NULL, "istore_1"},
	{0, NULL, "istore_2"},
	{0, NULL, "istore_3"},
	{0, NULL, "lstore_0"},
	{0, NULL, "lstore_1"},
	{0, NULL, "lstore_2"},
	{0, NULL, "lstore_3"},
	{0, NULL, "fstore_0"},
	{0, NULL, "fstore_1"},
	{0, NULL, "fstore_2"},
	{0, NULL, "fstore_3"},
	{0, NULL, "dstore_0"},
	{0, NULL, "dstore_1"},
	{0, NULL, "dstore_2"},
	{0, NULL, "dstore_3"},
	{0, NULL, "astore_0"},
	{0, NULL, "astore_1"},
	{0, NULL, "astore_2"},
	{0, NULL, "astore_3"},
	{0, NULL, "iastore"},
	{0, NULL, "lastore"},
	{0, NULL, "fastore"},
	{0, NULL, "dastore"},
	{0, NULL, "aastore"},
	{0, NULL, "bastore"},
	{0, NULL, "castore"},
	{0, NULL, "sastore"},
	{0, NULL, "pop"},
	{0, NULL, "pop2"},
	{0, NULL, "dup"},
	{0, NULL, "dup_x1"},
	{0, NULL, "dup_x2"},
	{0, NULL, "dup2_x1"},
	{0, NULL, "dup2_x2"},
	{0, NULL, "swap"},
	{0, NULL, "iadd"},
	{0, NULL, "ladd"},
	{0, NULL, "fadd"},
	{0, NULL, "dadd"},
	{0, NULL, "isub"},
	{0, NULL, "lsub"},
	{0, NULL, "fsub"},
	{0, NULL, "dsub"},
	{0, NULL, "imul"},
	{0, NULL, "lmul"},
	{0, NULL, "fmul"},
	{0, NULL, "dmul"},
	{0, NULL, "idiv"},
	{0, NULL, "ldiv"},
	{0, NULL, "fdiv"},
	{0, NULL, "ddiv"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"},
	{0, NULL, "nop"}
};





