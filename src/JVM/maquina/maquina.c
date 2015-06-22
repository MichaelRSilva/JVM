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

/// constroi e coloca no topo do stack de frames o frame relacionado com $metodo e $class
static void construirFrame(CLASS* class, struct _method_info* metodo) {
	// printf("\n\t\tentrou construirFrame: %s", class->getName(class));
	int flag = 0;
	if (metodo->attributes_count > 0) { // indica nao ser nativo
		for (int i = 0; i < metodo->attributes_count; i++) {
			if (!strcmp(class->constant_pool->getAttributeType(class->constant_pool, metodo->attributes[i].attributeNameIndex), "Code")) {
				maquina.stack->pushFrame(class, (struct _code_attribute*)&(metodo->attributes[i].info));
				flag = 1;
				break;
			}
		}
	} 
	if (!flag) {

	}
	// printf("\n\t\tsaiu construirFrame: %s", class->getName(class));
}

/// executa o método do current frame
static void execute() {
	// printf("\n\t\tentrou execute: %p; stack_count: %d", maquina.current_frame, maquina.stack->count);
	while (maquina.stack->have_returned == 0 
		&& maquina.current_frame != NULL && (maquina.current_frame->pc) < maquina.current_frame->code_attr->code_length) {
		
		uint32_t ins = maquina.current_frame->code_attr->code[maquina.current_frame->pc];
		printf("\n\tpc: %x; code: %x <%s>", maquina.current_frame->pc, ins , instructions[ins].nome);
		instructions[maquina.current_frame->code_attr->code[maquina.current_frame->pc]].call();
	}
	maquina.stack->have_returned = 0;

	// printf("\n\t\tsaiu execute: %p; stack_count: %d", maquina.current_frame, maquina.stack->count);
}

/// executa clinit
static void initialize(int class_index) { 
	// printf("\n\tentrou initialize; class_index: %d", class_index);
	CLASS* class = maquina.method_area->classes[class_index];
	struct _method_info* clinit = getclinit(class);
	int flag = -1;

	if (clinit == NULL) return; // classe abstrata ou interface
	
	construirFrame(class, clinit);
	execute();

	// printf("\n\tsaiu initialize; class_index: %d", class_index);
}


/// aloca e inicializa valores default para os fields estaticos da classe indicada por $index
static void prepare(uint32_t index) {
	// maquina.classes.array = realloc(maquina.classes.fields, (maquina.classes.size+1)*sizeof(struct _runtime_field));
	
	int count = 0;
	for (int j = 0; j < maquina.method_area->classes[index]->fields_count; j++) {
		if (checkIfFieldIsStatic(maquina.method_area->classes[index]->fields_pool->fields[j].access_flags)) {
			maquina.method_area->classes[index]->fields_pool->fields[j].value = 0;
		}
	}
}

/// verificação do .class
static void verify(int class_index) {
	// TODO
}

/// verifica, prepara e opcionalmente resolve
static void link(int class_index) {
	verify(class_index);
	prepare(class_index);
}

/// carrega as classes pai da classe na posicao maquina.classes.size - 1 no array de classes da area de metodo
static int loadParentClasses() {
	// printf("\n\tentrou loadParentClasses");
	CLASS* class = maquina.method_area->classes[maquina.method_area->classes_count-1];
	char* parentName = class->getParentName(class);
	int flag = 0;

	// insere parent em maquina.method_area->classes caso parent ainda nao esteja carregado 
	if (getClassIndex(parentName) == -1) {
		CLASS_LOADER *cl = initCLASS_LOADER();

		expandClassArray();
		cl->load(cl, getClassPath(parentName));
		maquina.method_area->classes[maquina.method_area->classes_count++]= cl->class;
		link(maquina.method_area->classes_count-1);
		initialize(maquina.method_area->classes_count-1);

		if (maquina.method_area->classes[maquina.method_area->classes_count-1]->super_class != 0) {
			flag = loadParentClasses(maquina);
		}

		free(cl);	
	}
	// printf("\n\tentrou loadParentClasses");
	return flag;
}

