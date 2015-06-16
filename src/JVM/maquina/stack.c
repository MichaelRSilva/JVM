#include "maquina.h"

void pushFrame(CLASS* class, struct _code_attribute* code_attr) {
	maquina.stack->proximo = maquina.stack;
	maquina.stack->topo = initFRAME(class, code_attr);
	maquina.current_frame = maquina.stack->topo;
}

FRAME* popFrame(CLASS* class, struct _code_attribute* code_attr) {
	FRAME* aux = maquina.stack->topo;

	maquina.stack = maquina.stack->proximo;
	maquina.current_frame = (maquina.stack != NULL) ? maquina.stack->topo : NULL;

	return aux;
}

STACK* initSTACK() {
	STACK* toReturn = (STACK*)malloc(sizeof(STACK));

	// campos
	toReturn->topo = NULL;
	toReturn->proximo = NULL;

	// funcoes
	toReturn->pushFrame = pushFrame;
	toReturn->popFrame = popFrame;
	return toReturn;
}
