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
	printf("Access flags: \t\t\t0x%04x \n", this->class->access_flags);
	printf("This class: \t\t\t%d \n", this->class->this_class);
	printf("Super class: \t\t\t%d \n", this->class->super_class);
	printf("Interfaces count: \t\t%d \n", this->class->interfaces_count);
	printf("Fields count: \t\t\t%d \n\n", this->class->fields_count);
	
	printf("Interfaces: \n");
	for (int i = 0; i < this->class->interfaces_count; i++) {
		printf("\tInterface %d: \n", i);
		printf("\t\tInterface index: %d\n", this->class->interfaces[i]);
	}

	printf("Constant Pool: \n");
	for (int i = 0; i < this->class->constant_pool_count - 1; i++) {
		switch (this->class->constant_pool->constants[i].tag) {
			case tUtf8:
				printf("\t[%d]CONSTANT_Utf8_info:\n", i + 1);
				printf("\t\tLength of byte array: %d\n", this->class->constant_pool->constants[i].type.Utf8.tam);
				printf("\t\tLength of string: %d\n", this->class->constant_pool->constants[i].type.Utf8.tam);
				printf("\t\tString: %s\n", (char*)this->class->constant_pool->constants[i].type.Utf8.bytes);
				break;
			case tInteger:
				printf("\t[%d]CONSTANT_Integer_info:\n", i + 1);
				printf("\t\tBytes: 0x%08x\n", this->class->constant_pool->constants[i].type.Integer.bytes);
				printf("\t\tInteger: %d\n", this->class->constant_pool->constants[i].type.Integer.bytes);
				break;
			case tFloat:
				printf("\t[%d]CONSTANT_Float_info:\n", i + 1);
				printf("\t\tBytes: 0x%08x\n", this->class->constant_pool->constants[i].type.Float.bytes);
				printf("\tFloat: %f\n", (float)this->class->constant_pool->constants[i].type.Float.bytes);
				break;
			case tLong: {
				printf("\t[%d]CONSTANT_Long_info:\n", i + 1);
				printf("\t\tHigh Bytes: 0x%08x\n", this->class->constant_pool->constants[i].type.Long.highBytes);
				printf("\t\tLow Bytes: 0x%08x\n", this->class->constant_pool->constants[i].type.Long.lowBytes);
				printf("\t\tLong: %lu\n", getLong(this->class->constant_pool->constants[i].type.Long.highBytes, this->class->constant_pool->constants[i].type.Long.lowBytes));
				break;
			}
			case tDouble: {
				printf("\t[%d]CONSTANT_Double_info:\n", i + 1);
				printf("\t\tHigh Bytes: 0x%08x\n", this->class->constant_pool->constants[i].type.Long.highBytes);
				printf("\t\tLow Bytes: 0x%08x\n", this->class->constant_pool->constants[i].type.Long.lowBytes);
				long var = getLong(this->class->constant_pool->constants[i].type.Long.highBytes, this->class->constant_pool->constants[i].type.Long.lowBytes);
				if (var == 0x7ff0000000000000L) {
					printf("\t\tDouble: infinito positivo\n");
				} else if (var == 0xfff0000000000000L) {
					printf("\t\tDouble: infinito negativo\n");
				} else if ((var >= 0x7ff0000000000001L && var <= 0x7fffffffffffffffL) || (var <= 0xfff0000000000001L && var >= 0xffffffffffffffffL) ) {
					printf("\t\tDouble: NaN\n");
				} else {
					printf("\t\tDouble: %f\n", getDouble(this->class->constant_pool->constants[i].type.Long.highBytes, this->class->constant_pool->constants[i].type.Long.lowBytes));
				}
				break;
			}
			case tContinued:
				printf("\t[%d]%s\n", i+1, this->class->constant_pool->constants[i].type.Continued.bytes);
				break;
			case tClass:
				printf("\t[%1d]CONSTANT_Class_info:\n", i + 1);
				printf("\t\tClass name: %d\n", this->class->constant_pool->constants[i].type.Class.nameIndex);
				break;		
			case tString:
				printf("\t[%1d]CONSTANT_String_info:\n", i + 1);
				printf("\t\tString: %d\n", this->class->constant_pool->constants[i].type.String.stringIndex);
				break;		
			case tFieldRef:
				printf("\t[%1d]CONSTANT_FieldRef_info:\n", i + 1);
				printf("\t\tClass name: %d\n", this->class->constant_pool->constants[i].type.FieldRef.classIndex);
				printf("\t\tName and type: %d\n", this->class->constant_pool->constants[i].type.FieldRef.nameTypeIndex);
				break;		
			case tMethodRef:
				printf("\t[%1d]CONSTANT_Methodref_info:\n", i + 1);
				printf("\t\tClass index: %d\n", this->class->constant_pool->constants[i].type.MethodRef.classIndex);
				printf("\t\tName and type index: %d\n", this->class->constant_pool->constants[i].type.MethodRef.nameTypeIndex);
				break;		
			case tInterfaceMethodRef:
				printf("\t[%1d]CONSTANT_InterfaceMethodref_info:\n", i + 1);
				printf("\t\tClass index: %d\n", this->class->constant_pool->constants[i].type.InterfaceMethodRef.classIndex);
				printf("\t\tName and type index: %d\n", this->class->constant_pool->constants[i].type.InterfaceMethodRef.nameTypeIndex);
				break;		
			case tNameType:
				printf("\t[%1d]CONSTANT_NameAndType_info:\n", i + 1);
				printf("\t\tName Index: %d\n", this->class->constant_pool->constants[i].type.NameType.nameIndex);
				printf("\t\tDescriptor Index: %d\n", this->class->constant_pool->constants[i].type.NameType.descriptorIndex);
				break;
			default:
				printf("\t[%d]\tERROR: %x\n",(i+1),this->class->constant_pool->constants[i].tag );
				break;	
		}
	}

	printf("Fields: \n");
	for (int i = 0; i < this->class->fields_count; i++) {
		printf("\t[%d]%s\n", i,this->class->constant_pool->constants[this->class->fields_pool->fields[i].name_index - 1].type.Utf8.bytes);
		
		for(int j=0; j < this->class->fields_pool->fields[i].attributes_count; j++){
			printScreenAttribute(this->class->fields_pool->fields[i].attributes[j], this->class->constant_pool, "\t\t");
		}
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


















