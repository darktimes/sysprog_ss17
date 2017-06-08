/*
 * ErrorToken.cpp
 *
 *  Created on: Jun 7, 2017
 *      Author: vladimir
 */

#include "ErrorToken.h"

ErrorToken::ErrorToken(TokenType tokenType, int line ,int pos, char errorToken) {
	this->tokenType = tokenType;
	this->line = line;
	this->pos = pos;
	this->errorToken = errorToken;
}

ErrorToken::~ErrorToken() {

}


