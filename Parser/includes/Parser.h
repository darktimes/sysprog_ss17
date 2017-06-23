#pragma once

#include "Scanner.h"
#include "SymbolTable.h"
#include "TreeEntities.h"
#include "Set.h"

class Node;

class ParseVisitor;

class ITokenGenerator {
	public:
		virtual Token* nextToken() = 0;
		virtual ~ITokenGenerator() {};
};

class Parser: ITokenGenerator{

	public:
		Parser(const char* file_path);
		virtual ~Parser();
		Node* parse();
		Token* nextToken() override;
		bool isErrored() const;

	private:
		Scanner* scanner;
		SymbolTable* symbolTable;
		ParseVisitor* parseVisitor;

};

class ParseVisitor {

	public:
		ParseVisitor(ITokenGenerator* tokenGenerator);
		virtual ~ParseVisitor() {}
		void parseNode(Node* node);
		bool isErrored() const;
		void nextToken();
		void printError(String msg);

	private:
		ITokenGenerator* tokenGenerator;
		Token* currentToken;
		bool errored;
};
