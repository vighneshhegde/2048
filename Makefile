2048: driver.o helper.o
	gcc helper.o driver.o -o 2048

2048.o: driver.c 
	gcc -c -g driver.c -o driver.o

helper.o: 2048.h helper.c
	gcc -c -g helper.c -o helper.o
