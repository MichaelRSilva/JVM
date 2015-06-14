#ifndef MODULE_JVM
	#define MODULE_JVM
	#include "../../ClassLoader/classloader.h"
	
	typedef struct _jvminstruction {
		uint16_t qtd_operandos;
		char *nome;
		void (*call)();
	} JVM_INSTRUCTION;


	/// Variável global para acessar as JVM instructions
	extern const JVM_INSTRUCTION instructions[];

	typedef struct _maquina_java {
		int classes_size;
		int interfaces_size;

		struct _class_arr {
			CLASS** array;
			int size;
		} classes, interfaces;

		int (*loadClass)(char*);
	} JVM;
	
	JVM initJVM();

	extern JVM maquina;

#endif