#include "Parser.h"

Parser::Parser(const char* file_path) {
	symbolTable = new SymbolTable();
	symbolTable->create(String("while"));
	symbolTable->create(String("WHILE"));
	symbolTable->create(String("if"));
	symbolTable->create(String("IF"));
	symbolTable->create(String("int"));
	symbolTable->create(String("read("));
	symbolTable->create(String("write("));
	scanner = new Scanner(file_path, symbolTable);
	currentToken = nullptr;
}

void Parser::nextToken() {
	if (currentToken) {
		delete currentToken;
	}
	while((currentToken = scanner->nextToken()) && currentToken->tokenType == TokenSeparator) {
		delete currentToken;
	}
}

void Parser::parse() {
	nextToken();
	declarations();
	statements();
}

void Parser::declarations() {

}

void Parser::declaration() {

}

void Parser::array() {

}

void Parser::statements() {

}

void Parser::statement() {

}

void Parser::exp() {

}

void Parser::exp2() {

}

void Parser::index() {

}

void Parser::op_exp() {

}

void Parser::op() {

}


Parser::~Parser() {
	delete symbolTable;
	delete scanner;
}
