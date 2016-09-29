#include "sockets.h"

using namespace std;


int sockets::createSocketAndConnect(char* serverHost, char* serverPort){

	int retval, sock;
	struct addrinfo settings;
	struct addrinfo *clientInfo;

	memset(&settings, 0, sizeof settings);
	settings.ai_family = AF_UNSPEC;
	settings.ai_socktype = SOCK_STREAM;

	if (retval = getaddrinfo(serverHost, 
													 serverPort, 
													 &settings, 
													 &clientInfo) != 0)
	{
		return CONNECTION_FAIL_DNS_LOOKUP;	
	}

	//create socket
	sock = socket(clientInfo->ai_family, 
								clientInfo->ai_socktype, 
								clientInfo->ai_protocol);

	//connect to server
	int ret = connect(sock, clientInfo->ai_addr, clientInfo->ai_addrlen);
	
	if (ret != 0){
		return CONNECTION_FAIL_ON_CONNECT;
	}

	freeaddrinfo(clientInfo);

	return sock;

}

int sockets::createSocketAndBind(){

	int retval, sock;
	struct addrinfo settings;
	struct addrinfo *serverInfo;

	memset(&settings, 0, sizeof settings);
	settings.ai_family = AF_UNSPEC;
	settings.ai_socktype = SOCK_STREAM;
	settings.ai_flags = AI_PASSIVE;

	if (retval = getaddrinfo(NULL, "0", &settings, &serverInfo) != 0)
	{
		return SOCKET_BIND_FAIL;	
	}

	//create socket
	sock = socket(serverInfo->ai_family, 
								serverInfo->ai_socktype, 
								serverInfo->ai_protocol);

	//bind to socket
	int ret = bind(sock, serverInfo->ai_addr, serverInfo->ai_addrlen);

	if (ret != 0){
		return SOCKET_BIND_FAIL;
	}

	freeaddrinfo(serverInfo);

	return sock;


}

