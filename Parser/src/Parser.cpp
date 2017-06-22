#include "Parser.h"
#include "Set.h"

Parser::Parser(const char* file_path) {
	symbolTable = new SymbolTable();
//	symbolTable->create(String("while"));
//	symbolTable->create(String("WHILE"));
//	symbolTable->create(String("if"));
//	symbolTable->create(String("IF"));
//	symbolTable->create(String("int"));
//	symbolTable->create(String("read("));
//	symbolTable->create(String("write("));
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

}

Parser::~Parser() {
	delete symbolTable;
	delete scanner;
}

ParseVisitor::ParseVisitor() {

}

void ParseVisitor::parseNode(Node* node) {

}

int main(int argc, char** args) {

	return 0;
}
