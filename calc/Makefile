.PHONY: all clean

all: calc

calc: calc.o atod.o
	gcc -o $@ $^

calc.o: calc.c

atod.o: atod.c 
