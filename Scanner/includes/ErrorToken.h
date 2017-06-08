/*
 * ErrorToken.h
 *
 *  Created on: Jun 7, 2017
 *      Author: vladimir
 */

#pragma once

#include "IToken.h"

class ErrorToken: public IToken {
public:
	ErrorToken(TokenType tokenType, int line, int pos, char errorToken);
	virtual ~ErrorToken();
private:
	TokenType tokenType;
	int line;
	int pos;
	char errorToken;
};
