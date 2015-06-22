/*! \file
	\brief Definicoes de funcoes e inicializadores do Class Loader

	Autores: 
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#ifndef MODULE_CLASS_LOADER
#define MODULE_CLASS_LOADER
	#include "../Common/common.h"
	#include "../Util/util.h"
	#include "Class/class.h"

	/*! @class
		class_loader tem uma array de classes
	*/
	typedef struct _class_loader {
		CLASS* class;

		CLASS* (*load)(struct _class_loader*, char*);
	} CLASS_LOADER;

	CLASS_LOADER* initCLASS_LOADER();
#endif