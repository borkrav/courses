CC = g++
CFLAGS = -Wall -c -g -w -std=c++0x
    
all: binder rpc
    
binder: binder.o sockets.o msgProtocol.o marshaller.o
	$(CC) binder.o -lpthread sockets.o msgProtocol.o marshaller.o -o binder
    
binder.o: binder.cpp
	$(CC) $(CFLAGS) binder.cpp

rpc: rpcClientStub.o rpcServerStub.o sockets.o msgProtocol.o marshaller.o
	ar rcs librpc.a rpcClientStub.o rpcServerStub.o sockets.o msgProtocol.o marshaller.o

rpcServerStub.o: rpcServerStub.cpp
	$(CC) $(CFLAGS) rpcServerStub.cpp

rpcClientStub.o: rpcClientStub.cpp
	$(CC) $(CFLAGS) rpcClientStub.cpp
 
sockets.o: sockets.cpp
	$(CC) $(CFLAGS) sockets.cpp

msgProtocol.o :msgProtocol.cpp 
	$(CC) $(CFLAGS) msgProtocol.cpp 

marshaller.o: marshaller.cpp
	$(CC) $(CFLAGS) marshaller.cpp 

clean:
	rm -f *.o binder librpc.a
