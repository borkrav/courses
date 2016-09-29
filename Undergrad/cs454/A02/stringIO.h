#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h> 
#include "arpa/inet.h"

#include <iostream>
#include <cstdlib>
#include <cstring>

class stringIO {

	public:

	static void transmitString(int socket, std::string msg);
	static std::string recieveString(int socket, int* flag);

};
