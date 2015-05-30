/*! \file 
	\brief Implementação das Funções Utilitárias para IO
	
	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "util.h"
#include "private.c"

static int VerificaLeitorExibidorCMDArgs(int argc, char **argv){
	FILE *fp;
    char *arq1name;
    int i;

    if (argc < LEITOREXIBIDORCMDARGCOUNT + 1 || argc > LEITOREXIBIDORCMDARGCOUNT + 1){
        return E_INVALID_NUM_ARGS; /*ERRO 1: invalido numero de argumentos*/
    }
	if ((fp=fopen(argv[1],"rb"))==NULL) {
		return E_ARGV1_FILE_NOT_EXISTENT; /*ERRO 2: argv[2] invalido: arquivo nao existente*/
	}else{
		fclose(fp);
	}
	return E_SUCCESS;
}

static int VerificaJVMCMDArgs(int argc, char** argv){
	FILE *fp;
    char *arq1name;
    int i;

    if (argc < LEITOREXIBIDORCMDARGCOUNT + 1 || argc > LEITOREXIBIDORCMDARGCOUNT + 1){
        return E_INVALID_NUM_ARGS; /*ERRO 1: invalido numero de argumentos*/
    }
	if ((fp=fopen(argv[1],"rb"))==NULL) {
		return E_ARGV1_FILE_NOT_EXISTENT; /*ERRO 2: argv[2] invalido: arquivo nao existente*/
	}else{
		fclose(fp);
	}
	return E_SUCCESS;
}

// le o arquivo passado por linha de comando e retorna um array de bytes
static DADOS LeArquivo(char* arqNome) {
	// inicializacoes
	unsigned long int i=0l;
	DADOS d = initDADOS();
	uint8_t value;
	FILE *fp=fopen(arqNome,"rb");

	// leitura iterativa, byte a byte
	while(fread(&value, sizeof(uint8_t), 1, fp)!=0){
		*(d.bytes + i) = value; i++;
		d.bytes = realloc(d.bytes,(i+1)*sizeof(uint8_t));
	}
	*(d.bytes + i) = (uint8_t)'\0'; // char \0 delimitando o fim do arquivo
	d.tamanho = i;

	fclose(fp);
	return d;
}

// escreve um array de bytes em um arquivo
static int EscreveArquivo(DADOS d, char *arqName){
	// inicializacoes
	FILE *fp = fopen(arqName,"wb");

	// escrita iterativa, byte a byte
	for(unsigned long int i=0l; i < d.tamanho; i++){
		fwrite((d.bytes+i),sizeof(uint8_t),1,fp);
	}

	fclose(fp);
	return E_SUCCESS;
}

//imprime os dados da classe na tela
static int PrintScreen(CLASS_LOADER* this) {

	printf("\nINFORMACOES DA CLASSE\n");
	printf("-------------------------------------------------------------------\n\n");

	printf("Magic Number: \t\t\t0x%x \n",this->class->magic);
	printf("Minor Version: \t\t\t%d \n",this->class->minor_version);
	printf("Major Version: \t\t\t%d \n",this->class->major_version);
	printf("Constant pool count: \t\t%d \n",this->class->constant_pool_count);
	printf("Constant Pool: \n");
	for (int i = 0; i < this->class->constant_pool_count - 1; i++) {
		if (this->class->constant_pool->constants[i].tag == 10) {
			printf("\t[%1d]CONSTANT_Methodref_info:\n", i);
			printf("\t\tClass index: %d\n", this->class->constant_pool->constants[i].type.MethodRef.classIndex);
			printf("\t\tName and type index: %d\n", this->class->constant_pool->constants[i].type.MethodRef.nameTypeIndex);
		}
		// printf("\ttag: %d", this->class->constant_pool->constants[0].tag);
		// if (this->class->constant_pool->constants[i].tag == 1) {
		// 	printf("\t[%d]CONSTANT_Utf8_info:\n", i);
		// 	printf("\t\tLength of byte array: %d", this->class->constant_pool->constants[i].type.Utf8.tam);
		// 	printf("\t\tLength of string: %d", this->class->constant_pool->constants[i].type.Utf8.tam);
		// 	printf("\t\tString: %s", (char*)this->class->constant_pool->constants[i].type.Utf8.bytes);
		// }
	}

	printf("\n-------------------------------------------------------------------");


	printf("\n\n");

	return 0;
}

//imprime os dados da classe no arquivo
static int PrintFile(CLASS_LOADER* this) {

	return 0;
}

//imprime os dados da classe em html
static int PrintHTML(CLASS_LOADER* this) {

	return 0;
}

// inicializa uma estrutura do tipo UTIL
UTIL getUTILInstance(void){
	UTIL util;
	util.VerificaJVMCMDArgs = VerificaJVMCMDArgs;
	util.VerificaLeitorExibidorCMDArgs = VerificaLeitorExibidorCMDArgs;
	util.LeArquivo = LeArquivo;
	util.EscreveArquivo = EscreveArquivo;
	util.PrintScreen = PrintScreen;
	util.PrintFile = PrintFile;
	util.PrintHTML = PrintHTML;

	return util;
}


















