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
		TokenInfo(int line, int pos);
		int line;
		int pos;
	};

class BaseToken {
public:
	BaseToken(TokenType tokenType, TokenInfo* tokenInfo, String *lexem);
	TokenInfo* tokenInfo;
	String* lexem;
	TokenType tokenType;
	virtual ~BaseToken();
protected:


};

