// File tokenbuffer.h

#ifndef TOKEN_BUFFER
#define TOKEN_BUFFER

#include "token.h"
#include <vector>
#include <list>

class TokenBuffer
{
    std::list<Token> buffer;
    std::list<Token>::iterator it;
public:
    void inputCookedTokensIntoBuffer ( );
    void outputCookedTokensFromBuffer ( );
    void outputRawTokensFromBuffer ( );
    void rewind ( ); // Sets iterator to beginning of buffer
    Token getToken ( );  // Rewind before using this;
	// Calls to getToken return each token in the buffer
};

#endif
