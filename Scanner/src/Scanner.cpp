/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

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
	this->currentLine = 0;
	this->currentPos = 0;
	this->active = false;
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
}

IToken *Scanner::nextToken() {
	active = true;
	delete currentToken;

	this->currentLine = buffer->getCurrentLine();
	this->currentPos = buffer->getCurrentPos();

	while (active) { /*if no symbols in buffer => \0 */
		if (currentToken == nullptr) {
			automat->process(buffer->getChar());
		} else {
			//this->currentLine = 0;
			//this->currentPos = 0;
			return currentToken;
		}
	}

	throw std::runtime_error("Reached end of nextToken while being active.");
	//active, EOF
}

void Scanner::mkToken(TokenType tokenType, String* lexem) {
	active = false;

	if (tokenType == TokenIdentifier) {
		currentToken = new SymbolToken(tokenType, currentLine, currentPos, symtab->create(*lexem));
	} else if (tokenType == TokenInteger) {
		errno = 0;
		long int tempInt = strtol(lexem->getStr(), NULL, 10);
		if (errno == ERANGE) {
			std::cout << "Integer conversion is outside a function's range. Overflow. \n";
		} else if ((tempInt < INT_MIN) || (tempInt > INT_MAX)) {
			std::cout << "Integer overflow \n";
		}
		currentToken = new IntegerToken(tokenType, currentLine, currentPos, tempInt);
	} else if (tokenType == TokenUnknown) {
		currentToken = new ErrorToken(tokenType, currentLine, currentPos, buffer->getChar());
	}
}

void Scanner::ungetChar(int number) {
	buffer->ungetChar(number);
}


