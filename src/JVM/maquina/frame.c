#include "maquina.h"

/*!
	empilha um valor na pilha de operandos
*/
static void push(uint64_t valor) {
	// printf("\n\t\tentrou no push(); current_frame: %p",maquina.current_frame);
	if (maquina.current_frame->operand_stack.allocated >= maquina.current_frame->code_attr->max_stack) error(E_STACK_OVERFLOW);
	struct _u4pilha* ref = maquina.current_frame->operand_stack.topo; // armazena referencia ao antigo topo

	maquina.current_frame->operand_stack.topo++; // sobe no stack
	maquina.current_frame->operand_stack.topo->next = ref; // guarda referencia para o proximo topo
	maquina.current_frame->operand_stack.topo->value = valor; // guarda o valor do topo
	maquina.current_frame->operand_stack.allocated++;
	// printf("\n\t\tsaiu no push(); valor: %llx;  current_frame: %p", valor, maquina.current_frame);
}

/*!
	desempilha um valor na pilha de operandos
*/
static uint64_t pop() {
	// printf("\n\t\tentrou no pop(); current_frame: %p",maquina.current_frame);
	if (maquina.current_frame->operand_stack.topo == NULL || !maquina.current_frame->operand_stack.allocated) error(E_VOID_OP_STACK);


	uint64_t toReturn = maquina.current_frame->operand_stack.topo->value; // guarda valor do topo
	maquina.current_frame->operand_stack.topo = maquina.current_frame->operand_stack.topo->next;
	maquina.current_frame->operand_stack.allocated--;

	// free(ref); // desalocado topo
	// printf("\n\t\tsaiu no pop(); valor: %llx; current_frame: %p", toReturn,maquina.current_frame);
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
	frame->operand_stack.topo = (struct _u4pilha*)malloc(code_attr->max_stack*sizeof(struct _u4pilha));

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

