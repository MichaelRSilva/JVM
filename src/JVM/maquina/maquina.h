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

	#define tREFERENCIA_SIZE	4
	#define	tBOOLEAN_SIZE		1
	#define	tCHAR_SIZE			2
	#define	tFLOAT_SIZE			4
	#define	tDOUBLE_SIZE		8
	#define	tBYTE_SIZE			1	
	#define	tSHORT_SIZE			2	
	#define	tINT_SIZE 			4	
	#define	tLONG_SIZE			8

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
			struct _array* (*newArray)(uint32_t, uint32_t);
		} HEAP;

	// stack
		typedef struct _stack {
			//campos
			struct _frame* topo;
			struct _stack* proximo;
			uint32_t count;
			uint8_t have_returned;

			//funcoes
			void (*pushFrame)(CLASS*, struct _code_attribute*);
			struct _frame* (*popFrame)();
		} STACK;

	// frame: capítulo 3, seção 3.6 da especificação
		typedef struct _frame {
			// campos
			uint64_t* local_variables;

			struct _operand_stack {
				uint32_t allocated;
				struct _u4pilha {
					uint64_t value;
					struct _u4pilha* next; 
				}* topo;
			} operand_stack;

			CONSTANT_POOL* runtime_constant_pool;
			struct _code_attribute* code_attr;
			CLASS* current_class;
			uint32_t pc;

			// funcoes
			void (*push)(uint64_t);
			uint64_t (*pop)();
			void (*push2)(uint64_t);
		} FRAME;		

	// method_area
		typedef struct _method_area {
			CLASS **classes, **interfaces;
			uint32_t classes_count, interfaces_count;
		} METHOD_AREA;

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
			// campos
			METHOD_AREA* method_area;
			HEAP* heap;
			STACK* stack;
			FRAME* current_frame;

			// funcoes
			int (*loadClass)(char*);
			void (*verify)(int);
			void (*prepare)(uint32_t);
			void (*link)(int);
			void (*initialize)(int);
			void (*execute)();
			uint32_t (*retrieveFieldIndex)(char*,char*,uint16_t,char*,uint16_t);
			CLASS* (*getClassByName)(char*);
			uint64_t (*getStaticFieldVal)(uint32_t, uint32_t);
			void (*setStaticFieldVal)(uint32_t, uint32_t,uint64_t);
			struct _field_info* (*getObjectField)(struct _object*, uint32_t);
			void (*setObjectField)(struct _object*, uint32_t,uint64_t);
			char* (*getNameConstants)(CLASS*, uint16_t);
			struct _method_info* (*getMethodByNameDesc)(CLASS*, CLASS*, uint16_t);
			int32_t (*getNumParameters)(CLASS*, struct _method_info*) ;
			void (*construirFrame)(CLASS*, struct _method_info*);
			void (*run)();
			int (*loadParentClasses)();
			int (*loadInterfaces)(CLASS* class);
			uint64_t (*getNativeValueForStaticMethod)(struct _method_info*);

		} JVM;
	
	HEAP* initHEAP();
	STACK* initSTACK();
	FRAME* initFRAME(CLASS*, struct _code_attribute*);
	JVM initJVM();

	extern JVM maquina;
#endif