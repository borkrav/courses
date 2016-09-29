#include <iostream>
#include <cstdlib>          // access: rand, srand
#include <unistd.h>         // access: getpid
using namespace std;

bool rtn( int i ) {
    if ( rand() % 5 == 0 ) return true;
}
int main( int argc, char *argv[] ) {
    int seed = getpid();
    if ( argc == 2 ) seed = atoi( argv[1] );
    srand( seed );

    for ( int i = 0; i < 10; i += 1 ) {
        if (rtn( i )){
			cout << "single loop:" << i << endl;
			break;
		}
    }

    for ( int i = 0; i < 10; i += 1 ) {
        for ( int j = 0; j < 10; j += 1 ) {
            if (rtn( j )){
				cout << "double loop:" << j << endl;
				goto done;
			}
        }
    }
	
	done:;
    
}
