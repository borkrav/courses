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
#include <map>
#include <utility>

using namespace std;

int binderSocket;
int localSocket;
string serverHost;
string serverPort;
bool systemShutdown = false;
map< pair<string,string>, skeleton> skeletonMap;

pthread_mutex_t lock;
pthread_cond_t cond;





extern int rpcInit(){

	char* binderHost = getenv("BINDER_ADDRESS");
	char* binderPort = getenv("BINDER_PORT");
	
	binderSocket = sockets::createSocketAndConnect(binderHost, binderPort);

	localSocket = sockets::createSocketAndBind();

	//couldn't bind local socket
	if (localSocket < 0){
		return localSocket;
	}

	//couldn't connect to binder
	if (binderSocket < 0){
		return binderSocket;
	}

	//extract port from socket, get hostname from OS
 	struct sockaddr_in sa_result;
	int sa_result_size = sizeof(sa_result);
	char hostname[64];

	getsockname(localSocket, (struct sockaddr*) &sa_result, (socklen_t*)&sa_result_size);
	gethostname(hostname, sizeof(hostname));

	serverHost = hostname;
 	serverPort = to_string(ntohs(sa_result.sin_port));

	//successful initialization
	return 0;

}


extern int rpcRegister(char* name, int* argTypes, skeleton f){
	
	//initialization failed, but still tried to register
	if (localSocket < 0 || binderSocket < 0){
		return INITIALIZATION_FAILED;
	}


	vector<int> argTypeVector;
	
	for(int i = 0; argTypes[i] != 0; i++){
		argTypeVector.push_back(argTypes[i]);
	}

	message registration;
	registration.type = REGISTER;
	registration.host = serverHost;
	registration.port = serverPort;
	registration.name = string(name);
	registration.argTypes = argTypeVector;

	msgProtocol::transmitMessage(binderSocket, registration);

	int flag = 0;

	message ret = msgProtocol::recieveMessage(binderSocket, &flag);

	string signature;

	if (ret.type == RETURNCODE && ret.reasonCode == 0){
		for (int i = 0; i<argTypeVector.size(); i++){
			int arrayLength =  ((argTypeVector[i] << 16) >> 16);				
			if (arrayLength > 0){
				signature += to_string(argTypeVector[i] | 0x0000FFFF);
			}
			else signature += to_string(argTypeVector[i]);
		}

		int retCode = 0;

		if (skeletonMap.find(make_pair(string(name),signature)) != skeletonMap.end()){
				retCode = FUNCTION_ALREADY_REGISTERED;
		}


		skeletonMap[make_pair(name,signature)] = f;

		return retCode;

	}

	else if (ret.type == RETURNCODE && ret.reasonCode < 0) {
		return ret.reasonCode;
	}

	else return INVALID_MESSAGE_TYPE;

	

}


void* processRequest(void *ptr){

	int socket = *(int *)ptr;

	pthread_cond_signal(&cond);


	int flag = 0;
	message msg = msgProtocol::recieveMessage(socket, &flag);

	//if server recieves anything but an execute request, it does nothing
	if (msg.type == EXECUTE){

		int argTypes[msg.argTypes.size() + 1];

		for (int i = 0; i<msg.argTypes.size(); i++){
			argTypes[i] = msg.argTypes[i];

		} 
		argTypes[msg.argTypes.size()] = 0;


		string signature;

		for (int i = 0; i<msg.argTypes.size(); i++){
			int arrayLength =  ((msg.argTypes[i] << 16) >> 16);				
			if (arrayLength > 0){
				signature += to_string(msg.argTypes[i] | 0x0000FFFF);
			}
			else signature += to_string(msg.argTypes[i]);
		}

		//cout << msg.name << endl;


		int retVal = skeletonMap[make_pair(msg.name,signature)](argTypes, msg.args);

		if (retVal == 0){
			msg.type = EXECUTE_SUCCESS;
			msgProtocol::transmitMessage(socket, msg);
		}

		else {
			message fail;
			fail.type = EXECUTE_FAILURE;
			fail.reasonCode = retVal;
			msgProtocol::transmitMessage(socket, fail);
		}

		for (int i = 0; i<msg.argTypes.size(); i++){
			free(msg.args[i]);

		}
		free(msg.args);

	}		
	
	else {

		message fail;
		fail.type = EXECUTE_FAILURE;
		fail.reasonCode = INVALID_MESSAGE_TYPE;
		msgProtocol::transmitMessage(socket, fail);
	}

	close(socket);


}

extern int rpcExecute(){

	//initialization failed, but still tried to execute
	if (localSocket < 0 || binderSocket < 0){
			return INITIALIZATION_FAILED;
		}


	if (skeletonMap.size() == 0){
		return NO_REGISTERED_FUNCTIONS;
	}

	
	int retval;

	fd_set globalFDs;

	fd_set currentFDs;

	//going to assume that there are at most 100 servers or clients
	listen(localSocket,100);
	

	//add listener socket to global fd set
	FD_SET(localSocket, &globalFDs);

	//add listener socket to global fd set
	FD_SET(binderSocket, &globalFDs);
	
	//keeps track of maximal file descriptor
	int fdmax = max(localSocket, binderSocket);
	int fdmax_old;



	while (!systemShutdown)
	{

		currentFDs = globalFDs;

		retval = select(fdmax+1, &currentFDs, NULL, NULL, NULL);

		if (retval == -1){
			cerr << "Error in select" << endl;
		}

		for(int i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &currentFDs)){
				
				//if there's a new connection request
				if (i == localSocket) {

						struct sockaddr_in remote;
  					int remotelen = sizeof(remote);

						//accept incoming connection
						int clientSock = accept (localSocket, 
																		 (struct sockaddr *)&remote, 	
																		 (socklen_t*)&remotelen);
						if (clientSock == -1){
							cerr << "Client connection error" << endl;
						}

						else {

							FD_SET(clientSock, &globalFDs); // add to master set
            	if (clientSock > fdmax) {    // keep track of the max
								fdmax_old = fdmax;
                fdmax = clientSock;
              }
						
						}

				}

				else if (i == binderSocket) {

					int flag = 0;
					message msg = msgProtocol::recieveMessage(i, &flag);

					if (flag == -1){ //binder left
						FD_CLR(i, &globalFDs);
					}			

					else if (msg.type == TERMINATE){
						message ret;
						ret.type = RETURNCODE;
						ret.reasonCode = 0;
						msgProtocol::transmitMessage(i, ret);
						close(i);
						systemShutdown = true;
					}


				}

				else {

					pthread_t serverThread;

					
					FD_CLR(i, &globalFDs);
					if(i == fdmax){
						fdmax = fdmax_old;
					}

					pthread_mutex_lock(&lock);
					pthread_create(&serverThread, NULL, &processRequest, &i);
					pthread_cond_wait(&cond, &lock);
					pthread_mutex_unlock(&lock);

			
				}
			}
		}
	}

	close(localSocket);	
	return 0;

}

