#include "maquina.h"

/// retorna um index para o array de classes da area de metodos
static int getClassIndex(char* class_name, struct _runtime_class_arr classes) {
	if (classes.array == NULL) return -1;

	for(int i=0; i < classes.size; i++){
		char *aux = classes.array[i].class->getName(classes.array[i].class);
		if(!strcmp(class_name,aux)){
			return i;
		}
	}

	return -1;
}

/// checa se o field é estático
int checkIfFieldIsStatic(uint16_t access_flags) {
	if ((access_flags &  0x0008) == 0x0008)
		return 1;
	else
		return 0;
}

/// retorna a concatenacao do nome qualificado da classe com .class
static char* getClassPath(char* class_name) {
	char* path = (char*)malloc(strlen(class_name) + 7);
	if (strstr(class_name,".class") != NULL) return class_name;
	sprintf(path, "%s.class", class_name);
	return path;
}

/// realoca o array de classes por 1
static void expandClassArray() {
	maquina.classes.array = (struct _runtime_class*)realloc(maquina.classes.array,(maquina.classes.size+1)*sizeof(struct _runtime_class));
}

/// realoca o array de interfaces por 1
static void expandInterfaceArray() {
	maquina.interfaces.array = (struct _runtime_class*)realloc(maquina.interfaces.array,(maquina.interfaces.size+1)*sizeof(struct _runtime_class*));
}

/// carrega as classes pai da classe na posicao maquina.classes.size - 1 no array de classes da area de metodo
static int loadParentClasses() {
	CLASS* class = maquina.classes.array[maquina.classes.size-1].class;
	char* parentName = class->getParentName(class);
	int flag = 0;

	// insere parent em maquina.classes caso parent ainda nao esteja carregado 
	if (getClassIndex(parentName, maquina.classes) == -1) {
		CLASS_LOADER *cl = initCLASS_LOADER();

		expandClassArray();
		cl->load(cl, getClassPath(parentName));
		maquina.classes.array[maquina.classes.size++].class= cl->class;
		if (maquina.classes.array[maquina.classes.size-1].class->super_class != 0) {
			flag = loadParentClasses(maquina);
		}

		free(cl);	
	}

	return flag;
}

/// carrega as interfaces da classe na posicao maquina.classes.size - 1 no array de interfaces da area de metodo 
static int loadInterfaces(CLASS* class) {
	int interfacesCount = class->interfaces_count;
	CLASS_LOADER *cl = initCLASS_LOADER();

	for(int i=0; i<interfacesCount; i++){
		char* name = class->getInterfaceName(class, i);
		
		if (getClassIndex(name, maquina.interfaces) == -1) {
			expandInterfaceArray();
			cl->load(cl, getClassPath(name));
			maquina.interfaces.array[maquina.interfaces.size++].class = cl->class;
		}
		
	}

	free(cl);
	return E_SUCCESS;
}

/// procura pela presenca do metodo clinit na classe $class
static struct _method_info* getclinit(CLASS* class) {
	printf("\nentrou getclinit");
	for (int i = 0; i < class->methods_count; i++) {
		char* name = class->constant_pool->getUtf8String(class->constant_pool, class->methods_pool->methods[i].name_index);
		char* desc = class->constant_pool->getUtf8String(class->constant_pool, class->methods_pool->methods[i].descriptor_index);

		if (!strcmp(name, "<clinit>") && !strcmp(desc, "()V")) {
			return &(class->methods_pool->methods[i]);
		}
	}
	printf("\nsaiu getclinit");
	return NULL;
}

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

/// retorna o valor default para fields estaticos
uint32_t getFieldDefaultValue(struct _field_info* field) {
	
	return 0;
}




