/*
 * IntegerToken.h
 *
 *  Created on: Jun 7, 2017
 *      Author: vladimir
 */

#pragma once

#include "IToken.h"

class IntegerToken: public IToken {
public:
	IntegerToken(TokenType tokenType, int line, int pos, int value);
	virtual ~IntegerToken();
	//IntegerToken* createToken(TokenType tokenType, int line, int pos, int value);
private:
	TokenType tokenType;
	int line;
	int pos;
	int value;
};
