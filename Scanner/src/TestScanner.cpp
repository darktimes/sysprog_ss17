#include "Scanner.h"
#include "SymbolTable.h"
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout<<"No file to test provided. Exiting..."<<std::endl;
		return -1;
	}

	SymbolTable* symTable = new SymbolTable();
	Scanner* scanner = new Scanner(argv[1], symTable);

	while (scanner->nextToken()) {
		String lexem = (scanner->currentToken->lexem->getSize() <= 2) ? String(wrapChar(*scanner->currentToken->lexem[0])) : *scanner->currentToken->lexem;
		std::cout<<"TokenType: "<<tokenToString(scanner->currentToken->tokenType)<<", lexem: ";
		std::cout<<lexem;
		std::cout<<", line: "<<scanner->currentToken->tokenInfo->line<<", pos: "<<scanner->currentToken->tokenInfo->pos<<std::endl;
	}
}

