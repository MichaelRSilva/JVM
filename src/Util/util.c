/*! \file 
	\brief Implementação das Funções Utilitárias para IO
	
	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "util.h"
UTIL MUTIL;

/*! 
	retorna a concatenacao do nome qualificado da classe com base_path e com .class
*/
static char* getClassPath(char* base_path, char* class_name) {
	char* path = (char*)malloc(strlen(base_path)+strlen(class_name) + 8);
	if (strstr(class_name,".class") != NULL) {
		if (strlen(base_path)==0)
			sprintf(path, "%s%s", base_path, class_name);
		else
			sprintf(path, "%s/%s", base_path, class_name);
		return path;
	}
	else if (!strcmp(class_name,"java/lang/Object") 
		|| !strcmp(class_name,"java/lang/System") 
		|| !strcmp(class_name,"java/io/PrintStream")
		|| !strcmp(class_name,"java/lang/String")) {

		sprintf(path, "%s.class", class_name);
		return path;	
	} else {
		sprintf(path, "%s/%s.class", base_path, class_name);
		return path;
	}
}

/*!
	trata se os argumentos passados para o executavel, se esta correto
*/
static int VerificaJVMCMDArgs(int argc, char** argv, char** basePath){
	FILE *fp;

    if (argc < JVMCMDARGCOUNT + 1 || argc > JVMCMDARGCOUNT + 5){
        return E_INVALID_NUM_ARGS; /*ERRO 1: invalido numero de argumentos*/
    }

	for (int i = 1; i <= argc; i++) {
		if (argv[i] != NULL) {
			if (!strcmp(argv[i], "--help")){
				return 1;
			} else if ( argv[i+1] != NULL && !strcmp(argv[i], "-p")) {
				if (!strcmp(argv[i+1], "both")) return 2;
				else if (!strcmp(argv[i+1], "tela")) return 3;
				else if (!strcmp(argv[i+1], "arquivo")) return 4;
				else return E_OPCAO_NAO_EXISTENTE;
			} else if ( argv[i+1] != NULL && !strcmp(argv[i], "-b")) {
				strcpy(*basePath, argv[i+1]);
				i++;
			}
		}
	}

	if ((fp=fopen(getClassPath(*basePath,argv[1]),"rb"))==NULL) {
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

#ifdef DEBUG
	printf("\nLENDO %s: %d", arqNome, (int)fp);
#endif
	if (fp==NULL) {
		printf("\nClass Not Found Exception: %s", arqNome);
		exit(-2000);
	} 
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

// inicializa uma estrutura do tipo UTIL
UTIL initUTIL(void){
	UTIL util;
	
	util.getClassPath = getClassPath;
	util.VerificaJVMCMDArgs = VerificaJVMCMDArgs;
	util.LeArquivo = LeArquivo;
	util.EscreveArquivo = EscreveArquivo;

	return util;
}


















