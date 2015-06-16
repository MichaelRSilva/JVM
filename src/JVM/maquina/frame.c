#include "maquina.h"

static void push(uint32_t valor) {
	maquina.current_frame->operand_stack.array[++maquina.current_frame->operand_stack.topo] = valor;
}

static uint32_t pop() {
	return maquina.current_frame->operand_stack.array[maquina.current_frame->operand_stack.topo--];
}

static void push2(uint64_t valor) {
	push(valor >> 32);
	push(valor & 0xffffffff);
}

FRAME* initFRAME(CLASS* class, struct _code_attribute* code_attr) {
	FRAME* frame = (FRAME*)malloc(sizeof(FRAME));
	
	frame->local_variables = (uint32_t*)malloc(code_attr->max_locals*sizeof(uint32_t));

	frame->operand_stack.base = 0;
	frame->operand_stack.topo = 0;

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

