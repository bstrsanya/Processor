all: pro asmr
pro:
	g++ -I./processor -I./Stack/include ./processor/processor.cpp ./Stack/src/stack.cpp ./processor/processor_func.cpp ./processor/check_func.cpp -o main
	./main.exe
asmr:
	g++ -I./processor -I./Stack/include ./assembler/assembler.cpp ./assembler/assembler_func.cpp ./processor/check_func.cpp ./Stack/src/stack.cpp -o asm
	./asm.exe
