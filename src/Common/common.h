/*! \file
	\brief Definicoes de funcoes e inicializadores comuns a todos os modulos.

	Autores: 
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#ifndef MODULE_COMMON
	#define MODULE_COMMON
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdint.h>
	#include <inttypes.h>
	#include <string.h>
	#include <math.h>

	/*!
		facilitar o uso para comparacao de access flags
	*/
	enum _ACCESS_FLAGS {
		mask_public = 0x0001,
		mask_private= 0x0002,
		mask_protected = 0x0004,
		mask_static = 0x0008,
		mask_final = 0x0010,
		mask_interface = 0x0200,
		mask_abstract = 0x0400,
		mask_volatile = 0x0040,
   		mask_transient = 0x0080,
   		mask_native  = 0x0100
	};


	// estruturas para propagacao de erros ao usuario.
		
		/// Associa inteiros com macros para melhor legibilidade dos erros.
		enum _config_error {
			E_SUCCESS = 0, E_INVALID_NUM_ARGS = -1, E_ARGV1_FILE_NOT_EXISTENT = -2, E_CAFEBABE = -3, E_VERSION = -4,
			W_NAOLIDOINTEIRO = -5, E_OPCAO_NAO_EXISTENTE = -6
		};


		/// Associa uma mensagem de erro a um código.
		typedef struct _errordesc {
			int code;
			char *message;
		} ERRORS;

		/// Variável global para acessar as mensagens de erro dado um código.
		extern const ERRORS errordesc[];

	// funcoes globais
		long getLong(uint32_t highBytes, uint32_t lowBytes);
		double getDouble(uint32_t highBytes, uint32_t lowBytes);
		const char *returnAccessFlagsName(uint16_t);

	/// Estrutura para representação de dados como array de bytes.
	/*!
		DADOS define uma estrutura para representacao de dados provenientes de qualquer meio;
		geralmente utilizado para representar um arquivo.
		
		A ideia por traz disso eh de facilitar o acesso as informacoes representadas pelos bytes, pois
		a manipulacao das mesmas é feita através de um array e não um arquivo (evitando problemas com fseek, etc)
	*/
		typedef struct _dados {
			unsigned long int tamanho;
			uint8_t *bytes;
			uint8_t (*le1Byte)(struct _dados*);
			uint16_t (*le2Bytes)(struct _dados*);
			uint32_t (*le4Bytes)(struct _dados*);
		} DADOS;

	// funcoes comuns a todos os modulos

		DADOS initDADOS();
#endif