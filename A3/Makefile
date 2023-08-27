#declare variable
CC=gcc
FC=flex

CFLAG=-c -Wall
CFLAGW=-Wall

#Commmands
output.txt: a.out A3_61.nc
	./a.out < A3_61.nc > output.txt

a.out: lex.yy.c A3_61.o 
	$(CC) $(CFLAGW) A3_61.o -lfl

lex.yy.c: A3_61.l
	$(FC) A3_61.l

A3_14.o: A3_61.c
	$(CC) $(CFLAG) -w A3_61.c 

clean:
	rm output.txt lex.yy.c a.out *.o