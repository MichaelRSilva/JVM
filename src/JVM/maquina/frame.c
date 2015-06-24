#include "maquina.h"

/*!
	empilha um valor na pilha de operandos
*/

static void printOperantStack(char* func) {
#ifdef DEBUG
	printf("\n%s: OPERAND STACK (%p):", func, maquina.current_frame);
	struct _u4pilha aux = *maquina.current_frame->operand_stack.topo;
	
	for (int i = 0; i < maquina.current_frame->operand_stack.allocated; i++) {
		printf(" %llx", aux.value);
		aux = *aux.next;
	}	
	printf("\n");
#endif
}

static void push(uint64_t valor) {
	printOperantStack("push");
	if (maquina.current_frame->operand_stack.allocated >= maquina.current_frame->code_attr->max_stack) error(E_STACK_OVERFLOW);
	struct _u4pilha* ref = maquina.current_frame->operand_stack.topo; // armazena referencia ao antigo topo

	maquina.current_frame->operand_stack.topo = (struct _u4pilha*)malloc(sizeof(struct _u4pilha));
	maquina.current_frame->operand_stack.topo->next = ref; // guarda referencia para o proximo topo
	maquina.current_frame->operand_stack.topo->value = valor; // guarda o valor do topo
	maquina.current_frame->operand_stack.allocated++;
}

/*!
	desempilha um valor na pilha de operandos
*/
static uint64_t pop() {
	printOperantStack("pop");

	if (maquina.current_frame->operand_stack.topo == NULL || !maquina.current_frame->operand_stack.allocated) error(E_EMPTY_STACK);

	uint64_t toReturn = maquina.current_frame->operand_stack.topo->value; // guarda valor do topo
	maquina.current_frame->operand_stack.topo = maquina.current_frame->operand_stack.topo->next;
	maquina.current_frame->operand_stack.allocated--;

	return toReturn;
}
/*!
	empilha um valor na pilha de operandos
*/
static void push2(uint64_t valor) {
	push(valor >> 32);
	push(valor & 0xffffffff);
}

/*!
	incicia e alococa o frame inicial na memoria
*/
FRAME* initFRAME(CLASS* class, struct _code_attribute* code_attr) {
	FRAME* frame = (FRAME*)malloc(sizeof(FRAME));
	
	frame->local_variables = (uint64_t*)malloc(code_attr->max_locals*sizeof(uint64_t));

	frame->operand_stack.allocated = 0;
	frame->operand_stack.topo = NULL;
	printf("\n max stack: %d\n", code_attr->max_stack);

	frame->runtime_constant_pool = class->constant_pool;
	frame->code_attr = code_attr;
	frame->current_class = class;
	frame->pc = 0;

	//funcoes 
	frame->pop = pop;
	frame->push = push;
	frame->push2 = push2;

	return frame;
}

