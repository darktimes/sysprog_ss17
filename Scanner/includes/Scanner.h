#pragma once

#include "IScanner.h"
#include "SymbolTable.h"
#include "Automat.h"
//#include "ErrorToken.h"
#include "TokenType.h"
#include "Buffer.h"
#include "Tokens.h"

class Scanner: public IScanner {
public:
	static const int TOKEN_MAX_LENGTH;

	Scanner(const char* filepath, SymbolTable *symtab);
	virtual ~Scanner();

	Token *nextToken(void);
	void mkToken(TokenType tokenType, String* lexem);
	void ungetChar(int number);
	Token *currentToken;


private:
	int currentLine;
	int currentColumn;
	Buffer *buffer;
	Automat *automat;
	SymbolTable *symtab;
	bool isScanningToken;
	bool finished;
//	TokenInfo* currentTokenInfo;
	unsigned int currentTokenLength;

	void adjustIndicies(String* lexem);
};

