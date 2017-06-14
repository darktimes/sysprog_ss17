/*
 * IToken.h
 *
 *  Created on: Jun 8, 2017
 *      Author: vladimir
 */
#pragma once

#include "TokenType.h"
#include "String.h"

struct tokenInfo {
		int line;
		int pos;
	};

class BaseToken {
public:
	BaseToken(TokenType tokenType, tokenInfo tokenInf, String *lexem);
	virtual ~BaseToken();
private:
	TokenType tokenType;
	tokenInfo tokenInf;
	String* lexem;
};

