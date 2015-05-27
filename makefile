all: JVM LeitorExibidor limpa

JVM: Common.o Util.o ClassLoader.o JVM.o
	gcc -std=c99 common.o util.o attributeinfo.o constantpool.o fieldinfo.o methodinfo.o class.o classloader.o jvm.o -o bin/JVM.exe

LeitorExibidor: Common.o Util.o ClassLoader.o LeitorExibidor.o
	gcc -std=c99 common.o util.o attributeinfo.o constantpool.o fieldinfo.o methodinfo.o class.o classloader.o LeitorExibidor.o -o bin/LeitorExibidor.exe

JVM.o: src/JVM/main.c
	gcc -std=c99 -c src/JVM/main.c -o jvm.o

LeitorExibidor.o: src/LeitorExibidor/main.c
	gcc -std=c99 -c src/LeitorExibidor/main.c -o leitorexibidor.o

ClassLoader.o: src/ClassLoader/classloader.c Class.o AttributeInfo.o ConstantPool.o FieldInfo.o MethodInfo.o
	gcc -std=c99 -c src/ClassLoader/classloader.c

Class.o: src/ClassLoader/Class/class.c
	gcc -std=c99 -c src/ClassLoader/Class/class.c

AttributeInfo.o: src/ClassLoader/Class/AttributeInfo/attributeinfo.c
	gcc -std=c99 -c src/ClassLoader/Class/AttributeInfo/attributeinfo.c

ConstantPool.o: src/ClassLoader/Class/ConstantPool/constantpool.c
	gcc -std=c99 -c src/ClassLoader/Class/ConstantPool/constantpool.c

FieldInfo.o: src/ClassLoader/Class/FieldInfo/fieldinfo.c
	gcc -std=c99 -c src/ClassLoader/Class/FieldInfo/fieldinfo.c

MethodInfo.o: src/ClassLoader/Class/MethodInfo/methodinfo.c
	gcc -std=c99 -c src/ClassLoader/Class/MethodInfo/methodinfo.c

Common.o: src/Common/common.c
	gcc -std=c99 -c src/Common/common.c

Util.o: src/util/util.c
	gcc -std=c99 -c src/util/util.c

limpa: 
	rm *.o