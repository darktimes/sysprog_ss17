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
	std::ofstream outputStream;
	String outputFileName = String("output-") + String(argv[1]);
	remove(outputFileName.getStr());
	outputStream.open(outputFileName.getStr());
	while (scanner->nextToken()) {
		String lexem = (scanner->currentToken->lexem->getSize() <= 2) ? String(wrapChar(*scanner->currentToken->lexem[0])) : *scanner->currentToken->lexem;
		outputStream<<"TokenType: "<<tokenToString(scanner->currentToken->tokenType)<<", lexem: ";
		outputStream<<lexem;
		outputStream<<", line: "<<scanner->currentToken->tokenInfo->line<<", pos: "<<scanner->currentToken->tokenInfo->pos<<std::endl;

	}
	outputStream.close();


}

