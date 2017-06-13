/*
 * IntegerToken.cpp
 *
 *  Created on: Jun 7, 2017
 *      Author: vladimir
 */

#include "IntegerToken.h"
#include "TokenType.h"

IntegerToken::IntegerToken(TokenType tokenType, int line, int pos, int value) {
	this->tokenType = tokenType;
	this->line = line;
	this->pos = pos;
	this->value = value;
}

IntegerToken::~IntegerToken() {

}

