/*
 * IToken.h
 *
 *  Created on: Jun 8, 2017
 *      Author: vladimir
 */
#pragma once

#include "TokenType.h"

class IToken {
public:

private:
	int line;
	int pos;
	TokenType tokenType;
};
