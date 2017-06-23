#pragma once

#include "String.h"
#include "TokenType.h"
#include <vector>
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
	Symbol* getSymbolOf(String str);

private:
	unsigned tableSize;
	unsigned existingElements;
	std::vector<Symbol*>* data;

	unsigned long strhash(const String str, const unsigned offset = 0);
	unsigned innerIndexof(const String str);
	bool needsResize();
	void resize();
//	void resizeCreate(Symbol* sym);
};

