#include "maquina.h"

static void push(uint32_t valor) {
	if (maquina.current_frame->operand_stack.allocated == maquina.current_frame->code_attr->max_stack)
		return;
	struct _u4pilha* ref = maquina.current_frame->operand_stack.topo; // armazena referencia ao antigo topo

	maquina.current_frame->operand_stack.topo++; // sobe no stack
	maquina.current_frame->operand_stack.topo->next = ref; // guarda referencia para o proximo topo
	maquina.current_frame->operand_stack.topo->value = valor; // guada o valor do topo
}

static uint32_t pop() {
	uint32_t* toReturn = (uint32_t*)malloc(sizeof(uint32_t)); // valor para retorno
	struct _u4pilha* ref = maquina.current_frame->operand_stack.topo; // topo sera desalocado

	memcpy(toReturn, &(maquina.current_frame->operand_stack.topo->value), sizeof(uint32_t)); // copia bits
	maquina.current_frame->operand_stack.topo = maquina.current_frame->operand_stack.topo->next;
	
	free(ref); // desalocado topo
	return *toReturn;
}

static void push2(uint64_t valor) {
	push(valor >> 32);
	push(valor & 0xffffffff);
}

FRAME* initFRAME(CLASS* class, struct _code_attribute* code_attr) {
	FRAME* frame = (FRAME*)malloc(sizeof(FRAME));
	
	frame->local_variables = (uint32_t*)malloc(code_attr->max_locals*sizeof(uint32_t));

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

