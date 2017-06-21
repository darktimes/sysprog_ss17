#include "SymbolTable.h"
#include <stdlib.h>
SymbolTable::SymbolTable() :tableSize(64), existingElements(0), data(new Symbol*[tableSize]) {
	data = (Symbol**) malloc(sizeof(Symbol*) * tableSize);
}

SymbolTable::~SymbolTable() {
	for (unsigned i = 0; i < tableSize; ++i) {
		Symbol* sym = data[i];
		if (sym != nullptr)
			delete sym;
	}
	delete[] data;
}

Symbol* SymbolTable::create(String str, TokenType tokenType) {
	if (isFull())
		resize();

	unsigned i = indexOf(str);

	if (data[i] == nullptr) {
		Symbol *sym = new Symbol(str, tokenType);
		data[i] = sym;
		existingElements++;
		return sym;
	} else
		return data[i];
}

unsigned SymbolTable::indexOf(const String str) {
	unsigned long h = strhash(str);
	unsigned i = 0;
	while (data[h] != nullptr && data[h]->ident.compare(str) != 0)
		h = strhash(str, i++);
	return h;
}
/**
 * djb2 algorithm k = 33
 */
unsigned long SymbolTable::strhash(const String str, const unsigned offset) {
	unsigned long hash = 5381;
	for (int i = 0;  i < str.getSize(); i++) {
		hash = hash * 33 + (int)str[i] + offset;
	}
	return hash % tableSize;
}
/**
 * falls >50% voll -> true
 */
bool SymbolTable::isFull() {
	return existingElements >= tableSize * 0.50;
}

/**
 * neue Table doppelt so gross machen, alte copieren und loeschen
 */
void SymbolTable::resize() {
	Symbol** oldData = data;
	unsigned oldSize = tableSize;
	tableSize *= 2;
	data = new Symbol*[tableSize];
	data = (Symbol**) malloc(sizeof(Symbol*) * tableSize);

	for (unsigned i = 0; i < oldSize; ++i) {
		Symbol* sym = oldData[i];
		if (sym != nullptr)
			resizeCreate(sym);
	}
	delete[] oldData;
}

void SymbolTable::resizeCreate(Symbol *sym) {
	unsigned i = indexOf(sym->ident);
	data[i] = sym;
}

Symbol::Symbol(String str, TokenType tokenType) {
	this->ident = String(str);
	this->tokenType = tokenType;
}

Symbol::~Symbol() {
}
