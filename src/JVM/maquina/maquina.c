/*! \file
	\brief Define funcoes associadas a maquina virtual java

	Autores:
		- Abilio Esteves Calegario de Oliveira - 10/0006132
		- Marcus da Silva Ferreira - 10/0056881
		- Michael Rodrigues - 09/0126432

	JVM - Software Basico 1/2015
*/
#include "instructions.c"
#include "private.c"
#include "heap.c"
#include "stack.c"
#include "frame.c"
#include "method_area.c"

static int loadClass(char* name) {
	int toReturn = -1;
	if ((toReturn = getClassIndex(name)) == -1) {
		CLASS_LOADER* cl = initCLASS_LOADER();

		cl->load(cl, getClassPath(name));
		toReturn = maquina.method_area->classes_count;
		expandClassArray();
		maquina.method_area->classes[maquina.method_area->classes_count++] = cl->class;

 		loadParentClasses(); // insere em maquina.classes todas as classes pai ainda nao carregadas em maquina.clasess
 		loadInterfaces(cl->class); // insere em maquinas.interfaces todas as interfaces ainda nao carregadas em maquina.interfaces

		free(cl);
	}

	return toReturn;
}

/// verificação do .class
static void verify(int class_index) {
	// TODO
}

/// aloca e inicializa valores default para os fields estaticos
static void prepare() {
	// maquina.classes.array = realloc(maquina.classes.fields, (maquina.classes.size+1)*sizeof(struct _runtime_field));
	
	int count = 0;
	for (int i = 0; i < maquina.method_area->classes_count; i++) {
		for (int j = 0; j < maquina.method_area->classes[i]->fields_count; j++) {
			if (checkIfFieldIsStatic(maquina.method_area->classes[i]->fields_pool->fields[j].access_flags)) {
				maquina.method_area->classes[i]->fields_pool->fields[j].value = 0;
			}
		}
	}
}

/// carrega para method_area as classes de $reference_name
static void resolve(int class_index, char* reference_name) {
	// TODO
}

/// verifica, prepara e opcionalmente resolve
static void link(int class_index) {
	verify(class_index);
	prepare();
}

/// executa o main
static void execute() {
	printf("\nentrou execute");
	while (maquina.current_frame != NULL && (maquina.current_frame->pc) < maquina.current_frame->code_attr->code_length) {
		// printf("\ncomecou laco");
		// // instructions[maquina.current_frame->code_attr->code[maquina.current_frame->pc]].call();
		// printf("\nfinalizou laco");
	}

	// maquina.stack->popFrame();
	printf("\nsaiu execute");
}

/// executa clinit
static void initialize(int class_index) { 
	struct _method_info* clinit = getclinit(maquina.method_area->classes[class_index]);
	if (clinit == NULL) return; // classe abstrata ou interface
	
	construirFrame(maquina.method_area->classes[class_index], clinit);
	execute();
	int flag = -1;
	if ((flag=getClassIndex(maquina.method_area->classes[class_index]->getParentName(maquina.method_area->classes[class_index]))) != -1){
		initialize(flag);
	}
}

static CLASS* getClassByName(char* classname){
	return maquina.method_area->classes[getClassIndex(classname)];
}

static uint64_t getStaticFieldVal(uint32_t class_index, uint32_t field_index){
	return maquina.method_area->classes[class_index]->fields_pool->fields[field_index].value;
}

static uint32_t retrieveFieldIndex(char *className, char *name, uint16_t nameLen, char *desc, uint16_t descLen) {
	
	int32_t i;
	CLASS *main_class;
	uint8_t *getName, *getDesc;
	uint16_t tamName, tamDesc;

	main_class = getClassByName(className);

	if (!main_class) {
		return -2;
	}
	for (i = 0; main_class && i < main_class->fields_count; i++) {
		
		getName = main_class->constant_pool->constants[(main_class->fields_pool->fields[i].name_index-1)].type.Utf8.bytes;
		tamName = main_class->constant_pool->constants[(main_class->fields_pool->fields[i].name_index-1)].type.Utf8.tam;
		
		getDesc = main_class->constant_pool->constants[(main_class->fields_pool->fields[i].descriptor_index-1)].type.Utf8.bytes;
		tamDesc = main_class->constant_pool->constants[(main_class->fields_pool->fields[i].descriptor_index-1)].type.Utf8.tam;
		
		if (nameLen != tamDesc) {
			continue;
		}
		if (descLen != tamDesc) {
			continue;
		}
		if ((strncmp((char *)name, (char *)getName , tamName) == 0) && (strncmp((char *)desc, (char *)getDesc , tamDesc) == 0)) {
			return i;
		}
	}

	return -1;
}


JVM initJVM() {
	JVM toReturn;
	
	toReturn.method_area = initMETHOD_AREA();
	toReturn.heap = initHEAP();
	toReturn.stack = initSTACK();
	toReturn.current_frame = NULL;

	toReturn.loadClass = loadClass;
	toReturn.link = link;
	toReturn.initialize = initialize;
	toReturn.execute = execute;
	toReturn.verify = verify;
	toReturn.prepare = prepare;
	toReturn.resolve = resolve;
	toReturn.retrieveFieldIndex = retrieveFieldIndex;
	toReturn.getClassByName = getClassByName;
	toReturn.getStaticFieldVal = getStaticFieldVal;

	return toReturn;
}


