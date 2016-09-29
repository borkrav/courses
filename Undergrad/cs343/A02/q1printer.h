#include <uC++.h>
#include <iostream>
#include <string>
#include "PRNG.h"
#include <vector>
#include <utility>

class Printer {

	unsigned int players;
	unsigned int cards;
	std::vector <std::pair <int, int> > buffer;
	void flush();
  public:
    Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards );
    void prt( const unsigned int id, const unsigned int took );
};
