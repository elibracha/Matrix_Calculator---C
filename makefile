magic:mymat.o mat.o 
	gcc -g	-ansi -pedantic -Wall mymat.o mat.o -o mymat

mymat.o: mymat.c
	gcc -c	mymat.c

mat.o: mat.c
	gcc -c	mat.c


