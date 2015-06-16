#ifndef MODULE_JVM
	#define MODULE_JVM
	#include "../../ClassLoader/classloader.h"

	#define tREFERENCIA 	0
	#define	tBOOLEAN	 	4
	#define	tCHAR 			5
	#define	tFLOAT 			6
	#define	tDOUBLE		 	7
	#define	tBYTE	 		8
	#define	tSHORT	 		9
	#define	tINT	 		10
	#define	tLONG	 		11

	// heap
		typedef struct _heap {
			struct _object {
				CLASS* class;
				struct _object* super;
			}** objects;
			struct _array {
				uint32_t quantidade;
				uint32_t tipo;
				uint32_t element_size;
			}** arrays;

			uint32_t object_count;
			uint32_t array_count;

			struct _object* (*newObject)(CLASS*);
		} HEAP;

	// stack
		typedef struct _stack {
			//campos
			struct _frame* topo;
			struct _stack* proximo;

			//funcoes
			void (*pushFrame)(CLASS*, struct _code_attribute*);
			struct _frame* (*popFrame)();
		} STACK;

	// frame: capítulo 3, seção 3.6 da especificação
		typedef struct _frame {
			// campos
			uint32_t* local_variables;

			struct _operand_stack {
				uint32_t allocated;
				struct _u4pilha {
					uint32_t value;
					struct _u4pilha* next; 
				}* topo;
			} operand_stack;

			CONSTANT_POOL* runtime_constant_pool;
			struct _code_attribute* code_attr;
			CLASS* current_class;
			uint32_t pc;

			// funcoes
			void (*push)(uint32_t);
			uint32_t (*pop)();
			void (*push2)(uint64_t);
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
	FRAME* initFRAME(CLASS*, struct _code_attribute*);
	JVM initJVM();
	extern JVM maquina;
#endif