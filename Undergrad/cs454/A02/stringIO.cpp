#include "stringIO.h"

using namespace std;

void stringIO::transmitString(int socket, string msg){

	//length of string
	unsigned long len = msg.length()+1;

	//prepare string
	char* stringToSend = new char[len+4];

	memcpy(stringToSend, (void*)&len, 4);
	memcpy(stringToSend+4, (char*)msg.c_str(), len);

	//transmit string
	int bytesSent = 0;
	int offset = 0;
	int bytesLeft = len+4;

	while (offset != len+4) {
			
		bytesSent = send(socket, 
										 stringToSend+offset, 
										 bytesLeft-=bytesSent, 0);

		offset += bytesSent;
			
	}	

	delete[] stringToSend;	

}

string stringIO::recieveString(int socket, int* flag){

	char buffer[3000];

	int bytesGot = recv(socket, &buffer, sizeof(buffer), 0);

	if (bytesGot == 0){
		*flag = -1;
		return "";
	}

	//extract length from string
	unsigned long messageSize = 0;

	memcpy((void*)&messageSize, &buffer, 4);

	char *message = new char[messageSize];

	memcpy(message, &(buffer[4]), bytesGot-4);


	//read message from socket
	unsigned long bytesLeft = messageSize - bytesGot + 4;
	unsigned long offset = bytesGot-4;

	while (bytesLeft > 0){
		bytesGot = recv(socket, &buffer, sizeof(buffer), 0);
		memcpy(message+offset, &buffer, bytesGot);
		bytesLeft -= bytesGot;
		offset += bytesGot;
	}

	string result(message);

	delete[] message;

	return result;

}



