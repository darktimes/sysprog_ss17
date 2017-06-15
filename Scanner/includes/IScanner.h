#pragma once

#include "String.h"
#include "TokenType.h"

/*
 * Interface to be used by 'Automat' (Finite State Machine)
 */
class IScanner {
public:
	virtual ~IScanner() {}
	virtual void mkToken(TokenType tokenType,String* lexem) = 0; // creates the token of given type and lexem
	virtual void ungetChar(int number) = 0; // read just position of scanner. 0 => child class must implement

};


