/*! \file 
	\brief Definição das Funções Utilitárias para IO
	
	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#ifndef MODULE_UTIL
	#define MODULE_UTIL
	#include "../common/common.h"
	#include "../ClassLoader/classloader.h"
	
	// Macros
		#define JVMCMDARGCOUNT 1 /// Quantidade de argumentos que a JVM aceita.
		#define LEITOREXIBIDORCMDARGCOUNT 1 /// Quantidade de argumentos que o Leitor/Exibidor de bytecode aceita.

	/// Encapsulamento das funcoes do modulo util.
	/*!
		UTIL é responsável por encapsular as funções auxiliares dentro de uma estrutura,
		simulando assim uma falsa orientação a objetos.

		Isso traz mais legibilidade ao código.
	*/	
	typedef struct _util {
		/// Verifica se os argumentos passados por linha de comando para a JVM estão ok.
		/*!
			@param %1 quantidade de argumentos.
			@param %2 os argumentos passado por linha de comando.
			@return Código de erro, onde sucesso é representado por E_SUCCESS
		*/
		int (*VerificaJVMCMDArgs)(int, char**);

		/// Verifica se os argumentos passados por linha de comando para o Leitor/Exibidor de bytecode estão ok.
		/*!
			@param %1 quantidade de argumentos.
			@param %2 os argumentos passado por linha de comando.
			@return Código de erro, onde sucesso é representado por E_SUCCESS
		*/
		int (*VerificaLeitorExibidorCMDArgs)(int, char**);

		/// Converte um arquivo numa estrutura DADOS
		/*!
			@param %1 o caminho para o arquivo
			@return Uma estrutura DADOS representando o arquivo
		*/
		DADOS (*LeArquivo)(char*);

		/// Converte uma estrutura DADOS num arquivo
		/*!
			@param %1 os dados
			@param %2 o nome do arquivo a ser criado
			@return Código de erro, onde sucesso é representado por E_SUCCESS
		*/
		int (*EscreveArquivo)(DADOS, char*); // escreverArquivo(dados, nome do arquivo) retorna codigo de erro ou sucesso

		//Imprime conteudo do .class na tela
		/*!
			@param %1 a struct que representa a classe do java
			@return 0
		*/
		int (*PrintScreen)(CLASS*);

		//Imprime conteudo do .class no arquivo
		/*!
			@param %1 a struct que representa a classe do java
			@return 0
		*/
		int (*PrintFile)(CLASS*);

		//Imprime conteudo do .class em html
		/*!
			@param %1 a struct que representa a classe do java
			@return 0
		*/
		int (*PrintHTML)(CLASS*);


	} UTIL;

	/// "instancia" uma nova "classe" util
	/*!
		@return Uma estrutura UTIL contendo os métodos auxiliares para IO
	*/
	UTIL getUTILInstance(void);
#endif