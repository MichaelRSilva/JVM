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
static int PrintClass(CLASS* this, FILE* output) {
	fprintf(output,"\nINFORMACOES DA CLASSE\n");
	fprintf(output,"-------------------------------------------------------------------\n\n");

	fprintf(output,"Magic Number: \t\t\t0x%x \n",this->magic);
	fprintf(output,"Minor Version: \t\t\t%d \n",this->minor_version);
	fprintf(output,"Major Version: \t\t\t%d \n",this->major_version);
	fprintf(output,"Constant pool count: \t\t%d \n",this->constant_pool_count);
	fprintf(output,"Access flags: \t\t\t0x%04x \n", this->access_flags);
	fprintf(output,"This class\t\t\tindice: %d\t=>\t<%s> \n", this->this_class, this->constant_pool->constants[this->constant_pool->constants[this->this_class-1].type.Class.nameIndex - 1].type.Utf8.bytes);
	fprintf(output,"Super class\t\t\tindice: %d\t=>\t<%s> \n", this->super_class, this->constant_pool->constants[this->constant_pool->constants[this->super_class-1].type.Class.nameIndex - 1].type.Utf8.bytes);
	fprintf(output,"Interfaces count: \t\t%d \n", this->interfaces_count);
	fprintf(output,"Fields count: \t\t\t%d \n", this->fields_count);
	fprintf(output,"Methods count: \t\t\t%d \n\n", this->methods_count);
	
	fprintf(output,"Interfaces: \n");
	for (int i = 0; i < this->interfaces_count; i++) {
		fprintf(output,"\tInterface %d: \n", i);
		fprintf(output,"\t\tInterface index: %d\t=>\t<%s>\n", this->interfaces[i], this->constant_pool->constants[this->constant_pool->constants[this->interfaces[i]-1].type.Class.nameIndex-1].type.Utf8.bytes);
	}

	fprintf(output,"Constant Pool: \n");
	for (int i = 0; i < this->constant_pool_count - 1; i++) {
		switch (this->constant_pool->constants[i].tag) {
			case tUtf8:
				fprintf(output,"\t[%d]CONSTANT_Utf8_info:\n", i + 1);
				fprintf(output,"\t\tLength of byte array: %d\n", this->constant_pool->constants[i].type.Utf8.tam);
				fprintf(output,"\t\tLength of string: %d\n", this->constant_pool->constants[i].type.Utf8.tam);
				fprintf(output,"\t\tString: %s\n", (char*)this->constant_pool->constants[i].type.Utf8.bytes);
				break;
			case tInteger:
				fprintf(output,"\t[%d]CONSTANT_Integer_info:\n", i + 1);
				fprintf(output,"\t\tBytes: 0x%08x\n", this->constant_pool->constants[i].type.Integer.bytes);
				fprintf(output,"\t\tInteger: %d\n", this->constant_pool->constants[i].type.Integer.bytes);
				break;
			case tFloat:
				fprintf(output,"\t[%d]CONSTANT_Float_info:\n", i + 1);
				fprintf(output,"\t\tBytes: 0x%08x\n", this->constant_pool->constants[i].type.Float.bytes);
				fprintf(output,"\tFloat: %f\n", (float)this->constant_pool->constants[i].type.Float.bytes);
				break;
			case tLong: {
				fprintf(output,"\t[%d]CONSTANT_Long_info:\n", i + 1);
				fprintf(output,"\t\tHigh Bytes: 0x%08x\n", this->constant_pool->constants[i].type.Long.highBytes);
				fprintf(output,"\t\tLow Bytes: 0x%08x\n", this->constant_pool->constants[i].type.Long.lowBytes);
				fprintf(output,"\t\tLong: %lu\n", getLong(this->constant_pool->constants[i].type.Long.highBytes, this->constant_pool->constants[i].type.Long.lowBytes));
				break;
			}
			case tDouble: {
				fprintf(output,"\t[%d]CONSTANT_Double_info:\n", i + 1);
				fprintf(output,"\t\tHigh Bytes: 0x%08x\n", this->constant_pool->constants[i].type.Long.highBytes);
				fprintf(output,"\t\tLow Bytes: 0x%08x\n", this->constant_pool->constants[i].type.Long.lowBytes);
				long var = getLong(this->constant_pool->constants[i].type.Long.highBytes, this->constant_pool->constants[i].type.Long.lowBytes);
				if (var == 0x7ff0000000000000L) {
					fprintf(output,"\t\tDouble: infinito positivo\n");
				} else if (var == 0xfff0000000000000L) {
					fprintf(output,"\t\tDouble: infinito negativo\n");
				} else if ((var >= 0x7ff0000000000001L && var <= 0x7fffffffffffffffL) || (var <= 0xfff0000000000001L && var >= 0xffffffffffffffffL) ) {
					fprintf(output,"\t\tDouble: NaN\n");
				} else {
					fprintf(output,"\t\tDouble: %f\n", getDouble(this->constant_pool->constants[i].type.Long.highBytes, this->constant_pool->constants[i].type.Long.lowBytes));
				}
				break;
			}
			case tContinued:
				fprintf(output,"\t[%d]%s\n", i+1, this->constant_pool->constants[i].type.Continued.bytes);
				break;
			case tClass:
				fprintf(output,"\t[%1d]CONSTANT_Class_info:\n", i + 1);
				fprintf(output,"\t\tClass name: %d\n", this->constant_pool->constants[i].type.Class.nameIndex);
				break;		
			case tString:
				fprintf(output,"\t[%1d]CONSTANT_String_info:\n", i + 1);
				fprintf(output,"\t\tString: %d\n", this->constant_pool->constants[i].type.String.stringIndex);
				break;		
			case tFieldRef:
				fprintf(output,"\t[%1d]CONSTANT_FieldRef_info:\n", i + 1);
				fprintf(output,"\t\tClass name: %d\n", this->constant_pool->constants[i].type.FieldRef.classIndex);
				fprintf(output,"\t\tName and type: %d\n", this->constant_pool->constants[i].type.FieldRef.nameTypeIndex);
				break;		
			case tMethodRef:
				fprintf(output,"\t[%1d]CONSTANT_Methodref_info:\n", i + 1);
				fprintf(output,"\t\tClass index: %d\n", this->constant_pool->constants[i].type.MethodRef.classIndex);
				fprintf(output,"\t\tName and type index: %d\n", this->constant_pool->constants[i].type.MethodRef.nameTypeIndex);
				break;		
			case tInterfaceMethodRef:
				fprintf(output,"\t[%1d]CONSTANT_InterfaceMethodref_info:\n", i + 1);
				fprintf(output,"\t\tClass index: %d\n", this->constant_pool->constants[i].type.InterfaceMethodRef.classIndex);
				fprintf(output,"\t\tName and type index: %d\n", this->constant_pool->constants[i].type.InterfaceMethodRef.nameTypeIndex);
				break;		
			case tNameType:
				fprintf(output,"\t[%1d]CONSTANT_NameAndType_info:\n", i + 1);
				fprintf(output,"\t\tName Index: %d\n", this->constant_pool->constants[i].type.NameType.nameIndex);
				fprintf(output,"\t\tDescriptor Index: %d\n", this->constant_pool->constants[i].type.NameType.descriptorIndex);
				break;
			default:
				fprintf(output,"\t[%d]\tERROR: %x\n",(i+1),this->constant_pool->constants[i].tag );
				break;	
		}
	}

	fprintf(output,"Fields: \n");
	for (int i = 0; i < this->fields_count; i++) {
		fprintf(output,"\t[%d]%s\n", i,this->constant_pool->constants[this->fields_pool->fields[i].name_index - 1].type.Utf8.bytes);
		
		for(int j=0; j < this->fields_pool->fields[i].attributes_count; j++){
			printScreenAttribute(this->fields_pool->fields[i].attributes[j], this->constant_pool, "\t\t", j, output);
		}
	}


	fprintf(output,"Methods: \n");
	for (int i = 0; i < this->methods_count; i++) {
		fprintf(output,"\t[%d]%s\n", i,this->constant_pool->constants[this->methods_pool->methods[i].name_index - 1].type.Utf8.bytes);
		fprintf(output,"\t\tName Index: %d\n", this->methods_pool->methods[i].name_index);
		fprintf(output,"\t\tDescriptor Index: %d\n", this->methods_pool->methods[i].descriptor_index);
		fprintf(output,"\t\tAcess Flags: %x\n", this->methods_pool->methods[i].access_flags);


		for(int j=0; j < this->methods_pool->methods[i].attributes_count; j++){
			printScreenAttribute(this->methods_pool->methods[i].attributes[j], this->constant_pool, "\t\t\t", j, output);
		}
	}

	fprintf(output,"\n-------------------------------------------------------------------");
	fprintf(output,"\n\n");

	return 0;
}

//imprime os dados da classe no arquivo
static int PrintFile(CLASS* this) {

	return 0;
}

//imprime os dados da classe em html
static int PrintHTML(CLASS* this) {

	return 0;
}

// inicializa uma estrutura do tipo UTIL
UTIL getUTILInstance(void){
	UTIL util;
	util.VerificaJVMCMDArgs = VerificaJVMCMDArgs;
	util.VerificaLeitorExibidorCMDArgs = VerificaLeitorExibidorCMDArgs;
	util.LeArquivo = LeArquivo;
	util.EscreveArquivo = EscreveArquivo;
	util.PrintClass = PrintClass;
	util.PrintHTML = PrintHTML;

	return util;
}


















