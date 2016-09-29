CC = g++
CFLAGS = -Wall -c -g -w
    
OBJECTS	:= router.o
    
my_program: $(OBJECTS)
	$(CC) $(OBJECTS) -o router
    
router.o: router.cpp
	$(CC) $(CFLAGS) router.cpp

clean:
	rm -f *.o router
