#pragma once

class Symbol final {
public:
//	Symbol(char const* ident);
	Symbol(String ident2);
	~Symbol();
	String ident2;
	//char const* ident;

private:
};

class Symtable final {
public:
	Symtable();
	~Symtable();
	//Create if non-existant or return already existing
	Symbol* create(String str);

private:
	unsigned tableSize;
	unsigned existingElements;
	Symbol** data;
	/*
	 *  a freaking comment
	 * */
	unsigned long strhash(const String str, const unsigned offset = 0);
	unsigned indexOf(const String str);
	bool isFull();
	void resize();
	void resizeCreate(Symbol* sym);
};

