#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h> 
#include "arpa/inet.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <deque>
#include <set>

typedef std::pair<std::string, std::string> stringPair;

struct message;

class binder {

	private:
	std::map<stringPair, std::vector<stringPair> > registrationTable;
	std::set<int> servers;
	std::deque <stringPair> roundRobin;

	public:
	binder();
	int initSocket();
	void doRegistration(message m, int socket);
	void locRequest(message m, int socket);
	int m_socket;
	void terminate(int socket);	
	bool running;

};


