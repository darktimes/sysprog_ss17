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
#include "BaseToken.h"
//#include "IntegerToken.h"
#include "SymbolToken.h"
//#include "ErrorToken.h"
#include "TokenType.h"
#include "Buffer.h"

class Scanner: public IScanner {
public:
	Scanner(const char* filepath, SymbolTable *symtab);
	virtual ~Scanner();
	bool active;
	BaseToken *nextToken(void);
	void mkToken(TokenType tokenType, String* lexem);
	void ungetChar(int number);
	BaseToken *currentToken;


private:
	Buffer *buffer;
	Automat *automat;
	SymbolTable *symtab;

//	int currentLine;
//	int currentPos;
	TokenInfo tokenInfo;

	BaseToken *createToken(TokenType tokenType, TokenInfo tokenInf, char *lexem);

};

