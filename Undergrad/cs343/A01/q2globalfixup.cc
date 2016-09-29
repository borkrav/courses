#include <iostream>
using namespace std;

int myfixup1( int i ) { return i + 2; }
int myfixup2( int i ) { return i + 1; }
int myfixup3( int i ) { return i + 3; }

int (*fixup)(int i) = myfixup1;

int rtn2( int p );                    // forward declaration

int rtn1( int p ) {
  int (*fixupEntry)(int i) = fixup;
  if ( p <= 0 ) return 0;                                  // base case
    if ( p % 2 != 0 ) { 
	fixup = myfixup2;                                   // even ?
        p = rtn2( p - 1 );
	fixup = fixupEntry;
    } else {
	fixup = myfixup3;
        p = rtn1( p - 2 );
	fixup = fixupEntry;
    }
    if ( p % 3 != 0 ) p = fixup( p );
    cout << p << " ";
    return p + 1;
}
int rtn2( int p ) {
  int (*fixupEntry)(int i) = fixup;
  if ( p <= 0 ) return 0;                                  // base case
    if ( p % 3 != 0 ) {
	fixup = myfixup1;                                    // even ?
        p = rtn2( p - 2 );
	fixup = fixupEntry;
    } else {
	fixup = myfixup2;
        p = rtn1( p - 1 );
	fixup = fixupEntry;
    }
    if ( p % 2 != 0 ) p = fixup( p );
    cout << p << " ";
    return p + 2;
}
int main() {
    cout << rtn2( 30 ) << endl;
}
