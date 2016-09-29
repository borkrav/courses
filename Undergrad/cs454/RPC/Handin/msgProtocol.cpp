#include "msgProtocol.h"
#include "marshaller.h"



using namespace std;

bool VERBOSE = 0;
const int HEADER_LEN = 8;
const int TYPE_LEN = 4;
const int SEGHEAD_LEN = 4;

void msgProtocol::transmitMessage(int socket, message msgStruct){

  vector<string> msg = marshaller::marshall(msgStruct);

	//first element is the message type
	//rest of elements is parts of the message

	//first 4 bytes is overall length
	//length = for all segments (4 bytes + length of segment) + first 4 bytes

	int type = atoi(msg[0].c_str());

	unsigned long long dataLength = TYPE_LEN;

	for (int i = 1; i<msg.size(); i++) dataLength += SEGHEAD_LEN + msg[i].length();



	char* data = new char [HEADER_LEN + dataLength];

	//write the overall data length
	memcpy(data, (void*)&dataLength, HEADER_LEN);

	//write the type of message
	memcpy(data+HEADER_LEN, (void*)&type, TYPE_LEN);

	unsigned long long copyOffset = HEADER_LEN + TYPE_LEN;

	for (int i = 1; i<msg.size(); i++){
			unsigned long len = msg[i].length();
			memcpy(data+copyOffset, (void*)&len, SEGHEAD_LEN);
			memcpy(data+copyOffset+SEGHEAD_LEN, (char*)msg[i].c_str(), len);
			copyOffset += SEGHEAD_LEN + len;
	}



	if (VERBOSE){
		//prints data sent
		cout << "SENT:";
		for (int i = 0; i < dataLength + HEADER_LEN; i++){
			cout << (int)data[i] << " ";
		}
		cout << endl;
	}



	int bytesSent = 0;
	int offset = 0;
	int bytesLeft = dataLength + HEADER_LEN;

	while (offset != dataLength + HEADER_LEN) {
			
		bytesSent = send(socket, 
										 data+offset, 
										 bytesLeft-=bytesSent, 0);

		offset += bytesSent;
			
	}	

	delete[] data;	

}

message msgProtocol::recieveMessage(int socket, int* flag){

	char buffer[3000];

	int bytesGot = recv(socket, &buffer, sizeof(buffer), 0);

	if (bytesGot == 0){
		*flag = -1;
		return message();
	}


	//extract length from string
	unsigned long messageSize = 0;

	memcpy((void*)&messageSize, &buffer, HEADER_LEN);

	char *rawMessage = new char[messageSize];

	memcpy(rawMessage, &(buffer[HEADER_LEN]), bytesGot-HEADER_LEN);


	//read message from socket
	unsigned long bytesLeft = messageSize - bytesGot + 8;
	unsigned long offset = bytesGot-HEADER_LEN;

	while (bytesLeft > 0){
		bytesGot = recv(socket, &buffer, sizeof(buffer), 0);
		memcpy(rawMessage+offset, &buffer, bytesGot);
		bytesLeft -= bytesGot;
		offset += bytesGot;
	}


	//full message has been recieved
	if (VERBOSE){
		cout << "GOT:";
		for (int i = 0; i < messageSize; i++){
			cout << (int)rawMessage[i] << " ";
		}
		cout << endl;
	}


	int messageType = 0;

	memcpy((void*)&messageType, rawMessage, TYPE_LEN);

	vector<string> dataSegments = parseSegments(messageType, rawMessage);	

	delete[] rawMessage;
	
	message m = marshaller::unmarshall(messageType, dataSegments);



	return m;

}



std::vector<std::string> msgProtocol::parseSegments(int messageType, char* message){

	vector<string> result;

	int segments = messageType/10;

	char* head = message + TYPE_LEN;

	for (int i = 0; i < segments; i++){

		unsigned long segmentLength = 0;
		memcpy((void*)&segmentLength, head, SEGHEAD_LEN);

		char* segment = new char [segmentLength];

		memcpy(segment, head+SEGHEAD_LEN, segmentLength);

		string segString = string(reinterpret_cast<char*>(segment), segmentLength);

		result.push_back(segString);

		delete[] segment;

		head += SEGHEAD_LEN + segmentLength;		


	}

	return result;

}
