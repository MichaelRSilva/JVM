#ifndef MODULE_JVM
	#define MODULE_JVM
	#include "../../ClassLoader/classloader.h"
	
	// heap
		typedef struct _heap {
			struct _object {
				CLASS* class;
				struct _object *super;
			}* Objects;
			struct _array {
				uint32_t ref;
				uint32_t size;
			}* arrays;
		} HEAP;

	// stack
		typedef struct _stack {
			struct _frame* value;
			struct _stack* proximo;
		} STACK;

	// frame: capítulo 3, seção 3.6 da especificação
		typedef struct _frame {
			uint32_t* local_variables;
			uint32_t* operand_stack;
			CONSTANT_POOL* runtime_constant_pool;
			struct _method_info* current_method;
			CLASS* current_class;
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
			FRAME* current_frame;

			int (*loadClass)(char*);
		} JVM;
	
	HEAP* initHEAP();
	STACK* initSTACK();
	FRAME* initFRAME();
	JVM initJVM();
	extern JVM maquina;
#endif