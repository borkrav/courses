#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h> 

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <pthread.h>
#include <bitset>

class stringClient {

	private:


	public:
	stringClient();
	~stringClient();
	int initSocket();

	std::queue<std::string> m_stringBuffer;
	int m_socket;

	static void *sendStrings(void *ptr);
	static void *bufferStrings(void *ptr);

};
