#include "Scanner.h"

#include <iostream> //std out
#include <stdlib.h> //strtol
#include <error.h>
#include <errno.h>
#include <limits.h>
#include <stdexcept>

const int Scanner::TOKEN_MAX_LENGTH = 128;

Scanner::Scanner(const char* filepath, SymbolTable* symtab) {
	this->buffer = new Buffer(filepath);
	this->automat = new Automat(this);
	this->symtab = symtab;
	this->currentToken = nullptr;
	this->isScanningToken= false;
	this->finished = false;
	this->currentTokenInfo = nullptr;
	this->currentTokenLength = 0;
	if (buffer->isNoFile()) {
		std::cout<<"There was an error opening the file."<<std::endl;
	}

}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
}

BaseToken *Scanner::nextToken() {
	currentToken = nullptr;
	currentTokenInfo = nullptr;
	currentTokenLength = 0;

	if (finished || buffer->isNoFile()) {
		return nullptr;
	}
	isScanningToken = true;

	this->currentTokenInfo = new TokenInfo(buffer->getCurrentLine(), buffer->getCurrentPos());

	while (isScanningToken) {
		automat->process(buffer->getChar());
		currentTokenLength++;
	}
	return currentToken;
}

void Scanner::mkToken(TokenType tokenType, String* lexem) {
	isScanningToken = false;
	if (currentTokenLength >= TOKEN_MAX_LENGTH) {
		currentToken = new BaseToken(TokenLengthExceeded, currentTokenInfo, lexem);
	} else if (tokenType == TokenIdentifier) {
		currentToken = new SymbolToken(tokenType, currentTokenInfo, symtab->create(*lexem));
	} else if (tokenType == TokenInteger) {
		errno = 0;
		long int tempInt = strtol(lexem->getStr(), NULL, 10);
		if (errno == ERANGE || (tempInt < INT_MIN) || (tempInt > INT_MAX)) {
			currentToken = new BaseToken(TokenError, currentTokenInfo, lexem); //replace with tokens, that report proper error, if needed
		} else {
			currentToken = new BaseToken(tokenType, currentTokenInfo, lexem);
		}
	} else {
		if (tokenType == TokenEOF) {
				finished = true;
			}
		currentToken = new BaseToken(tokenType, currentTokenInfo, lexem);
	}

}

void Scanner::ungetChar(int number) {
	buffer->ungetChar(number);
}


