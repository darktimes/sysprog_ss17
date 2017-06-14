#include "BaseToken.h"

BaseToken::BaseToken(TokenType tokenType, tokenInfo tokenInf, String *lexem) {
	this->tokenType = tokenType;
	this->tokenInf = tokenInf;
	this->lexem = lexem;
}

BaseToken::~BaseToken() {

}
