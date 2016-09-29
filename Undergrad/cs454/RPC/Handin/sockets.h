#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h> 
#include "arpa/inet.h"

#include <iostream>
#include <cstring>

#define RPC_EXECUTE_FAILURE -1;
#define RPC_NO_FUNCTION_DEFINED -2;
#define CONNECTION_FAIL_ON_CONNECT -3;
#define CONNECTION_FAIL_DNS_LOOKUP -4;
#define SOCKET_BIND_FAIL -5;
#define NO_SERVER_CONNECTION -6;
#define NO_BINDER_CONNECTION -7;
#define NO_REGISTERED_FUNCTIONS -8;
#define INVALID_MESSAGE_TYPE -9;
#define INITIALIZATION_FAILED -10;

#define FUNCTION_ALREADY_REGISTERED 1;

class sockets {

	public:
	
	static int createSocketAndConnect(char* serverHost, char* serverPort);
	static int createSocketAndBind();

};
