#include "Scanner.h"
#include "SymbolTable.h"
#include <iostream>

String formatTokenOutput(Token* token) {
	if (token->tokenType == TokenIdentifier) {
		return String("Lexem: ") + *(static_cast<LexemToken*>(token))->lexem;
	} else if (ErrorToken* err_token = dynamic_cast<ErrorToken*>(token)){
		return String("Error: ") + String(*err_token->err_msg);
	} else if (token->tokenType == TokenInteger) {
		return String("Value: ") + String((static_cast<IntegerToken*>(token))->value);
	} else if (token->tokenType == TokenUnknown) {
		return String("Char: ") + (static_cast<UnknownToken*>(token))->character;
	} else {
		return String();
	}
}

int main(int argc, char **argv) {

	if (argc != 2) {
		std::cout<<"No file to test provided. Exiting..."<<std::endl;
		return -1;
	}
	std::cout<<"Processing..."<<std::endl;
	SymbolTable* symTable = new SymbolTable();
	symTable->create(String("while"), TokenKeyWordWhile);
	symTable->create(String("WHILE"), TokenKeyWordWhile);
	symTable->create(String("if"), TokenKeyWordIf);
	symTable->create(String("IF"), TokenKeyWordIf);
	Scanner* scanner = new Scanner(argv[1], symTable);
	std::ofstream outputStream;
	String outputFileName = String("output-") + String(argv[1]);
	remove(outputFileName.getStr());
	outputStream.open(outputFileName.getStr());
	Token* currentToken;
	while ((currentToken = scanner->nextToken())) {
		String str = tokenToString(currentToken->tokenType);


		if (ErrorToken* err_token = dynamic_cast<ErrorToken*>(currentToken))  {
			fprintf(stderr, "Token %s, line: %d, column: %d, error: %s \n",
					tokenToString(err_token->tokenType),
					err_token->tokenInfo->line, err_token->tokenInfo->col,
					(dynamic_cast<ErrorToken*>(err_token)->err_msg->getStr()));

		} else if (currentToken->tokenType == TokenUnknown) {
			fprintf(stderr, "Token %s, line: %d, column: %d, char: %c \n",
								tokenToString(currentToken->tokenType),
								currentToken->tokenInfo->line, currentToken->tokenInfo->col,
								(static_cast<UnknownToken*>(currentToken))->character);
		}
		outputStream<<"Token "<<tokenToString(currentToken->tokenType)<<'\t';
		if (str.getSize() < 11) {
			outputStream<<'\t';
		}
		outputStream<<"Line: "<<currentToken->tokenInfo->line<<'\t'<<'\t'<<"Column: "<<currentToken->tokenInfo->col<<'\t'<<'\t';
		outputStream<<formatTokenOutput(currentToken)<<std::endl;
	}
	outputStream.close();
	std::cout<<"Stop."<<std::endl;


}

