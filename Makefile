all: built run

built:
	make -f ./Assembler/Makefile
	make -f ./Processor/Makefile

run:
	./asm $(INPUT) $(OUTPUT)
	./pro $(OUTPUT)