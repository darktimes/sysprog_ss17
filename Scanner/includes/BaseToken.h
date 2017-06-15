/*
 * IToken.h
 *
 *  Created on: Jun 8, 2017
 *      Author: vladimir
 */
#pragma once

#include "TokenType.h"
#include "String.h"

struct TokenInfo {
		int line;
		int pos;
	};

class BaseToken {
public:
	BaseToken(TokenType tokenType, TokenInfo tokenInfo, String *lexem);
	String* lexem;
	TokenType tokenType;
	TokenInfo tokenInfo;
	virtual ~BaseToken();
protected:


};

