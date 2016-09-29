#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h> 
#include "arpa/inet.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>


#define REGISTER 40
#define RETURNCODE 12
#define LOC_REQUEST 20
#define LOC_SUCCESS 21
#define LOC_FAILURE 10
#define EXECUTE 30
#define EXECUTE_SUCCESS 31
#define EXECUTE_FAILURE 11
#define TERMINATE 0


struct message {
	int type;
	int reasonCode;
	std::string host;
	std::string port;
	std::string name;
	std::vector<int> argTypes;
	void** args;
};


class msgProtocol {

	public:

	static void transmitMessage(int socket, message msgStruct);
	static message recieveMessage(int socket, int* flag);
	static std::vector<std::string> parseSegments(int messageType, char* message);

};
