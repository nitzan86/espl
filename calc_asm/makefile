calc: calc.o atod.o
	gcc -m32 -o calc calc.o atod.o
calc.o:
	gcc -c -m32 -o calc.o calc.c

atod.o: atod.asm
	nasm -g -f elf -o $@ $<

.PHONY: clean all