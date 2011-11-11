canalyze: canalyze.o namelist.o
	gcc -o canalyze canalyze.o namelist.o
namelist.o: namelist.h namelist.c
	gcc -c -o namelist.o namelist.c 
canalyze.o: canalyze.c namelist.o
	gcc -c -o canalyze.o canalyze.c