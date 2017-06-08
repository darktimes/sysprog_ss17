/*
 * SymbolToken.cpp
 *
 *  Created on: Jun 7, 2017
 *      Author: vladimir
 */

#include "SymbolToken.h"

SymbolToken::SymbolToken(TokenType tokenType, int line, int pos, Symbol* symbol) {
	this->tokenType = tokenType;
	this->line = line;
	this->pos = pos;
	this->symbol = symbol;
}

SymbolToken::~SymbolToken() {

}


