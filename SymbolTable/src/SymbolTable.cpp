#include "SymbolTable.h"
#include <stdlib.h>
SymbolTable::SymbolTable() :
		tableSize(64), existingElements(0), data(
				new std::vector<Symbol*>[tableSize]) {

}

SymbolTable::~SymbolTable() {
	for (unsigned i = 0; i < tableSize; i++) {

		for (Symbol* symbol : data[i]) {
			delete symbol;
		}

	}
	delete[] data;
}

Symbol* SymbolTable::create(String str, TokenType tokenType) {
	if (needsResize()) {
		resize();
	}
	unsigned i = strhash(str);

	for (Symbol* symbol : data[i]) {
		if (symbol->ident.compare(str)) {
			return symbol;
		}
	}
	Symbol* result = new Symbol(str, tokenType, NoType);
	data[i].push_back(result);
	existingElements++;
	return result;
}

Symbol* SymbolTable::getSymbolOf(String str) {
	for (Symbol* symbol : data[strhash(str)]) {
		if (symbol->ident.compare(str)) {
			return symbol;
		}
	}
	return nullptr;
}

/**
 * djb2 algorithm k = 33
 */
unsigned long SymbolTable::strhash(const String str, const unsigned offset) {
	unsigned long hash = 5381;
	for (int i = 0; i < str.getSize(); i++) {
		hash = hash * 33 + (int) str[i] + offset;
	}
	return hash % tableSize;
}
/**
 * falls >50% voll -> true
 */
bool SymbolTable::needsResize() {
	return existingElements >= tableSize * 0.50;
}

/**
 * neue Table doppelt so gross machen, alte copieren und loeschen
 */
void SymbolTable::resize() {
	std::vector<Symbol*>* old = data;
	unsigned oldsize = tableSize;
	tableSize *= 2;
	data = new std::vector<Symbol*>[tableSize];

	for (unsigned i = 0; i < oldsize; i++) {
		for (Symbol* symbol : old[i]) {
			int j = strhash(symbol->ident);
			data[j].push_back(symbol);
		}
	}
}

Symbol::Symbol(String str, TokenType tokenType, NodeCheckType checkType) {
	this->ident = String(str);
	this->tokenType = tokenType;
	this->checkType = NoType;
}

Symbol::~Symbol() {
}
