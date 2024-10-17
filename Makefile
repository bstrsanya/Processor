all: pro asm
pro:
	g++ -I./processor -I./Stack/include ./processor/processor.cpp ./Stack/src/stack.cpp ./processor/processor_func.cpp -o main
	./main.exe
asm:
	g++ -I./processor -I./Stack/include ./assembler/assembler.cpp ./assembler/assembler_func.cpp -o asm
	./asm.exe
