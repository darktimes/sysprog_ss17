#include "Scanner.h"
#include "SymbolTable.h"
#include <iostream>

String formatTokenOutput(Token* token) {
	if (token->tokenType == TokenIdentifier) {
		return String("Lexem: ") + *(static_cast<LexemToken*>(token))->lexem;
	} else if (token->tokenType == TokenInteger) {
		return String("Value: ") + String((static_cast<IntegerToken*>(token))->value);
	} else if (token->tokenType == TokenUnknown) {
		return String("Char: ") + (static_cast<UnknownToken*>(token))->character;
	} else if (ErrorToken* err_token = dynamic_cast<ErrorToken*>(token)){
		return String("Error: ") + String(*err_token->err_msg);
	} else {
		return String();
	}
}

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
	Token* currentToken;
	while ((currentToken = scanner->nextToken())) {
		String str = tokenToString(currentToken->tokenType);
		outputStream<<"Token "<<tokenToString(currentToken->tokenType)<<'\t';
		if (str.getSize() < 11) {
			outputStream<<'\t';
		}
		outputStream<<"Line: "<<currentToken->tokenInfo->line<<'\t'<<'\t'<<"Column: "<<currentToken->tokenInfo->col<<'\t'<<'\t';
		outputStream<<formatTokenOutput(currentToken)<<std::endl;
//		String lexem = (scanner->currentToken->lexem->getSize() <= 2) ? String(wrapChar(*scanner->currentToken->lexem[0])) : *scanner->currentToken->lexem;
//		outputStream<<"TokenType:"<<tokenToString(scanner->currentToken->tokenType)<<", "<<'\t'<<'\t'<<'\t'<<"lexem: ";
//		outputStream<<lexem;
//		outputStream<<'\t'<<'\t'<<"line:"<<scanner->currentToken->tokenInfo->line<<", "<<'\t'<< "pos:"<<'\t'<<scanner->currentToken->tokenInfo->pos<<std::endl;

	}
	outputStream.close();


}

