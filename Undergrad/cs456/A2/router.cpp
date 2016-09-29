#include "router.h"

using namespace std;


Router::Router(int id, string nse_host, int nse_port, int port) : m_id(id), m_nse_host(nse_host), m_nse_port(nse_port), m_port(port){

	m_LSD = map<int, link_info>();
	m_completeEntries = 0;


	//opens an appropriately named log file
	string num = static_cast<ostringstream*>
							( &(ostringstream() << m_id) )->str();

	stringstream ss;
	ss << "router" << num << ".log";
	m_log.open(ss.str().c_str());
}

Router::~Router(){
	m_log.close();
}


void Router::connectToNse(){

		int sock, retval; //socket fd and return value
    struct sockaddr_in sa_rem;	//remote address
    struct sockaddr_in sa_loc;	//local address
		struct hostent *nse_address;
		string nse_ip;

		try {

			//resolve hostname
			nse_address = gethostbyname(m_nse_host.c_str());
			if (nse_address == NULL) throw 1;
			//extract IP field (for error purposes)
			nse_ip = inet_ntoa(*((struct in_addr *)nse_address->h_addr));

		  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		  // zero out struct
		  memset(&sa_loc, 0, sizeof(struct sockaddr_in));
		  sa_loc.sin_family = AF_INET;
		  sa_loc.sin_port = htons(m_port);
		  sa_loc.sin_addr.s_addr = htonl(INADDR_ANY);

			//bind to local port
		  retval = bind(sock, (struct sockaddr *)&sa_loc, sizeof(struct sockaddr));
		  if (retval == -1) throw 2;

		  // zero out struct
		  memset(&sa_rem, 0, sizeof(struct sockaddr_in));
		  sa_rem.sin_family = AF_INET;
		  sa_rem.sin_port = htons(m_nse_port);
		  sa_rem.sin_addr.s_addr = inet_addr(nse_ip.c_str());

			//connect to nse host and port
		  retval = connect(sock, (struct sockaddr *)&sa_rem, sizeof(struct sockaddr));
		  if (retval == -1) throw 3;

		} catch (int e) {
				switch(e){
					case 1:
						cerr << "Could not reslove " << m_nse_host << endl;
						break;
					case 2:
						cerr << "Could not bind to port " << m_port << endl;
						break;
					case 3:
						cerr << "Could not connect to " << nse_ip << " " << m_nse_port << endl;
						break;
				}
		}

		m_socket = sock;

}