/// carrega as interfaces da classe na posicao maquina.classes.size - 1 no array de interfaces da area de metodo 
static int loadInterfaces(CLASS* class) {
	int interfacesCount = class->interfaces_count;
	CLASS_LOADER *cl = initCLASS_LOADER();

	for(int i=0; i<interfacesCount; i++){
		char* name = class->getInterfaceName(class, i);
		
		if (getInterfceIndex(name) == -1) {
			expandInterfaceArray();
			cl->load(cl, getClassPath(name));
			maquina.method_area->interfaces[maquina.method_area->interfaces_count++] = cl->class;
		}
		
	}

	free(cl);
	return E_SUCCESS;
}

/*!
	carrega uma classe que ainda nao foi carregada na memoria 
*/
static int loadClass(char* name) {
	// printf("\nentrou loadClass: %s", name);
	int toReturn = -1;
	if ((toReturn = getClassIndex(name)) <= -1) {
		CLASS_LOADER* cl = initCLASS_LOADER();

		cl->load(cl, getClassPath(name));
		toReturn = maquina.method_area->classes_count;
		expandClassArray();
		maquina.method_area->classes[maquina.method_area->classes_count++] = cl->class;
		link(maquina.method_area->classes_count-1);
		initialize(maquina.method_area->classes_count-1);

 		loadParentClasses(); // insere em maquina.classes todas as classes pai ainda nao carregadas em maquina.clasess
 		loadInterfaces(cl->class); // insere em maquinas.interfaces todas as interfaces ainda nao carregadas em maquina.interfaces

		free(cl);
	}

	// printf("\nsaiu loadClass: %s; toReturn: %d", name, toReturn);
	return toReturn;
}

/// executa o main
static void run() {
	// printf("\nENTROU RUN");
	struct _method_info* main = getMainMethod();
	if (main == NULL) {printf("Nao foi encontrado nenhuma main!"); exit(-1230);}

	construirFrame(maquina.method_area->classes[0], main);
	execute();
	// printf("\nSAIU RUN");
}

/*!
	procura uma class pelo nome no array de classes
*/

static CLASS* getClassByName(char* classname){
	int flag = getClassIndex(classname);
	if (flag < 0) return NULL;
	return maquina.method_area->classes[getClassIndex(classname)];
}

/*!
	devolve um valor de um field estatico
*/
static uint64_t getStaticFieldVal(uint32_t class_index, uint32_t field_index){
	return maquina.method_area->classes[class_index]->fields_pool->fields[field_index].value;
}

/*!
	atribui um valor a um field estatico
*/
static void setStaticFieldVal(uint32_t class_index, uint32_t field_index, uint64_t value){
	maquina.method_area->classes[class_index]->fields_pool->fields[field_index].value = value;
}

/*!
	dado um objeto devolve a referencia para um field desse objeto
*/
static struct _field_info *getObjectField(struct _object *object, uint32_t name_index) {

	int32_t i = 0;

	while (object->class->fields_pool->fields[i].name_index != name_index) {
		i++;
	}
	return &(object->class->fields_pool->fields[i]);
}

/*!
	seta um valor a um field que estah instanciado
*/
static void setObjectField(struct _object *object, uint32_t name_index, uint64_t value) {

	int32_t i = 0;

	while (object->class->fields_pool->fields[i].name_index != name_index) {
		i++;
	}
	
	object->class->fields_pool->fields[i].value = value;

}

/*!
	devolve o index de um field de uma classe
*/
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
		if ((strcmp((char *)name, (char *)getName) == 0) && (strcmp((char *)desc, (char *)getDesc) == 0)) {
			return i;
		}
	}
	// exit(-24242);

	return -1;
}

/*!
	devolve um index de um nome de uma constant
*/
static char * getNameConstants(CLASS *class, uint16_t nameIndex) {
	return  class->constant_pool->getUtf8String(class->constant_pool, nameIndex);
}

