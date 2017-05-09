#ifndef SYMTABLE_H_
#define SYMTABLE_H_


class Symbol final {
public:
	Symbol(char const* ident);
	~Symbol();
	char const* ident;

private:
};

class Symtable final {
public:
	Symtable();
	~Symtable();
	//Create if non-existant or return already existing
	Symbol* create(char* str);

private:
	unsigned tableSize;
	unsigned existingElements;
	Symbol** data;

	unsigned long strhash(const char* str, const unsigned offset = 0);
	unsigned indexOf(const char* str);
	bool isFull();
	void resize();
	void resizeCreate(Symbol* sym);
};

#endif
