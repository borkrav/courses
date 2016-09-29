CC = gcc
CFLAGS = -Wall -c -g -w
    
all: sploit1 sploit2
    
sploit1: sploit1.o
	$(CC) sploit1.o -o sploit1

sploit2: sploit2.o
	$(CC) sploit2.o -o sploit2
    
sploit1.o: sploit1.c
	$(CC) $(CFLAGS) sploit1.c

sploit1.o: sploit2.c
	$(CC) $(CFLAGS) sploit2.c

clean:
	rm -f *.o sploit1 sploit2
