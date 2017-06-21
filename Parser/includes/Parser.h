#pragma once

#include "Scanner.h"
#include "SymbolTable.h"

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

		void declarations();
		void declaration();
		void array();

		void statements();
		void statement();
		void exp();
		void exp2();
		void index();
		void op_exp();
		void op();

};