void Router::run(){

	pkt_INIT init = pkt_INIT{m_id};
	circuit_DB cdb;
	char buffer[1024];
	vector<unsigned int> hellos = vector<unsigned int>();
	vector<pkt_LSPDU> sentSoFar = vector<pkt_LSPDU>();
	struct timeval tv;

	tv.tv_sec = 5;  /* 5 sec Timeout */
	tv.tv_usec = 0;  

	//sets timeout on socket to be 5 seconds
	setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
	
	m_log << "R" << m_id << " sends INIT" << endl;

	send(m_socket, &init, sizeof(init), 0);
	recv(m_socket, &cdb, sizeof(cdb), 0);

	m_log << "R" << m_id << " gets CDB" << endl;

	int numOfNeighbours =  cdb.nbr_link;

	//iterate over the CDB
	for (int i = 0; i<numOfNeighbours; i++){

		int link = cdb.linkcost[i].link;

		//insert CDB information into LSD
		m_LSD.insert(pair<unsigned int, link_info>
								(cdb.linkcost[i].link, link_info{m_id, 0 ,cdb.linkcost[i].cost}));


		//Send Hello to all neighbours 
		pkt_HELLO hello = pkt_HELLO{m_id, link};
	
		m_log << "R" << m_id
					<< " sent HELLO: router_id " << m_id 
					<< " link " << link 
					<< endl;

		send(m_socket, &hello, sizeof(hello), 0);

	}


	while (true){

	 
		int size = recv(m_socket, &buffer, sizeof(buffer), 0);
		if (size == -1) break;	//done


		//if I got a hello 
		if (size == sizeof(pkt_HELLO)){

			pkt_HELLO* reply = (pkt_HELLO*)buffer;

			m_log << "R" << m_id 
						<< " got HELLO: router_id " << reply->router_id 
						<< " link " << reply->link_id 
						<< endl;
			
			//save that I got a hello from this link
			hellos.push_back(reply->link_id);

			
			int linkCost = m_LSD[reply->link_id].cost;

			//update the entry I already have with router information I just got
			m_insert_ret = m_LSD.insert(pair<unsigned int, link_info>
											(reply->link_id, link_info{m_id, reply->router_id,linkCost}));

			if (m_insert_ret.second == false) {
				m_LSD.erase(m_insert_ret.first);
				m_insert_ret = m_LSD.insert(pair<unsigned int, link_info>
											(reply->link_id, link_info{m_id, reply->router_id,linkCost}));
			}
	
			//transmit LSPDU's for entire LSD to router that Hello'd me
			for(m_LSD_it = m_LSD.begin(); m_LSD_it != m_LSD.end(); m_LSD_it++) {

				pkt_LSPDU lspdu = pkt_LSPDU{m_id, 
															m_LSD_it->second.r1, 
															m_LSD_it->first, 
															m_LSD_it->second.cost,
										 					reply->link_id};


				m_log << "R" << m_id << " sent LS PDU: sender " << lspdu.sender 
						 << " router_id " << lspdu.link_id 
 						 << " link_id " << lspdu.link_id 
						 << " cost " << lspdu.cost 
						 << " via " << lspdu.via << endl;

				send(m_socket, &lspdu, sizeof(lspdu), 0);

			}

		}

		//if I got an LSPDU
		if (size == sizeof(pkt_LSPDU)){

			pkt_LSPDU* reply = (pkt_LSPDU*)buffer;

			m_log << "R" << m_id << " got LS PDU: sender " << reply->sender 
						 << " router_id " << reply->link_id 
 						 << " link_id " << reply->link_id 
						 << " cost " << reply->cost 
						 << " via " << reply->via << endl;

			pkt_LSPDU lspdu = *reply;

			//if the LSPDU sent from neighbour who doesn't know my router ID, insert that 			// information
			if (lspdu.router_id == 0 && lspdu.link_id == lspdu.via) {
				lspdu.router_id = m_id;
			}
			
			//update my LSD with this LSPDU
			m_insert_ret = m_LSD.insert(pair<unsigned int, link_info>
												(lspdu.link_id, link_info{lspdu.router_id, 0 ,lspdu.cost}));

			//this ensures the second router field is correctly filled
			if (m_insert_ret.second == false && m_LSD[reply->link_id].r1 !=
				  lspdu.router_id && m_LSD[reply->link_id].r2 != lspdu.router_id) {

				int rID = m_LSD[reply->link_id].r1;
				m_LSD.erase(m_insert_ret.first);
							m_insert_ret = m_LSD.insert(pair<unsigned int, link_info>
								(lspdu.link_id, link_info{rID, lspdu.router_id ,lspdu.cost}));

			}
	
			lspdu.sender = m_id;

			//for all hello's
			for (int i = 0; i<hellos.size(); i++){
				//except the router who sent me this LSPDU
				if (lspdu.via != hellos[i]){

					lspdu.via = hellos[i];

					bool sentAlready = false;

					//check if I've sent this exact LSPDU already (Prevents a loop)
					for (int i = 0; i < sentSoFar.size(); i++){
						if (lspdu.sender == sentSoFar[i].sender &&
								lspdu.router_id == sentSoFar[i].router_id &&
								lspdu.link_id == sentSoFar[i].link_id &&
								lspdu.cost == sentSoFar[i].cost &&
								lspdu.via == sentSoFar[i].via ) sentAlready = true;
					}

					//if I haven't, send
					if(!sentAlready) {
						sentSoFar.push_back(lspdu);

						m_log << "R" << m_id << " sent LS PDU: sender " << lspdu.sender 
						 << " router_id " << lspdu.link_id 
 						 << " link_id " << lspdu.link_id 
						 << " cost " << lspdu.cost 
						 << " via " << lspdu.via << endl;


						send(m_socket, &lspdu, sizeof(lspdu), 0);
					}

				}
			}

		}

		//count the total entries in the LSD
		int totalEntries = 0;
		int entries = 0;
		for(m_LSD_it = m_LSD.begin(); m_LSD_it != m_LSD.end(); m_LSD_it++) {
			if (m_LSD_it->second.r2 != 0 && m_LSD_it->second.r1 != 0) entries++;
			if (m_LSD_it->second.r2 != 0) totalEntries++;
			if (m_LSD_it->second.r1 != 0) totalEntries++;

		}

		//if the topology changed, print it
		if (totalEntries > m_completeEntries*2) printTopology();

		//if the topology has one extra complete row (both routers in edge known)
		//run shortest path calculation
		if (entries > m_completeEntries){
			m_completeEntries = entries;
			getShortestPath();
		}

	}

}



