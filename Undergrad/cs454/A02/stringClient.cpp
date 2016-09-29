#include "stringClient.h"
#include "stringIO.h"

using namespace std;

pthread_mutex_t lock;
bool done;

stringClient::stringClient(){
	done = false;
}

stringClient::~stringClient(){
	close(m_socket);
}

int stringClient::initSocket(){

	char* serverHost = getenv("SERVER_ADDRESS");
	char* serverPort = getenv("SERVER_PORT");

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
		cerr << gai_strerror(retval) << endl;
		return -1;	
	}

	//create socket
	sock = socket(clientInfo->ai_family, 
								clientInfo->ai_socktype, 
								clientInfo->ai_protocol);

	//connect to server
	connect(sock, clientInfo->ai_addr, clientInfo->ai_addrlen);

	m_socket = sock;

	freeaddrinfo(clientInfo);
}

void* stringClient::bufferStrings(void *ptr){

	stringClient* client = (stringClient *)ptr;

	while(!done)
	{

		string msg;

		getline(cin,msg);

		//push the end of file string and set a flag
		if(cin.eof()){
			msg = "END OF FILE";
			pthread_mutex_lock(&lock);
			done = true;
			pthread_mutex_unlock(&lock);
		}
		
		//save string to buffer	
		pthread_mutex_lock(&lock);
		client->m_stringBuffer.push(msg);
		pthread_mutex_unlock(&lock);

	}

}

void* stringClient::sendStrings(void *ptr){

	stringClient* client = (stringClient *)ptr;

	while(true)
	{

		if (client->m_stringBuffer.size() > 0){

			//fetch string from buffer
			pthread_mutex_lock(&lock);
			string msg = client->m_stringBuffer.front();
			client->m_stringBuffer.pop();
		  pthread_mutex_unlock(&lock);

			//quit if end of file string is on buffer and flag is set
			if (msg == "END OF FILE" && done){
				break;
			}

			
			//transmit string

			stringIO::transmitString(client->m_socket, msg);
			
			//get it back

			int flag = 0;

			string reply = stringIO::recieveString(client->m_socket, &flag);

			cout << "Server: " << reply << endl;
	
			sleep(2);

		}
	}

}


int main()
{

	stringClient c;

	if (c.initSocket() == -1){
		exit(1);
	}

	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, &stringClient::sendStrings, &c);
	pthread_create(&thread2, NULL, &stringClient::bufferStrings, &c);

 	pthread_join(thread1, NULL);
 	pthread_join(thread2, NULL);
	
}
