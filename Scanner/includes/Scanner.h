/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#pragma once

#include "IScanner.h"
#include "SymbolTable.h"
#include "Automat.h"
#include "IntegerToken.h"
#include "SymbolToken.h"
#include "ErrorToken.h"
#include "TokenType.h"
#include "Buffer.h"
#include "IToken.h"

class Scanner: public IScanner {
public:
	Scanner(const char* filepath, SymbolTable *symtab);
	virtual ~Scanner();
	bool active;
	IToken *nextToken(void);
	void mkToken(TokenType tokenType, String* lexem);
	void ungetChar(int number);



private:
	Buffer *buffer;
	Automat *automat;
	SymbolTable *symtab;
	IToken *currentToken;
	int currentLine;
	int currentPos;

	IToken *createToken(TokenType tokenType, int row, int column, char *lexem);

};

