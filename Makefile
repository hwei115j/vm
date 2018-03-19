vm: main.c virtual.o
	gcc main.c virtual.o -o vm
virtual: virtual.c
	gcc -c virtual.c 
clean:
	rm *.o *.exe
