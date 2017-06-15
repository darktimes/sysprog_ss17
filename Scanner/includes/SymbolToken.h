#pragma once

#include "BaseToken.h"
#include "SymbolTable.h"

class SymbolToken: public BaseToken {
public:
	SymbolToken(TokenType tokenType, TokenInfo tokenInf, Symbol* symbol);
	virtual ~SymbolToken();
private:
	Symbol* symbol;
};
