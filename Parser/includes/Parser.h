
#pragma once

#include "Scanner.h"
#include "SymbolTable.h"
#include "TreeEntities.h"
#include "Set.h"
#include "Tokens.h"

class Node;

//class ParseVisitor;


class ITokenGenerator {
	public:
		virtual Token* nextToken() = 0;
		virtual std::ofstream& getStream() = 0;
		virtual ~ITokenGenerator() {};
};

class ParseVisitor {

	public:
		ParseVisitor(ITokenGenerator* tokenGenerator);
		virtual ~ParseVisitor() {}
		void parseNode(Node* node);
		void checkNode(Node* node);
		void makeNode(Node* node);
		bool isErrored() const;
		void nextToken();
		void printParseError(String msg);
		void printTypeCheckError(String msg, Token* token = nullptr);

	private:
		ITokenGenerator* tokenGenerator;
		Token* currentToken;
		bool errored;
};



class Parser: ITokenGenerator{

	public:
		Parser(const char* file_path);
		virtual ~Parser();
		void parse();
		void typeCheck();
		void makeCode();
		bool isFinished() const;
		Token* nextToken() override;
		std::ofstream& getStream() override;
		bool isErrored() const;

	private:
		SymbolTable symbolTable;
		Scanner scanner;
		ParseVisitor parseVisitor;

		String outputFileName;
		std::ofstream* outputStream;

	public:
		Node* root;
};

