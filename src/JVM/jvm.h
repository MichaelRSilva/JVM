#ifndef MODULE_JVM
	#define MODULE_JVM
	#include "../ClassLoader/classloader.h"
	#include "../Util/util.h"
	
	typedef struct _jvm {
		int class_array_size;
		CLASS** classes;

		int (*loadParentClasses)(struct _jvm*, CLASS*, UTIL*);
	} JVM;
	
	JVM initJVM();

#endif