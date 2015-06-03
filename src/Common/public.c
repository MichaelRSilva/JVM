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
	{ W_NAOLIDOINTEIRO, "WARNING: bytecode nao lido completamente"}
};

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

static void nop(PILHA* pilha, ...){
	// TODO
}

const JVM_INSTRUCTIONS instructions[] = {
	{0, NULL, "nop", nop},
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
	{1, NULL, "bipush"},
	{2, NULL, "sipush"},
	{1, NULL, "ldc"},
	{2, NULL, "ldc_w"},
	{2, NULL, "ldc2_w"},
	{1, NULL, "iload"},
	{1, NULL, "lload"},
	{1, NULL, "fload"},
	{1, NULL, "dload"},
	{1, NULL, "aload"},
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
	{1, NULL, "istore"},
	{1, NULL, "lstore"},
	{1, NULL, "fstore"},
	{1, NULL, "dstore"},
	{1, NULL, "astore"},
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
	{0, NULL, "dup2"},
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
	{0, NULL, "irem"},
	{0, NULL, "lrem"},
	{0, NULL, "frem"},
	{0, NULL, "drem"},
	{0, NULL, "ineg"},
	{0, NULL, "lneg"},
	{0, NULL, "fneg"},
	{0, NULL, "dneg"},
	{0, NULL, "ishl"},
	{0, NULL, "lshl"},
	{0, NULL, "ishr"},
	{0, NULL, "lshr"},
	{0, NULL, "iushr"},
	{0, NULL, "lushr"},
	{0, NULL, "iand"},
	{0, NULL, "land"},
	{0, NULL, "ior"},
	{0, NULL, "lor"},
	{0, NULL, "ixor"},
	{0, NULL, "lxor"},
	{2, NULL, "iinc"},
	{0, NULL, "i2l"},
	{0, NULL, "i2f"},
	{0, NULL, "i2d"},
	{0, NULL, "l2i"},
	{0, NULL, "l2f"},
	{0, NULL, "l2d"},
	{0, NULL, "f2i"},
	{0, NULL, "f2l"},
	{0, NULL, "f2d"},
	{0, NULL, "d2i"},
	{0, NULL, "d2l"},
	{0, NULL, "d2f"},
	{0, NULL, "i2b"},
	{0, NULL, "i2c"},
	{0, NULL, "i2s"},
	{0, NULL, "lcmp"},
	{0, NULL, "fcmpl"},
	{0, NULL, "fcmpg"},
	{0, NULL, "dcmpl"},
	{0, NULL, "dcmpg"},
	{2, NULL, "ifeq"},
	{2, NULL, "ifne"},
	{2, NULL, "iflt"},
	{2, NULL, "ifge"},
	{2, NULL, "ifgt"},
	{2, NULL, "ifle"},
	{2, NULL, "if_icmpeq"},
	{2, NULL, "if_icmpne"},
	{2, NULL, "if_icmplt"},
	{2, NULL, "if_icmpge"},
	{2, NULL, "if_icmpgt"},
	{2, NULL, "if_icmple"},
	{2, NULL, "if_acmpeg"},
	{2, NULL, "if_acmpne"},
	{2, NULL, "goto"},
	{2, NULL, "jsr"},
	{1, NULL, "ret"},
	{14, NULL, "tableswitch"},
	{10, NULL, "lookupswitch"},
	{0, NULL, "ireturn"},
	{0, NULL, "lreturn"},
	{0, NULL, "freturn"},
	{0, NULL, "dreturn"},
	{0, NULL, "areturn"},
	{0, NULL, "return"},
	{2, NULL, "getstatic"},
	{2, NULL, "putstatic"},
	{2, NULL, "getfield"},
	{2, NULL, "putfield"},
	{2, NULL, "invokevirtual"},
	{2, NULL, "invokespecial"},
	{2, NULL, "invokestatic"},
	{4, NULL, "invokeinterface"},
	{0, NULL, NULL},
	{2, NULL, "new"},
	{1, NULL, "newarray"},
	{2, NULL, "anewarray"},
	{0, NULL, "arraylength"},
	{0, NULL, "athrow"},
	{0, NULL, "checkcast"},
	{0, NULL, "instanceof"},
	{0, NULL, "monitorenter"},
	{0, NULL, "monitorexit"},
	{7, NULL, "wide"},
	{3, NULL, "multianewarray"},
	{2, NULL, "ifnull"},
	{2, NULL, "ifnonnull"},
	{4, NULL, "goto_w"},
	{4, NULL, "jsr_w"}
};





