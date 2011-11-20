bfix: bfix.o bfix.o
	gcc -o bfix bfix.o diff.o
diff.o: diff.h diff.c
	gcc -c -o diff.o diff.c 
bfix.o: bfix.c diff.o
	gcc -c -o bfix.o bfix.c