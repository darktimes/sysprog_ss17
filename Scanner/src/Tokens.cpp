#include "Tokens.h"

Token::Token(TokenType tokenType, TokenInfo* tokenInf) {
	this->tokenType = tokenType;
	this->tokenInfo = tokenInf;
}

Token::~Token() {
	delete tokenInfo;
}

LexemToken::LexemToken(TokenType tokenType, TokenInfo* tokenInfo, String* lexem, Symbol* symbol): Token(tokenType, tokenInfo),
		lexem(lexem), symbolTableKeyReference(symbol) {

}

LexemToken::~LexemToken() {
	delete lexem;
	delete symbolTableKeyReference;
}

IntegerToken::IntegerToken(TokenType tokenType, TokenInfo* tokenInfo, int value): Token(tokenType, tokenInfo), value(value) {

}

UnknownToken::UnknownToken(TokenType tokenType, TokenInfo* tokenInfo, char character) : Token(tokenType, tokenInfo),
		character(character) {

}

ErrorToken::ErrorToken(TokenType tokenType, TokenInfo* tokenInfo, String* err_msg): Token(tokenType, tokenInfo), err_msg(err_msg) {

}

ErrorToken::~ErrorToken() {
	delete err_msg;
}

TokenInfo::TokenInfo(int line, int col) :line(line), col(col){

}

TokenBufferInfo::TokenBufferInfo(int bufferIndex, int bufferPos): bufferIndex(bufferIndex), bufferPos(bufferPos) {

}
