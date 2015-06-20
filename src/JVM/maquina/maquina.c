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

static int loadClass(char* name) {
	int toReturn = -1;
	if ((toReturn = getClassIndex(name, maquina.classes)) == -1) {
		CLASS_LOADER* cl = initCLASS_LOADER();

		cl->load(cl, getClassPath(name));
		toReturn = maquina.classes.size;
		expandClassArray();
		maquina.classes.array[maquina.classes.size++].class = cl->class;

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
	for (int i = 0; i < maquina.classes.size; i++) {
		for (int j = 0; j < maquina.classes.array[i].class->fields_count; j++) {
			if (checkIfFieldIsStatic(maquina.classes.array[i].class->fields_pool->fields[j].access_flags)) {
				maquina.classes.array[i].fields = realloc(maquina.classes.array[i].fields,(++count)*sizeof(struct _runtime_field));
				maquina.classes.array[i].fields[j].info = &maquina.classes.array[i].class->fields_pool->fields[j];
				maquina.classes.array[i].fields[j].value = getFieldDefaultValue(maquina.classes.array[i].fields[j].info);
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
	struct _method_info* clinit = getclinit(maquina.classes.array[class_index].class);
	if (clinit == NULL) return; // classe abstrata ou interface
	
	construirFrame(maquina.classes.array[class_index].class, clinit);
	execute();
	int flag = -1;
	if ((flag=getClassIndex(maquina.classes.array[class_index].class->getParentName(maquina.classes.array[class_index].class), maquina.classes)) != -1){
		initialize(flag);
	}
}

static CLASS* getClassByName(char* classname){
	return maquina.classes.array[getClassIndex(classname,maquina.classes)].class;
}

static uint32_t getStaticFieldVal(char* classname){
	return maquina.classes.array[getClassIndex(classname,maquina.classes)].class;
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

	toReturn.classes.size = 0;
	toReturn.interfaces.size = 0;
	
	toReturn.classes.array = (struct _runtime_class*)malloc(sizeof(struct _runtime_class));
	toReturn.interfaces.array = NULL;

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

	return toReturn;
}


