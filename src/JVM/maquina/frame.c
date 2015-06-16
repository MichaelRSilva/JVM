#include "maquina.h"

// TODO


void push(uint32_t valor) {
	maquina.current_frame->operand_stack[++maquina.current_frame->operand_stack_top] = valor;
}

uint32_t pop() {
	return maquina.current_frame->operand_stack[maquina.current_frame->operand_stack_top--];
}

FRAME* initFRAME() {
	
	return NULL;
}
