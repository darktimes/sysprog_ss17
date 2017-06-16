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
	currentLine = 1;
	currentColumn = 1;
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
}

Token *Scanner::nextToken() {
	currentToken = nullptr;
	currentTokenInfo = nullptr;
	currentTokenLength = 0;

	if (finished || buffer->isNoFile()) {
		return nullptr;
	}
	isScanningToken = true;

	this->currentTokenInfo = new TokenInfo(currentLine, currentColumn);

	while (isScanningToken) {
		char c = buffer->getChar();
		automat->process(c);
		currentTokenLength++;
	}
	return currentToken;
}

void Scanner::mkToken(TokenType tokenType, String* lexem) {

	isScanningToken = false;
	if (currentTokenLength >= TOKEN_MAX_LENGTH) {
		currentToken = new ErrorToken(tokenType, currentTokenInfo, new String("Token length exceeded"));
	} else if (tokenType == TokenIdentifier) {
		currentToken = new LexemToken(tokenType, currentTokenInfo, lexem, symtab->create(*lexem));
	} else if (tokenType == TokenInteger) {
		errno = 0;
		long int tempInt = strtol(lexem->getStr(), NULL, 10);
		if (errno == ERANGE || (tempInt < INT_MIN) || (tempInt > INT_MAX)) {
			currentToken = new ErrorToken(tokenType, currentTokenInfo, new String("Integer value out of range.")); //replace with tokens, that report proper error, if needed
		} else {
			currentToken = new IntegerToken(tokenType, currentTokenInfo, (int)tempInt);
		}
	} else if (tokenType == TokenUnknown) {
		currentToken = new UnknownToken(tokenType, currentTokenInfo, *lexem[0]);
	} else {
		if (tokenType == TokenEOF) {
				finished = true;
			}
		currentToken = new Token(tokenType, currentTokenInfo);
	}
	adjustIndicies(lexem);
	currentTokenInfo = nullptr;
}

void Scanner::ungetChar(int number) {

	buffer->ungetChar(number);
}

void Scanner::adjustIndicies(String* lexem) {

	for (int i = 0; i < lexem->getSize() - 1; i++) {
		if ((*lexem)[i] == '\n') {
			currentLine++;
			currentColumn = 1;
		} else {
			currentColumn++;
		}
	}
}


