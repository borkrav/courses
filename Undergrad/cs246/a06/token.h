// File token.h

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>

class Token
{
    char head;
    std::string tail;
public:
    bool isSkinny( );
    Token (char hd, std::string tl);
    Token (char hd);  // Set tail = ""
    Token ( );

    char getHead( );
    std::string getTail ( );
    
    // Output in cooked format, e.g. as
    //    +       skinny token
    //    ":abc   fat token
    // All tokens followed by newline

    void inputCookedToken( );
    void outputCookedToken ( );
    friend std::ostream& operator <<
        (std::ostream & os, const Token & tok);
};

// Output in raw format, e.g. as
//    +	          skinny token
//    "abc"	  fat token
// All tokens followed by blank except
//    semicolon (followed by newline)

std::ostream& operator <<
    (std::ostream & os, const Token & tok);

#endif
