all: main.c virtual.o
	gcc main.c virtual.c -o vm
debug: main.c virtual.c
	gcc -g main.c virtual.c -o vm
clean:
	rm -f *.o *.exe *.stackdump 
