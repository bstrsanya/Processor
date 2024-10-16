all: pro asm
pro:
	g++ -I./processor -I./Stack/include ./processor/processor.cpp ./Stack/src/stack.cpp -o main
	./main.exe
asm:
	g++ -I./processor -I./Stack/include ./assembler/assembler.cpp -o asm
	./asm.exe