void Router::getShortestPath(){

	//Implementation of Dijsktra’s Algorithm, straight from the slides

	set<int> N = set<int>(); 
	set<int> Vs = set<int>(); 
	std::map<int, int> Dv;
	std::map<int, int> Pv;

	N.insert(m_id); //N' = {u}

	//get all the V's from the LSD
	for(m_LSD_it = m_LSD.begin(); m_LSD_it != m_LSD.end(); m_LSD_it++) {
			if (m_LSD_it->second.r1 != 0) Vs.insert(m_LSD_it->second.r1);
			if (m_LSD_it->second.r2 != 0) Vs.insert(m_LSD_it->second.r2);
	} 
	Vs.erase(m_id);
	
	//for all nodes v
	for(set<int>::iterator it = Vs.begin(); it != Vs.end(); it++) {
		for(m_LSD_it = m_LSD.begin(); m_LSD_it != m_LSD.end(); m_LSD_it++) {
			//if v is adjacent to u
			if ((m_LSD_it->second.r1 == *it && m_LSD_it->second.r2 == m_id) || 
					(m_LSD_it->second.r2 == *it && m_LSD_it->second.r1 == m_id)){
				//D(v) = C(u,v)
				Dv.insert(pair<int,int>(*it, m_LSD_it->second.cost));
				Pv.insert(pair<int,int>(*it, m_id));
			}
		} 
	} 

	for (set<int>::iterator it = Vs.begin(); it != Vs.end(); it++)	{
		//else D(v) = infinity
		Dv.insert(pair<int,int>(*it, std::numeric_limits<int>::max()-1));
		Pv.insert(pair<int,int>(*it, m_id));
	}

	//while all nodes not in N'
	while(N.size() != Vs.size() + 1){

		//assuming no negative weights
		int minW = std::numeric_limits<int>::max();
		int w = 0;

		//find w not in N' such that D(w) is a minimum
		for (std::map<int, int>::iterator it = Dv.begin(); it != Dv.end(); it++) {

			if (N.find(it->first) == N.end() && it->second < minW){
				minW = it->second;
				w = it->first;
			}

		}

		//add w to N'
		N.insert(w);

		//update D(v) for all v adjacent to w and not in N'
		for(set<int>::iterator it = Vs.begin(); it != Vs.end(); it++) {
			for(m_LSD_it = m_LSD.begin(); m_LSD_it != m_LSD.end(); m_LSD_it++) {
				if (((m_LSD_it->second.r1 == *it && m_LSD_it->second.r2 == w) || 
						(m_LSD_it->second.r2 == *it && m_LSD_it->second.r1 == w)) &&
					 	N.find(*it) == N.end()){
					
					//D(v) = min( D(v), D(w) + c(w,v) ) 
					int newCost = minW + m_LSD_it->second.cost;
					int v = *it;
					if (newCost < Dv[*it]){
						std::map<int, int>::iterator it = Dv.find(v);
						Dv.erase(it);
						Dv.insert(pair<int,int>(v, newCost));

						std::map<int, int>::iterator it2 = Pv.find(v);
						Pv.erase(it2);
						Pv.insert(pair<int,int>(v, w));
					}
				}
			} 
		} 
	}

	//prints the results of shortest path
	m_log << "# RIB" << endl;

	for (int i = 1; i <= NBR_ROUTER; i++){
		
		if (i == m_id){
			m_log << "R" << m_id << " -> " << "R" << i <<  " -> " << "Local, 0" << endl;
		}

		else if (Vs.find(i) != Vs.end()){

			if (i != m_id){
				int path = i;
						
				while (Pv[path] != m_id){
					path = Pv[path];
				}

					m_log << "R" << m_id << " -> " << "R" << i 
								<<  " -> " << path << ", " << Dv[i] << endl;
			}
		}
	}
}


void Router::printTopology(){

		//prints the topology database.

		//in my opinion, this table format is far more informative then the one given
		//in the assignment description, as it gives a better picture of the 
		//actual network topology, while conveying the same information

		m_log << "# Topology Database" << endl;
		m_log << "Link\tFrom\tTo\tCost\t" << endl;

		for(m_LSD_it = m_LSD.begin(); m_LSD_it != m_LSD.end(); m_LSD_it++) {

			string r1 = static_cast<ostringstream*>
							( &(ostringstream() << m_LSD_it->second.r1) )->str();
			string r2 = static_cast<ostringstream*>
							( &(ostringstream() << m_LSD_it->second.r2) )->str();

			//if router information isn't yet known, print "?"	
			if (m_LSD_it->second.r1 == 0) r1 = "?";
			if (m_LSD_it->second.r2 == 0) r2 = "?";

			m_log << m_LSD_it->first << "\t " 
					 << r1 << "\t "
					 << r2 << "\t " 
					 << m_LSD_it->second.cost << "\t " << endl;
		}

}


int main(int argc, char** argv) {

	int router_id;
	string nse_host;
	int nse_port;
	int router_port;

	//initialize parameters
	if (argc == 5){
		router_id = atoi(argv[1]);
		nse_host = argv[2];
		nse_port = atoi(argv[3]);
		router_port = atoi(argv[4]);
	}
	
	else {
		std::cerr
				<< "Usage: " 
				<< argv[0] 
				<< " <router_id> <nse_host> <nse_port> <router_port>" 
				<< std::endl;
		return 0;
	}

	//run router
	Router r(router_id, nse_host, nse_port, router_port);
	r.connectToNse();
	r.run();


	
}
