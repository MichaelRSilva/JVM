all: JVM LeitorExibidor limpa

JVM: Common.o Util.o ClassLoader.o JVM.o
	gcc -std=c99 common.o util.o attributeinfo.o constantpool.o fieldinfo.o methodinfo.o class.o classloader.o jvm.o -o JVM.exe

LeitorExibidor: Common.o Util.o ClassLoader.o LeitorExibidor.o
	gcc -std=c99 common.o util.o attributeinfo.o constantpool.o fieldinfo.o methodinfo.o class.o classloader.o LeitorExibidor.o -o LeitorExibidor.exe

JVM.o: src/JVM/main.c
	gcc -std=c99 -c src/JVM/main.c -o jvm.o

LeitorExibidor.o: src/LeitorExibidor/main.c
	gcc -std=c99 -c src/LeitorExibidor/main.c -o leitorexibidor.o

ClassLoader.o: src/ClassLoader/public.c Class.o AttributeInfo.o ConstantPool.o FieldInfo.o MethodInfo.o
	gcc -std=c99 -c src/ClassLoader/public.c -o classloader.o

Class.o: src/ClassLoader/Class/public.c
	gcc -std=c99 -c src/ClassLoader/Class/public.c -o class.o

AttributeInfo.o: src/ClassLoader/Class/AttributeInfo/public.c
	gcc -std=c99 -c src/ClassLoader/Class/AttributeInfo/public.c -o attributeinfo.o

ConstantPool.o: src/ClassLoader/Class/ConstantPool/public.c
	gcc -std=c99 -c src/ClassLoader/Class/ConstantPool/public.c -o constantpool.o

FieldInfo.o: src/ClassLoader/Class/FieldInfo/public.c
	gcc -std=c99 -c src/ClassLoader/Class/FieldInfo/public.c -o fieldinfo.o

MethodInfo.o: src/ClassLoader/Class/MethodInfo/public.c
	gcc -std=c99 -c src/ClassLoader/Class/MethodInfo/public.c -o methodinfo.o

Common.o: src/Common/public.c
	gcc -std=c99 -c src/Common/public.c -o common.o

Util.o: src/util/public.c
	gcc -std=c99 -c src/util/public.c -o util.o

limpa: 
	rm *.o