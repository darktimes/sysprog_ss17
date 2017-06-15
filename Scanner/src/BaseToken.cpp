#include "BaseToken.h"

BaseToken::BaseToken(TokenType tokenType, TokenInfo* tokenInf, String *lexem) {
	this->tokenType = tokenType;
	this->tokenInfo = tokenInf;
	this->lexem = lexem;
}

BaseToken::~BaseToken() {
	delete lexem;
	delete tokenInfo;
}

TokenInfo::TokenInfo(int line, int pos) :line(line), pos(pos) {

}
