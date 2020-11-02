2048: 2048.o helper.o
	gcc helper.o 2048.o -o 2048

2048.o: 2048.c 
	gcc -c 2048.c -o 2048.o

helper.o: 2048.h
	gcc -c helper.c -o helper.o
