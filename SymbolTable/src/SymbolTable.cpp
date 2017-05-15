#include "String.h"
#include "SymbolTable.h"
#include <stdlib.h>

Symtable::Symtable() :
		tableSize(64), existingElements(0), data(new Symbol*[tableSize]) {
	//memset(data, 0, sizeof(Symbol*) * tableSize);
	data = (Symbol**) malloc(sizeof(Symbol*) * tableSize);
}

Symtable::~Symtable() {
	for (unsigned i = 0; i < tableSize; ++i) {
		Symbol* sym = data[i];
		if (sym != nullptr)
			delete sym;
	}
	delete[] data;
}

Symbol* Symtable::create(String str) {
	if (isFull())
		resize();

	unsigned i = indexOf(str);

	if (data[i] == nullptr) {
		Symbol *sym = new Symbol(str);
		data[i] = sym;
		existingElements++;
		return sym;
	} else
		return data[i];
}

unsigned Symtable::indexOf(const String str) { //methode code aendern so dass es passt
	// const char oder unsere string classe
	unsigned long h = strhash(str);
	unsigned i = 0;
	while (data[h] != nullptr && data[h]->ident2.compare(str) != 0)
		h = strhash(str, i++);
	return h;
}

unsigned long Symtable::strhash(const String str, const unsigned offset) {
	// djb2 algorithm k = 33
	unsigned long hash = 5381;
	int c;
	while ((c = str++))
		hash = hash * 33 + c + offset;
	return hash % tableSize;
}

bool Symtable::isFull() {	//falls >75% voll -> true
	return existingElements >= tableSize * 0.75;
}

void Symtable::resize() {// neue Table doppelt so gross machen, alte copieren und loeschen
	Symbol** oldData = data;
	unsigned oldSize = tableSize;
	tableSize *= 2;
	data = new Symbol*[tableSize];
	//memset(data, 0, sizeof(Symbol*) * tableSize);
	data = (Symbol**) malloc(sizeof(Symbol*) * tableSize);

	for (unsigned i = 0; i < oldSize; ++i) {
		Symbol* sym = oldData[i];
		if (sym != nullptr)
			resizeCreate(sym);
	}
	delete[] oldData;
}

void Symtable::resizeCreate(Symbol *sym) {
	unsigned i = indexOf(sym->ident2);
	data[i] = sym;
}

//Symbol::Symbol(char const *ident){
//	auto len = strlen(ident);
//	this->ident = new char[len + 1];
//	strcpy((char*) this->ident, ident);
//}

Symbol::Symbol(String indent2) {
	this->ident2 = ident2;
}

Symbol::~Symbol() {
	delete[] ident2;
}
