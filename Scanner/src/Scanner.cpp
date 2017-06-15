#include "Scanner.h"

#include <iostream> //std out
#include <stdlib.h> //strtol
#include <error.h>
#include <errno.h>
#include <limits.h>
#include <stdexcept>

Scanner::Scanner(const char* filepath, SymbolTable* symtab) {
	this->buffer = new Buffer(filepath);
	this->automat = new Automat(this);
	this->symtab = symtab;
	this->currentToken = nullptr;
	this->isScanningToken= false;
	this->finished = false;
	this->currentTokenInfo = nullptr;

	if (buffer->isNoFile()) {
		std::cout<<"There was an error opening the file.";
	}

}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
}

BaseToken *Scanner::nextToken() {
	currentToken = nullptr;
	currentTokenInfo = nullptr;

	if (finished || buffer->isNoFile()) {
		return nullptr;
	}
	isScanningToken = true;

	this->currentTokenInfo = new TokenInfo(buffer->getCurrentLine(), buffer->getCurrentPos());

	while (isScanningToken) {
		automat->process(buffer->getChar());
	}
	return currentToken;
}

void Scanner::mkToken(TokenType tokenType, String* lexem) {
	isScanningToken = false;

	if (tokenType == TokenIdentifier) {
		currentToken = new SymbolToken(tokenType, currentTokenInfo, symtab->create(*lexem));
	} else if (tokenType == TokenInteger) {
		errno = 0;
		long int tempInt = strtol(lexem->getStr(), NULL, 10);
		if (errno == ERANGE) {
			throw std::runtime_error("Integer conversion is outside a function's range. Overflow");
		} else if ((tempInt < INT_MIN) || (tempInt > INT_MAX)) {
			throw std::runtime_error("Integer overflow");
		}
		currentToken = new BaseToken(tokenType, currentTokenInfo, lexem);
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


