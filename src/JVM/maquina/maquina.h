#ifndef MODULE_JVM
	#define MODULE_JVM
	#include "../../ClassLoader/classloader.h"
	
	// heap
		typedef struct _heap {
			// TODO
		} HEAP;

	// stack
		typedef struct _stack {
			// TODO	
		} STACK;

	// frame
		typedef struct _frame {
			// TODO
		} FRAME;		

	// instructions
		typedef struct _jvminstruction {
			uint16_t qtd_operandos;
			char *nome;
			void (*call)();
		} JVM_INSTRUCTION;

		/// Variável global para acessar as instruções da JVM
		extern const JVM_INSTRUCTION instructions[];

	// JVM
		typedef struct _maquina_java {
			int classes_size;
			int interfaces_size;

			struct _class_arr {
				CLASS** array;
				int size;
			} classes, interfaces;

			HEAP* heap;
			STACK* stack;
			FRAME* frame;

			int (*loadClass)(char*);
		} JVM;
	
	HEAP* initHEAP();
	STACK* initSTACK();
	FRAME* initFRAME();
	JVM initJVM();
	extern JVM maquina;
#endif