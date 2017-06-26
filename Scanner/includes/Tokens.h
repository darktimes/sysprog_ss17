#pragma once

#include "TokenType.h"
#include "String.h"
#include "SymbolTable.h"

struct TokenInfo {
		TokenInfo(int line, int col);
		int line;
		int col;
	};

struct TokenBufferInfo {
		TokenBufferInfo(int bufferIndex, int bufferPos);
		int bufferIndex;
		int bufferPos;
};

class Token {
public:
	Token(TokenType tokenType, TokenInfo* tokenInfo);
	TokenInfo* tokenInfo;
	
	TokenType tokenType;
	virtual ~Token();
};

class LexemToken: public Token {
	public:
		LexemToken(TokenType tokenType, TokenInfo* tokenInfo, String *lexem, Symbol* symbolTableReference);
		String* lexem;
		Symbol* symbolTableKeyReference;
		virtual ~LexemToken();
};

class IntegerToken: public Token {
	public:
		IntegerToken(TokenType tokenType, TokenInfo* tokenInfo, int value);
		int value;
};

class UnknownToken: public Token {
	public:
		UnknownToken(TokenType tokenType, TokenInfo* tokenInfo, char c);
		char character;
};

class ErrorToken: public Token {
	public:
		ErrorToken(TokenType tokenType, TokenInfo* tokenInfo, String* err_msg);
		String* err_msg;
		virtual ~ErrorToken();
};
