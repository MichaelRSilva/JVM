#include "maquina.h"

/// retorna um index para o array de classes da area de metodos
static int getClassIndex(char* class_name) {
	// printf("\n\t\t\tentrou getClassIndex: %s", class_name);
	if (maquina.method_area->classes == NULL) {printf("\n\t\t\tsaiu getClassIndex: %s; toReturn: %d", class_name, -3); return -3;}
	if (class_name == NULL || !strcmp(class_name, "")) {printf("\n\t\t\tsaiu getClassIndex: %s; toReturn: %d", class_name, -2);return -2;}

	for(int i=0; i < maquina.method_area->classes_count; i++){
		char *aux = maquina.method_area->classes[i]->getName(maquina.method_area->classes[i]);
		if(!strcmp(class_name,aux)){
			return i;
		}
	}
	// printf("\n\t\t\tsaiu getClassIndex: %s; toReturn: %d", class_name, -1);
	return -1;
}

/// retorna um index para o array de interfaces da area de metodos
static int getInterfceIndex(char* interface_name) {
	if (maquina.method_area->classes == NULL) return -1;
	if (interface_name == NULL || !strcmp(interface_name, "")) return -2;
	
	for(int i=0; i < maquina.method_area->interfaces_count; i++){
		char *aux = maquina.method_area->interfaces[i]->getName(maquina.method_area->interfaces[i]);
		if(!strcmp(interface_name,aux)){
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
	char* path = (char*)malloc(strlen(maquina.basePath)+strlen(class_name) + 7);
	if (strstr(class_name,".class") != NULL) return class_name;
	if (!strcmp(class_name,"java/lang/Object") 
		|| !strcmp(class_name,"java/lang/System") 
		|| !strcmp(class_name,"java/io/PrintStream")
		|| !strcmp(class_name,"java/lang/String")) {

		sprintf(path, "%s.class", class_name);
		return path;	
	} 
	sprintf(path, "%s/%s.class", maquina.basePath, class_name);
	return path;
}

/// realoca o array de classes por 10 (precaução contra memory corruption)
static void expandClassArray() {
	CLASS** tmp;
	tmp = (CLASS**)realloc(maquina.method_area->classes,(maquina.method_area->classes_count+10)*sizeof(CLASS*));

	if (tmp == NULL) {
		printf("\nexpandClassArray(): MEMORY CORRUPTION");
		exit(-1000);
	}

	maquina.method_area->classes = tmp;
}

/// realoca o array de interfaces por 10 (precaução contra memory corruption)
static void expandInterfaceArray() {
	CLASS** tmp;
	tmp = (CLASS**)realloc(maquina.method_area->interfaces,(maquina.method_area->interfaces_count+10)*sizeof(CLASS*));

	if (tmp == NULL) {
		printf("\nexpandInterfaceArray(): MEMORY CORRUPTION");
		exit(-1000);
	}

	maquina.method_area->interfaces = tmp;
}

/// procura pela presenca do metodo clinit na classe $class
static struct _method_info* getclinit(CLASS* class) {
	// printf("\n\tentrou getclinit: %s", class->getName(class));
	for (int i = 0; i < class->methods_count; i++) {
		char* name = class->constant_pool->getUtf8String(class->constant_pool, class->methods_pool->methods[i].name_index);
		char* desc = class->constant_pool->getUtf8String(class->constant_pool, class->methods_pool->methods[i].descriptor_index);

		if (!strcmp(name, "<clinit>") && !strcmp(desc, "()V")) {
			return &(class->methods_pool->methods[i]);
		}
	}
	// printf("\n\tsaiu getclinit%s", class->getName(class));
	return NULL;
}

/*!
	procura e devolve o metodo MAIN
*/
struct _method_info* getMainMethod() {
	CLASS *main_class;
	uint8_t *name, *desc;

	main_class = maquina.method_area->classes[0];

	/* procura por método main ([LJava/lang/String;)V */
	for (int i = 0; i < main_class->methods_count; i++){
		name = main_class->constant_pool->constants[(main_class->methods_pool->methods[i].name_index-1)].type.Utf8.bytes;
		desc = main_class->constant_pool->constants[(main_class->methods_pool->methods[i].descriptor_index-1)].type.Utf8.bytes;

		if ((strcmp("main", (char *)name) == 0) && (strcmp("([Ljava/lang/String;)V", (char *)desc) == 0))
			return &(main_class->methods_pool->methods[i]);
	}

	return NULL;
}




