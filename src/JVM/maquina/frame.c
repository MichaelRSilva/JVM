#include "maquina.h"

// TODO

static void push(uint32_t valor) {
	maquina.current_frame->operand_stack.array[++maquina.current_frame->operand_stack.top] = valor;
}

static uint32_t pop() {
	return maquina.current_frame->operand_stack.array[maquina.current_frame->operand_stack.top--];
}

FRAME* initFRAME() {
	FRAME* frame = (FRAME*)malloc(sizeof(FRAME));
	
	frame->pop = pop;
	frame->push = push;
	
	return frame;
}
