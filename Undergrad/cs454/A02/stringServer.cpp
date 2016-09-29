#include "stringServer.h"
#include "stringIO.h"

using namespace std;


stringServer::stringServer(){
	
}


int stringServer::initSocket(){


	int retval, sock;
	struct addrinfo settings;
	struct addrinfo *serverInfo;

	memset(&settings, 0, sizeof settings);
	settings.ai_family = AF_UNSPEC;
	settings.ai_socktype = SOCK_STREAM;
	settings.ai_flags = AI_PASSIVE;

	if (retval = getaddrinfo(NULL, "0", &settings, &serverInfo) != 0)
	{
		cerr << gai_strerror(retval) << endl;
		return -1;	
	}

	//create socket
	sock = socket(serverInfo->ai_family, 
								serverInfo->ai_socktype, 
								serverInfo->ai_protocol);

	//bind to socket
	bind(sock, serverInfo->ai_addr, serverInfo->ai_addrlen);

	m_socket = sock;

	//extract port from socket, get hostname from OS
 	struct sockaddr_in sa_result;
	int sa_result_size = sizeof(sa_result);
	char hostname[64];

	getsockname(sock, (struct sockaddr*) &sa_result, (socklen_t*)&sa_result_size);
	gethostname(hostname, sizeof(hostname));

	cout << "SERVER_ADDRESS " << hostname << endl;
 	cout << "SERVER_PORT " << ntohs(sa_result.sin_port) << endl;

	freeaddrinfo(serverInfo);

}


std::string stringServer::processString(std::string input)
{

	string output = input;

	bool capNext = true;

	for (int i = 0; i<output.length(); i++)
	{

		if ((int) output[i] == 32)
		{
			capNext = true;
		}


		else if (capNext == true)
		{ 
			output[i] = toupper(output[i]);
			capNext = false;
		}

		else
		{  
			output[i] = tolower(output[i]);
		}

	}

	return output;


}


int main()
{
	stringServer s;

	if	(s.initSocket() == -1)	exit(0);

	int retval = 0;

	fd_set globalFDs;
	fd_set currentFDs;


	//listen on socket
	listen(s.m_socket,5);

	//add listener socket to global fd set
	FD_SET(s.m_socket, &globalFDs);
	
	//keeps track of maximal file descriptor
	int fdmax = s.m_socket;


	while (true)
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

					string message = stringIO::recieveString(i, &flag);
				
					if (flag == -1){ //client left

						FD_CLR(i, &globalFDs);
					}				
				
					else {
						//print the string					
						cout << message << endl;
						//convert string and send it back
						stringIO::transmitString(i, s.processString(message));

					}
				}
			}
		}
	}

	close(s.m_socket);

}
