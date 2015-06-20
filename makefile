all: JVM LeitorExibidor limpa

JVM: Common.o Util.o ClassLoader.o JVM.o
	gcc -std=c99 common.o util.o attributeinfo.o constantpool.o fieldinfo.o methodinfo.o class.o classloader.o jvm.o main.o -o JVM.exe

LeitorExibidor: Common.o Util.o ClassLoader.o LeitorExibidor.o
	gcc -std=c99 common.o util.o attributeinfo.o constantpool.o fieldinfo.o methodinfo.o class.o classloader.o main.o -o LeitorExibidor.exe

JVM.o: src/JVM/main.c src/JVM/maquina/maquina.c
	gcc -std=c99 -c src/JVM/maquina/maquina.c -o jvm.o
	gcc -std=c99 -c src/JVM/main.c -o main.o

LeitorExibidor.o: src/LeitorExibidor/main.c
	gcc -std=c99 -c src/LeitorExibidor/main.c -o main.o

ClassLoader.o: src/ClassLoader/classloader.c Class.o AttributeInfo.o ConstantPool.o FieldInfo.o MethodInfo.o
	gcc -std=c99 -c src/ClassLoader/classloader.c -o classloader.o

Class.o: src/ClassLoader/Class/class.c
	gcc -std=c99 -c src/ClassLoader/Class/class.c -o class.o

AttributeInfo.o: src/ClassLoader/Class/AttributeInfo/attributeinfo.c
	gcc -std=c99 -c src/ClassLoader/Class/AttributeInfo/attributeinfo.c -o attributeinfo.o

ConstantPool.o: src/ClassLoader/Class/ConstantPool/constantpool.c
	gcc -std=c99 -c src/ClassLoader/Class/ConstantPool/constantpool.c -o constantpool.o

FieldInfo.o: src/ClassLoader/Class/FieldInfo/fieldinfo.c
	gcc -std=c99 -c src/ClassLoader/Class/FieldInfo/fieldinfo.c -o fieldinfo.o

MethodInfo.o: src/ClassLoader/Class/MethodInfo/methodinfo.c
	gcc -std=c99 -c src/ClassLoader/Class/MethodInfo/methodinfo.c -o methodinfo.o

Common.o: src/Common/common.c
	gcc -std=c99 -c src/Common/common.c -o common.o

Util.o: src/util/util.c
	gcc -std=c99 -c src/util/util.c -o util.o

limpa: 
	rm *.o