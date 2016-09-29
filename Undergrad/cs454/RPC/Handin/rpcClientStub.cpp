#include "rpc.h"
#include "sockets.h"
#include "msgProtocol.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h> 
#include <unistd.h>

#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;

int binderSocket = 0;

void connectToBinder(){
	
	char* binderHost = getenv("BINDER_ADDRESS");
	char* binderPort = getenv("BINDER_PORT");

	binderSocket = sockets::createSocketAndConnect(binderHost, binderPort);

}

extern int rpcCall(char* name, int* argTypes, void** args){

	connectToBinder();
		
	if (binderSocket < 0){
		return NO_BINDER_CONNECTION;
	}



	message locRequest;

	int *flag;

	vector<int> argTypeVector;
	vector<void*> argsVector;
	
	for(int i = 0; argTypes[i] != 0; i++){
		argTypeVector.push_back(argTypes[i]);
		argsVector.push_back(args[i]);
	}

	//pack and send location request
	locRequest.type = LOC_REQUEST;
	locRequest.name = string(name);
	locRequest.argTypes = argTypeVector;
	msgProtocol::transmitMessage(binderSocket, locRequest);
	message reply = msgProtocol::recieveMessage(binderSocket, flag);

	if (reply.type == LOC_SUCCESS){

		char* serverHost = (char*) reply.host.c_str();
		char* serverPort = (char*) reply.port.c_str();


		int serverSocket = sockets::createSocketAndConnect(serverHost, serverPort);

		if (serverSocket < 0){
			return NO_SERVER_CONNECTION;
		}


		message execute;
		execute.type = EXECUTE;
		execute.name = string(name);
		execute.argTypes = argTypeVector;
		execute.args = args;
		msgProtocol::transmitMessage(serverSocket, execute);

		reply = msgProtocol::recieveMessage(serverSocket, flag);

		if (reply.type == EXECUTE_SUCCESS){
			for(int i = 0; argTypes[i] != 0; i++){
				int rawType = ((argTypes[i] << 8) >> 24);
				int arrayLength = ((argTypes[i] << 16) >> 16);	
				switch(rawType){
					case ARG_CHAR:

						if (arrayLength == 0){
							*(char*)args[i] = *(char*)reply.args[i];
						}

						else {
							for(int j = 0; j<arrayLength; j++){
								((char*)args[i])[j] = ((char*)reply.args[i])[j];
							}
						}

						break;

					case ARG_SHORT:
				
						if (arrayLength == 0){
							*(short*)args[i] = *(short*)reply.args[i];
						}

						else {
							for(int j = 0; j<arrayLength; j++){
								((short*)args[i])[j] = ((short*)reply.args[i])[j];
							}
						}

						break;

					case ARG_INT:
								
						if (arrayLength == 0){
							*(int*)args[i] = *(int*)reply.args[i];
						}

						else {
							for(int j = 0; j<arrayLength; j++){
								((int*)args[i])[j] = ((int*)reply.args[i])[j];
							}
						}

						break;

					case ARG_LONG:
								
						if (arrayLength == 0){
							*(long*)args[i] = *(long*)reply.args[i];
						}

						else {
							for(int j = 0; j<arrayLength; j++){
								((long*)args[i])[j] = ((long*)reply.args[i])[j];
							}
						}

						break;

					case ARG_DOUBLE:
								
						if (arrayLength == 0){
							*(double*)args[i] = *(double*)reply.args[i];
						}

						else {
							for(int j = 0; j<arrayLength; j++){
								((double*)args[i])[j] = ((double*)reply.args[i])[j];
							}
						}

						break;

					case ARG_FLOAT:
								
						if (arrayLength == 0){
							*(float*)args[i] = *(float*)reply.args[i];
						}

						else {
							for(int j = 0; j<arrayLength; j++){
								((float*)args[i])[j] = ((float*)reply.args[i])[j];
							}
						}

						break;

				}
				free(reply.args[i]);
		
			}

			free(reply.args);

			close(binderSocket);
			close(serverSocket);
			//successful execution
			return 0;
		}

		else if (reply.type == EXECUTE_FAILURE){	
			return RPC_EXECUTE_FAILURE;
			close(binderSocket);
			close(serverSocket);
		}
	}

	//return on failure
	else if (reply.type == LOC_FAILURE){
		return reply.reasonCode;
	}

	//this should never happen, unless someone is trying to attack the system
	else return INVALID_MESSAGE_TYPE;

}

extern int rpcCacheCall(char* name, int* argTypes, void** args){

}

extern int rpcTerminate(){

	connectToBinder();
		
	if (binderSocket < 0){
		return NO_BINDER_CONNECTION;
	}


	message term;

	int *flag;
	
	term.type = TERMINATE;
	msgProtocol::transmitMessage(binderSocket, term);
	message reply = msgProtocol::recieveMessage(binderSocket, flag);

}
