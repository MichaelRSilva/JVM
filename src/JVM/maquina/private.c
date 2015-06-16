#include "maquina.h"

static int getClassIndex(char* class_name, struct _class_arr classes) {
	if (classes.array == NULL) return -1;

	for(int i=0; i < classes.size; i++){
		char *aux = classes.array[i]->getName(classes.array[i]);
		if(!strcmp(class_name,aux)){
			return i;
		}
	}

	return -1;
}

static char* getClassPath(char* class_name) {
	char* path = (char*)malloc(strlen(class_name) + 7);
	if (strstr(class_name,".class") != NULL) return class_name;
	sprintf(path, "%s.class", class_name);
	return path;
}

static void expandClassArray() {
	maquina.classes.array = (CLASS**)realloc(maquina.classes.array,(maquina.classes.size+1)*sizeof(CLASS*));
}

static void expandInterfaceArray() {
	maquina.interfaces.array = (CLASS**)realloc(maquina.interfaces.array,(maquina.interfaces.size+1)*sizeof(CLASS*));
}

static int loadParentClasses() {
	CLASS* class = maquina.classes.array[maquina.classes.size-1];
	char* parentName = class->getParentName(class);
	int flag = 0;

	// insere parent em maquina.classes caso parent ainda nao esteja carregado 
	if (getClassIndex(parentName, maquina.classes) == -1) {
		CLASS_LOADER *cl = initCLASS_LOADER();

		expandClassArray();
		cl->load(cl, getClassPath(parentName));
		maquina.classes.array[maquina.classes.size++] = cl->class;
		if (maquina.classes.array[maquina.classes.size-1]->super_class != 0) {
			flag = loadParentClasses(maquina);
		}

		free(cl);	
	}

	return flag;
}

static int loadInterfaces(CLASS* class) {
	int interfacesCount = class->interfaces_count;
	CLASS_LOADER *cl = initCLASS_LOADER();

	for(int i=0; i<interfacesCount; i++){
		char* name = class->getInterfaceName(class, i);
		
		if (getClassIndex(name, maquina.interfaces) == -1) {
			expandInterfaceArray();
			cl->load(cl, getClassPath(name));
			maquina.interfaces.array[maquina.interfaces.size++] = cl->class;
		}
		
	}

	free(cl);
	return E_SUCCESS;
}
