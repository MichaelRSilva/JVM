#ifndef MODULE_JVM
	#define MODULE_JVM
	#include "../../ClassLoader/classloader.h"
	#include "../../Util/util.h"
	
	typedef struct _maquina_java {
		int classes_size;
		int interfaces_size;

		struct _class_arr {
			CLASS** array;
			int size;
		} classes, interfaces;

		int (*loadClass)(struct _maquina_java*, char*);
	} JVM;
	
	JVM initJVM();

#endif