parmes = gcc -g -std=c99 -Wall
final = -lm

all: JVM limpa

debug: Common.o Util.o ClassLoader.o JVM.o
	$(parmes) common.o util.o attributeinfo.o constantpool.o fieldinfo.o methodinfo.o class.o classloader.o jvm.o main.o -o JVM.exe $(final)

JVM: Common.o Util.o ClassLoader.o JVM.o
	$(parmes) common.o util.o attributeinfo.o constantpool.o fieldinfo.o methodinfo.o class.o classloader.o jvm.o main.o -o JVM.exe $(final)

JVM.o: src/JVM/main.c src/JVM/maquina/maquina.c
	$(parmes) -c src/JVM/maquina/maquina.c -o jvm.o $(final)
	$(parmes) -c src/JVM/main.c -o main.o $(final)

ClassLoader.o: src/ClassLoader/classloader.c Class.o AttributeInfo.o ConstantPool.o FieldInfo.o MethodInfo.o 
	$(parmes) -c src/ClassLoader/classloader.c -o classloader.o $(final)

Class.o: src/ClassLoader/Class/class.c
	$(parmes) -c src/ClassLoader/Class/class.c -o class.o $(final)

AttributeInfo.o: src/ClassLoader/Class/AttributeInfo/attributeinfo.c
	$(parmes) -c src/ClassLoader/Class/AttributeInfo/attributeinfo.c -o attributeinfo.o $(final)

ConstantPool.o: src/ClassLoader/Class/ConstantPool/constantpool.c
	$(parmes) -c src/ClassLoader/Class/ConstantPool/constantpool.c -o constantpool.o $(final)

FieldInfo.o: src/ClassLoader/Class/FieldInfo/fieldinfo.c
	$(parmes) -c src/ClassLoader/Class/FieldInfo/fieldinfo.c -o fieldinfo.o $(final)

MethodInfo.o: src/ClassLoader/Class/MethodInfo/methodinfo.c
	$(parmes) -c src/ClassLoader/Class/MethodInfo/methodinfo.c -o methodinfo.o $(final)

Common.o: src/Common/common.c
	$(parmes) -c src/Common/common.c -o common.o $(final)

Util.o: src/Util/util.c
	$(parmes) -c src/Util/util.c -o util.o $(final)

limpa: 
	del *.o
