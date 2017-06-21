#pragma once

#include "String.h"
#include "TokenType.h"
class Symbol final {
public:
	Symbol(String ident, TokenType tokenType);
	~Symbol();
	String ident;
	TokenType tokenType;

private:
};

class SymbolTable final {
public:
	SymbolTable();
	~SymbolTable();
	//Create if non-existent or return already existing
	Symbol* create(String str, TokenType tokenType);

private:
	unsigned tableSize;
	unsigned existingElements;
	Symbol** data;

	unsigned long strhash(const String str, const unsigned offset = 0);
	unsigned indexOf(const String str);
	bool isFull();
	void resize();
	void resizeCreate(Symbol* sym);
};

