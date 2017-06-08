#pragma once

#include "String.h"

class Symbol final {
public:
	Symbol(String ident2);
	~Symbol();
	String ident2;

private:
};

class SymbolTable final {
public:
	SymbolTable();
	~SymbolTable();
	//Create if non-existent or return already existing
	Symbol* create(String str);

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

