#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h> 
#include "arpa/inet.h"

#include <iostream>
#include <cstdlib>
#include <cstring>

class stringServer {

	private:

	public:
	stringServer();
	int initSocket();

	std::string processString(std::string input);

	int m_socket;
};
