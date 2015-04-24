all: JVM LeitorExibidor limpa

JVM: Common.o Util.o JVM.o
	gcc -std=c99 common.o util.o jvm.o -o bin/JVM.exe

LeitorExibidor: Common.o Util.o LeitorExibidor.o
	gcc -std=c99 common.o util.o LeitorExibidor.o -o bin/LeitorExibidor.exe

JVM.o: src/JVM/main.c
	gcc -std=c99 -c src/JVM/main.c -o jvm.o

LeitorExibidor.o: src/LeitorExibidor/main.c
	gcc -std=c99 -c src/LeitorExibidor/main.c -o leitorexibidor.o

Common.o: src/Common/common.c
	gcc -std=c99 -c src/Common/common.c

Util.o: src/util/util.c
	gcc -std=c99 -c src/util/util.c

limpa: 
	rm *.o