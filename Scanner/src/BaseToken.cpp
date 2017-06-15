#include "BaseToken.h"

BaseToken::BaseToken(TokenType tokenType, TokenInfo tokenInf, String *lexem) {
	this->tokenType = tokenType;
	this->tokenInfo = tokenInf;
	this->lexem = lexem;
}

BaseToken::~BaseToken() {

}
