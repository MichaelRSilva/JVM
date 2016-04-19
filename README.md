# JVM

This design was made in the course of Computer Science, Software Basic matter.
We follow the specification JVM 2, we implemented all methods except the Multiple Array.

This project did not require complex error handling, not garbage collector and was implemented in C, it can be compiled with newer versions of GCC. And the executable is supported by: Windows XP, Windows 7, Windows 10, Ubuntu 14, OSx El Capitan and Yosemite.

Students
- Michael Rodrigues
- Abílio Oliveira
- Marcus Ferreira

Compilation

======

One Makefile for generation of binary is provided. By the terminal, go to the folder for this Readme.txt and run 'make'.
Two binary will be generated

 
	- LeitorExibidor.exe (app that read .class)

	- JVM.exe (the bytecode interpreter)

If you do not want to use the makefile, you will be required to run the following command line:
	
	gcc -std=c99 src/Common/common.c src/Util/util.c src/ClassLoader/Class/class.c src/ClassLoader/Class/AttributeInfo/attributeinfo.c src/ClassLoader/Class/ConstantPool/constantpool.c src/ClassLoader/Class/FieldInfo/fieldinfo.c src/ClassLoader/Class/MethodInfo/methodinfo.c src/ClassLoader/classloader.c src/JVM/maquina/maquina.c src/JVM/main.c

Execution

======
To run the JVM, go to the terminal and run './JVM.exe <ClassName> [options]'

The command line options available for the implementation of the JVM can be accessed by running:

	./JVM.exe <ClassName> [--help]

Structure
=======
	
	./ -> folder that contains the project files (executables will be posted here)
		
		./documentação -> documentation doxygen
			
			./html -> doxygen html files
		
		./testes -> test files to see if JVM is running correctly
		
		./src -> source files
		
			./Common -> Modulo with structures common to all modules and global variables
			
			./Util   -> Module with functions and structures to handle routines I / O

			./JVM    -> Module containing the 'int main (int argc, char ** argv)' Java interpreter (JVM)

				./maquina -> Submodule containing the bodies responsible for managing the implementation of the JVM

			./ClassLoader -> Module that handles loading in memory of a '.class' in a structured way
			
				./Class -> Module that defines the structure of a class point provides the functionality required to load a memory .class
				
					./AttributeInfo -> Module that defines the structure of a AttributeInfo and functions to handle such a structure 
				
					./ConstantPool -> Module that defines the structure of a ConstantPool and functions to handle such a structure
	
					./FieldInfo -> Module that defines the structure of a FieldInfo and functions to handle such a structure

					./MethodInfo -> Module that defines the structure of a MethodInfo and functions to handle such a structure

Note
=======
We try to organize this project non-standard object-oriented. Each module should have a varied number of folders, and at least two files indicating their structures and functions related.
	
	- X.h -> defines structures such module

	- X.c -> functions visible to other modules, however only accessible via a variable of the module type that has been initialized by initx function ()

	- private.c -> only visible to the module functions X

	- subpastas -> submodels

Using pointers to functions in structures enabled us to simulate a false orientation object to facilitate the maintainability of the application and also to better scalability.

--
(c)
