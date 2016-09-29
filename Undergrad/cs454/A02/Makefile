CC = g++
CFLAGS = -Wall -c -g -w -std=c++0x
    
all: stringClient stringServer
    
stringClient: stringClient.o stringIO.o
	$(CC) stringClient.o stringIO.o -lpthread -o stringClient
    
stringClient.o: stringClient.cpp
	$(CC) $(CFLAGS) stringClient.cpp

stringServer: stringServer.o stringIO.o
	$(CC) stringServer.o stringIO.o -lpthread -o stringServer
    
stringServer.o: stringServer.cpp
	$(CC) $(CFLAGS) stringServer.cpp

stringIO.o: stringIO.cpp
	$(CC) $(CFLAGS) stringIO.cpp

clean:
	rm -f *.o stringClient stringServer
