#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "String.h"
#include "SymbolTable.h"
#include "TokenType.h"

int main()
{
	SymbolTable* symbolTable = new SymbolTable();

	symbolTable->create(String("while"), TokenKeyWordWhile);
//	symbolTable->create(String("WHILE"));
	symbolTable->create(String("if"), TokenKeyWordIf);
//	symbolTable->create(String("IF"));
	symbolTable->create(String("int"), TokenKeyWordInt);
	symbolTable->create(String("read"), TokenKeyWordRead);
	symbolTable->create(String("write"), TokenKeyWordWrite);

	std::cout<<tokenToString(symbolTable->getSymbolOf(String("int"))->tokenType)<<std::endl;

  return 0;
}
