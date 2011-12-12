%.o: %.asm
	nasm -g -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g -nostdlib -fno-stack-protector -c -o $@ $<

.PHONY: clean all

all: bcmp

bcmp: puts.o start.o main.o write.o length.o exit.o open.o close.o read.o
	ld -melf_i386 -g -o $@ $^

#ahalan.o: ahalan.asm 
puts.o: puts.c
start.o: start.asm
main.o: main.c
write.o: write.asm
length.o: length.c
exit.o: exit.asm
open.o: open.asm
close.o: close.asm
read.o: read.asm



clean:
	rm *.o bcmp