/*!
	devolve a quantidade de parametros de um metodo
*/
int32_t getNumParameters(CLASS *class, struct _method_info *method) {
	int32_t i;
	int32_t parametros = 0;
	uint16_t length;
	uint8_t *bytes;

	bytes = class->constant_pool->constants[(method->descriptor_index-1)].type.Utf8.bytes;
	length = class->constant_pool->constants[(method->descriptor_index-1)].type.Utf8.tam;
	for(i = 0; i < length && bytes[i] != ')'; i++) {
		if(bytes[i] == 'L') {
			while(bytes[i] != ';') {
				i++;
			}
			parametros++;
		} else if((bytes[i] == 'B')||(bytes[i] == 'C')||(bytes[i] == 'F')|| (bytes[i] == 'I')||(bytes[i] == 'S')||(bytes[i] == 'Z') ) {
			parametros++;
		} else if((bytes[i] == 'D')||(bytes[i] == 'J')) {
			parametros+=2;
		}
	}
	// printf("\n\t\t\tparametros: %d", parametros);
	return parametros;
}

/*!
	procura e devolve um metodo, pesquisando por nome e descricao
*/
struct _method_info *getMethodByNameDesc(CLASS *main_class, CLASS *name_type_class, uint16_t name_type_index) {
	int i;
	uint8_t *m_name, *m_desc;
	uint16_t m_name_len, m_desc_len;
	char *name, *desc;
	uint16_t name_len, desc_len;

	name = getNameConstants(name_type_class, name_type_class->constant_pool->constants[name_type_index-1].type.NameType.nameIndex);
	name_len = strlen(name);
	desc = getNameConstants(name_type_class, name_type_class->constant_pool->constants[name_type_index-1].type.NameType.descriptorIndex);
	desc_len = strlen(desc);

	for(i = 0; i < main_class->methods_count; i++) {

		m_name = main_class->constant_pool->constants[(main_class->methods_pool->methods[i].name_index-1)].type.Utf8.bytes;
		m_name_len = main_class->constant_pool->constants[(main_class->methods_pool->methods[i].name_index-1)].type.Utf8.tam;
		m_desc = main_class->constant_pool->constants[(main_class->methods_pool->methods[i].descriptor_index-1)].type.Utf8.bytes;
		m_desc_len = main_class->constant_pool->constants[(main_class->methods_pool->methods[i].descriptor_index-1)].type.Utf8.tam;
		
		if(name_len != m_name_len) {
			continue;
		}
		if(desc_len != m_desc_len) {
			continue;
		}
		if((strncmp((char *)name,(char *)m_name , m_name_len) == 0) &&(strncmp((char *)desc,(char *)m_desc , m_desc_len) == 0)) {
			return &(main_class->methods_pool->methods[i]);
		}

	}
	return NULL;
}

static uint64_t getNativeValueForStaticMethod(struct _method_info* method) {
	return 0;
}

/*!
	inicia a JVM 
*/
JVM initJVM() {
	JVM toReturn;
	
	// init campos
	toReturn.method_area = initMETHOD_AREA();
	toReturn.heap = initHEAP();
	toReturn.stack = initSTACK();
	toReturn.current_frame = NULL;

	// init funcoes`
	toReturn.loadClass = loadClass;
	toReturn.link = link;
	toReturn.initialize = initialize;
	toReturn.execute = execute;
	toReturn.verify = verify;
	toReturn.prepare = prepare;
	toReturn.retrieveFieldIndex = retrieveFieldIndex;
	toReturn.getClassByName = getClassByName;
	toReturn.getStaticFieldVal = getStaticFieldVal;
	toReturn.setStaticFieldVal = setStaticFieldVal;
	toReturn.getObjectField = getObjectField;
	toReturn.setObjectField = setObjectField;
	toReturn.getNameConstants = getNameConstants;
	toReturn.getMethodByNameDesc = getMethodByNameDesc;
	toReturn.getNumParameters = getNumParameters;
	toReturn.construirFrame = construirFrame;
	toReturn.run = run;
	toReturn.loadParentClasses = loadParentClasses;
	toReturn.loadInterfaces = loadInterfaces;
	toReturn.getNativeValueForStaticMethod = getNativeValueForStaticMethod;

	return toReturn;
}


