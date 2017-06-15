#include "SymbolToken.h"

SymbolToken::SymbolToken(TokenType tokenType, TokenInfo tokenInfo, Symbol* symbol) : BaseToken(tokenType, tokenInfo, &symbol->ident2) {
	this->symbol = symbol;
}

SymbolToken::~SymbolToken() {

}
