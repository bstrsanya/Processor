all: asmr pro

asmr:
	make -f ./Assembler/Makefile

pro:
	make -f ./Processor/Makefile
