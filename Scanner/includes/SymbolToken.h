/*
 * SymbolToken.h
 *
 *  Created on: Jun 7, 2017
 *      Author: vladimir
 */

#pragma once

#include "IToken.h"
#include "SymbolTable.h"

class SymbolToken: public IToken {
public:
	SymbolToken(TokenType tokenType, int line, int pos, Symbol* symbol);
	virtual ~SymbolToken();
private:
	TokenType tokenType;
	int line;
	int pos;
	Symbol* symbol;
};
