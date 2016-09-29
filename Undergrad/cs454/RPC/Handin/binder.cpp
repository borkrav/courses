#include "binder.h"
#include "sockets.h"
#include "msgProtocol.h"
#include <iostream>

using namespace std;

binder::binder(){
	running = true;
}


int binder::initSocket(){

	m_socket = sockets::createSocketAndBind();

	if (m_socket < 0){
		cerr << "Fatal error: " << m_socket << endl;
	}

	//extract port from socket, get hostname from OS
 	struct sockaddr_in sa_result;
	int sa_result_size = sizeof(sa_result);
	char hostname[64];

	getsockname(m_socket, (struct sockaddr*) &sa_result, (socklen_t*)&sa_result_size);
	gethostname(hostname, sizeof(hostname));

	cout << "BINDER_ADDRESS " << hostname << endl;
 	cout << "BINDER_PORT " << ntohs(sa_result.sin_port) << endl;

}


void binder::locRequest(message m, int socket){
	

	string signature;

	for (int i = 0; i<m.argTypes.size(); i++){
		int arrayLength =  ((m.argTypes[i] << 16) >> 16);				
		if (arrayLength > 0){
			signature += to_string(m.argTypes[i] | 0x0000FFFF);
		}
		else signature += to_string(m.argTypes[i]);
	}

	stringPair function = make_pair(m.name,signature);

	vector<stringPair> current = registrationTable[function];

	if (current.size() == 0){
		message failure;
		failure.type = LOC_FAILURE;
		failure.reasonCode = RPC_NO_FUNCTION_DEFINED;
		msgProtocol::transmitMessage(socket, failure);
	}

	else{

		stringPair serverInformation;

		deque<stringPair>::iterator it;


		//go through the deque head to tail
		for (it = roundRobin.begin(); it!=roundRobin.end(); ++it){

			//first server in deque that's in the registered server list wins
			if (find(current.begin(), current.end(), *it) != current.end()){
				serverInformation = *it;
				roundRobin.erase(it);
				roundRobin.push_back(serverInformation);
				break;
			}

		}

		//need to get the server information here


		message success;
		success.type = LOC_SUCCESS;
		success.host = serverInformation.first;
		success.port = serverInformation.second;
		msgProtocol::transmitMessage(socket, success);

	}

}

void binder::doRegistration(message m, int socket){

	string signature;

	for (int i = 0; i<m.argTypes.size(); i++){
		int arrayLength =  ((m.argTypes[i] << 16) >> 16);				
		if (arrayLength > 0){
			signature += to_string(m.argTypes[i] | 0x0000FFFF);
		}
		else signature += to_string(m.argTypes[i]);
	}

	//cout << m.name << signature << endl;

	stringPair function = make_pair(m.name,signature);
	stringPair serverInfo = make_pair(m.host, m.port);

	//if this is a new server, push it to the front of the deque
	if (find(roundRobin.begin(), roundRobin.end(), serverInfo) == roundRobin.end()){
		roundRobin.push_front(serverInfo);
	}


	vector<stringPair> current = registrationTable[function];

	if (find(current.begin(), current.end(), serverInfo) != current.end()){
		//do nothing, function already registered by this server
	}
	else {
		current.push_back(serverInfo);
		registrationTable[function] = current;
	}

	
	current = registrationTable[function];
	
	//for(int i = 0; i < current.size(); i++){
		//cout << "<" << current[i].first << "," << current[i].second << ">" << endl;
	//}

	servers.insert(socket);

	message ret;
	ret.type = RETURNCODE;
	ret.reasonCode = 0;
	msgProtocol::transmitMessage(socket, ret);
	
}

void binder::terminate(int socket){
	if (find(servers.begin(), servers.end(), socket) != servers.end()){
		//terminate was sent from a server, this is bad
	}

	else {
		for (set<int>::iterator it=servers.begin(); it!=servers.end(); ++it){
			message term;
			int *flag;
	
			term.type = TERMINATE;
			msgProtocol::transmitMessage(*it, term);
			message reply = msgProtocol::recieveMessage(*it, flag);

		}

		message ret;
		ret.type = RETURNCODE;
		ret.reasonCode = 0;
		msgProtocol::transmitMessage(socket, ret);

		running = false;
	}

}


int main()
{
	binder s;
	int retval = 0;

	if	(s.initSocket() == -1)	exit(0);

	fd_set globalFDs;
	fd_set currentFDs;

	//going to assume that there are at most 100 servers or clients
	listen(s.m_socket,100);
	

	//add listener socket to global fd set
	FD_SET(s.m_socket, &globalFDs);
	
	//keeps track of maximal file descriptor
	int fdmax = s.m_socket;



	while (s.running)
	{
		currentFDs = globalFDs;
		retval = select(fdmax+1, &currentFDs, NULL, NULL, NULL);

		if (retval == -1){
			cerr << "Error in select" << endl;
		}

		for(int i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &currentFDs)){
				
				//if there's a new connection request
				if (i == s.m_socket) {

						struct sockaddr_in remote;
  					int remotelen = sizeof(remote);

						//accept incoming connection
						int clientSock = accept (s.m_socket, 
																		 (struct sockaddr *)&remote, 	
																		 (socklen_t*)&remotelen);
						if (clientSock == -1){
							cerr << "Client connection error" << endl;
						}

						else {

							FD_SET(clientSock, &globalFDs); // add to master set
            	if (clientSock > fdmax) {    // keep track of the max
                fdmax = clientSock;
              }
						
						}

				}

				else {
					//proccess recived string

					int flag = 0;

					message msg = msgProtocol::recieveMessage(i, &flag);
			

					if (flag == -1){ //client left
						FD_CLR(i, &globalFDs);
					}				
				
					else {
						switch(msg.type){
							case REGISTER:
								s.doRegistration(msg, i);
								break;
							case LOC_REQUEST:
								s.locRequest(msg, i);
								break;
							case TERMINATE:
								s.terminate(i);
						}				

					}
				}
			}
		}
	}

	close(s.m_socket);
	
}
