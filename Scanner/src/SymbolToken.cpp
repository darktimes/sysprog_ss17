#include "SymbolToken.h"

SymbolToken::SymbolToken(TokenType tokenType, tokenInfo tokenInf, Symbol* symbol) {
	this->tokenType = tokenType;
	this->tokenInf = tokenInf;
	this->symbol = symbol;
}

SymbolToken::~SymbolToken() {

}
