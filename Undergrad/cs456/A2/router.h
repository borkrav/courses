#ifndef __ROUTER__
#define __ROUTER__

#define NBR_ROUTER 5				/* for simplicity we consider only 5 routers */

#include "router.h"
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h> 
#include "arpa/inet.h"
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <sstream>
#include <fstream>

//this is used to save LSD info
struct link_info {	
	unsigned int r1;					/* router 1 */
	unsigned int r2;					/* router 2 */
	unsigned int cost;				/* cost of link */
};

struct pkt_HELLO {
	unsigned int router_id;		/* id of the router who sends the HELLO PDU */
	unsigned int link_id;			/* id of the link through which it is sent */
};		

struct pkt_LSPDU {
	unsigned int sender;			/* sender of the LS PDU */
	unsigned int router_id;		/* router id */
	unsigned int link_id; 		/* link id */
	unsigned int cost; 				/* cost of the link */
	unsigned int via; 				/* id of the link through which the LS PDU is sent */
};

struct pkt_INIT {
	unsigned int router_id;		/* id of the router that send the INIT PDU */
};

struct link_cost {
	unsigned int link;				/* link id */
	unsigned int cost;				/* associated cost */
};

struct circuit_DB {
	unsigned int nbr_link;	/* number of links attached to a router */
	struct link_cost linkcost[NBR_ROUTER];
	/* we assume that at most NBR_ROUTER links are attached to each router */
};



class Router {

	private:
		int m_id;
		std::string m_nse_host;
		int m_nse_port;
		int m_port;
		int m_socket;

		//the LSD, using stl map
		std::map<int, link_info> m_LSD;
		std::map<int, link_info>::iterator m_LSD_it;
		std::pair<std::map<int, link_info>::iterator,bool> m_insert_ret;
	
		int m_completeEntries; //the number of complete entries (r1 and r2 known) in LSD
		std::ofstream m_log;
	


	public:
		Router(int id, std::string nse_host, int nse_port, int port);
		~Router();
		void connectToNse();
		void run();

		void getShortestPath();
		void printTopology();

};


#endif
