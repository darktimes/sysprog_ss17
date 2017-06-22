#pragma once

#include "Scanner.h"
#include "SymbolTable.h"
#include "TreeEntities.h"

class Node;

class Parser{

	public:
		Parser(const char* file_path);
		virtual ~Parser();
		void parse();

	private:
		Scanner* scanner;
		SymbolTable* symbolTable;
		Token* currentToken;

		void nextToken();
};

class ParseVisitor {
public:
	ParseVisitor();
	virtual ~ParseVisitor() {}
	void parseNode(Node* node);
};
