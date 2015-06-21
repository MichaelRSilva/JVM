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
	printf("\nentrou construirFrame");
	int flag = 0;
	if (metodo->attributes_count > 0) { // indica nao ser nativo
		for (int i = 0; i < metodo->attributes_count; i++) {
			if (strcmp(class->constant_pool->getAttributeType(class->constant_pool, metodo->attributes[i].attributeNameIndex), "Code")) {
				maquina.stack->pushFrame(class, (struct _code_attribute*)&(metodo->attributes[i].info));
				flag = 1;
				break;
			}
		}
	} 
	if (!flag) {

	}
	printf("\nsaiu construirFrame");
}

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

static void setStaticFieldVal(uint32_t class_index, uint32_t field_index, uint64_t value){
	maquina.method_area->classes[class_index]->fields_pool->fields[field_index].value = value;
}

static struct _field_info *getObjectField(struct _object *object, uint32_t name_index) {

	int32_t i = 0;

	while (object->class->fields_pool->fields[i].name_index != name_index) {
		i++;
	}
	return &(object->class->fields_pool->fields[i]);
}

static void setObjectField(struct _object *object, uint32_t name_index, uint64_t value) {

	int32_t i = 0;

	while (object->class->fields_pool->fields[i].name_index != name_index) {
		i++;
	}
	
	object->class->fields_pool->fields[i].value = value;

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

static char * getNameConstants(CLASS *class, uint16_t nameIndex) {
	
	int i;
	char *data = malloc((class->constant_pool->constants[nameIndex - 1]).type.Utf8.tam + 1);

	for (i = 0; i < ( class->constant_pool->constants[nameIndex - 1]).type.Utf8.tam; i++) {
		data[i] = (char) (class->constant_pool->constants[nameIndex - 1]).type.Utf8.bytes[i];
	}

	return data;
}

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
	return parametros;
}

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
	toReturn.setStaticFieldVal = setStaticFieldVal;
	toReturn.getObjectField = getObjectField;
	toReturn.setObjectField = setObjectField;
	toReturn.getNameConstants = getNameConstants;
	toReturn.getMethodByNameDesc = getMethodByNameDesc;
	toReturn.getNumParameters = getNumParameters;
	toReturn.construirFrame = construirFrame;
	
	

	return toReturn;
}


