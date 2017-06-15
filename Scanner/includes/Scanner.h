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
	static const int TOKEN_MAX_LENGTH;

	Scanner(const char* filepath, SymbolTable *symtab);
	virtual ~Scanner();

	BaseToken *nextToken(void);
	void mkToken(TokenType tokenType, String* lexem);
	void ungetChar(int number);
	BaseToken *currentToken;


private:
	Buffer *buffer;
	Automat *automat;
	SymbolTable *symtab;
	bool isScanningToken;
	bool finished;
	TokenInfo* currentTokenInfo;
	unsigned int currentTokenLength;
};

