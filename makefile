#Mitch Lindsey
#cs4280
#03-31-2019

CC = gcc
CFLAGS = -g -Wall
OBJ = main.o scanner.o tests.o

P1: $(OBJ)
	$(CC)  $(CFLAGS) -o P1 $(OBJ)

%.o: %.c *.h
	$(CC) -c $(CFLAGS) $*.c -o $*.o

clean:
	rm P1 *.o 
