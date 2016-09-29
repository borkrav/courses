// File tokennames.h

// Note that there is no file named tokennames.cpp

// These names of tokens e.g. plusToken should be used instead
//   of literal constansts, e.g., '+'

// These are used with scanners/interpreters in CS246
// Many of these tokens are not of use in a particular language

#ifndef _TOKENNAMES
#define _TOKENNAMES

// Single character tokens
const char shortToken = '.';  // Not really a token.  Used by roughKind
const char semicolonToken = ';';  
const char assignToken = '='; // Single = (equal sign)
const char plusToken = '+';
const char minusToken = '-';
const char multiplyToken = '*';
const char divideToken = '/';
const char lessToken = '<';
const char gtrToken = '>';
const char leftParenToken = '(';  
const char rightParenToken = ')';
const char leftBraceToken = '{';  
const char rightBraceToken = '}';

const char hashToken = '#';  
const char commaToken = ','; 

// Double character tokens
const char equalToken = 'e';  // Double ==
const char leftShiftToken = 'L';
const char rightShiftToken = 'R';

// Complex tokens
const char stringToken = '"';
const char charToken = '\'';
const char intToken = '9';
const char identifierToken = 'x';

const char EOFToken = 'E';
const char badToken = '?';

#endif
