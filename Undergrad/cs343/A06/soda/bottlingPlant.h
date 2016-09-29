#ifndef __BOTTLINGPLANT__
#define __BOTTLINGPLANT__

#include "common.h"

extern MPRNG number_generator;

_Task Truck;
_Task NameServer;

_Task BottlingPlant {
    void main();
		Printer *m_printer;

		unsigned int m_maxShipped, m_delay;
		bool m_finished;
		unsigned int m_inventory[ NUMBER_OF_FLAVOURS ];

		Truck* m_truck;
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
		~BottlingPlant();
    bool getShipment( unsigned int cargo[] );
};

#endif
