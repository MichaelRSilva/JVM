#include "maquina.h"

void pushFrame(CLASS* class, struct _code_attribute* code_attr) {
	printf("\n\t\t\tentrou pushFrame:  %s", class->getName(class));
	struct _frame_pilha* newTopo = (struct _frame_pilha*)malloc(sizeof(struct _frame_pilha));

	newTopo->value = initFRAME(class, code_attr);
	newTopo->next = maquina.stack->topo;
	maquina.stack->topo = newTopo;

	maquina.current_frame = maquina.stack->topo->value;
	maquina.stack->count++;
	printf("\n\t\t\tsaiu pushFrame:  %s", class->getName(class));
}

void popFrame() {
	printf("\n\t\t\tentrou popFrame: current_frame: %p", maquina.current_frame);
	if (maquina.stack->count == 0) { printf("\nStack de Frames VAZIA!"); exit(123123);}

	struct _frame_pilha* aux = maquina.stack->topo->next;
	free(maquina.stack->topo);
	
	maquina.stack->topo = aux;
	maquina.stack->count--;
	maquina.current_frame = (aux!=NULL)?aux->value:NULL;
	printf("\n\t\t\tsaiu popFrame: current_frame: %p", maquina.current_frame);
}

/*!
	inicia a pilha de frames, onde cada metodo tem um frame 
*/
STACK* initSTACK() {
	STACK* toReturn = (STACK*)malloc(sizeof(STACK));

	// campos
	toReturn->topo = NULL;
	toReturn->count = 0;
	toReturn->have_returned = 0;

	// funcoes
	toReturn->pushFrame = pushFrame;
	toReturn->popFrame = popFrame;

	return toReturn;
}
