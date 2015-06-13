#ifndef MODULE_JVM
	#define MODULE_JVM
	#include "../../ClassLoader/classloader.h"
	#include "../../Util/util.h"
	
	typedef struct _maquina_java {
		int classes_size;
		int interfaces_size;

		CLASS** classes;
		CLASS** interfaces;

		int (*loadParentClasses)(struct _maquina_java*, CLASS*, UTIL*);
		int (*loadInterfaces)(struct _maquina_java*, CLASS*, UTIL*);
	} JVM;
	
	JVM initJVM();

#endif