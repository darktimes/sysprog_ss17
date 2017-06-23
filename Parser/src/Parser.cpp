#include "Parser.h"
#include "Set.h"


Parser::Parser(const char* file_path) {
	symbolTable = new SymbolTable();
	symbolTable->create(String("while"), TokenKeyWordWhile);
//	symbolTable->create(String("WHILE"));
	symbolTable->create(String("if"), TokenKeyWordIf);
//	symbolTable->create(String("IF"));
	symbolTable->create(String("int"), TokenKeyWordInt);
	symbolTable->create(String("read"), TokenKeyWordRead);
	symbolTable->create(String("write"), TokenKeyWordWrite);

	scanner = new Scanner(file_path, symbolTable);
	parseVisitor = new ParseVisitor(this);
}

Token* Parser::nextToken() {
	Token* result;
	result = scanner->nextToken();
	while(result && (result->tokenType==TokenSeparator || result->tokenType == TokenEOF)) {
		delete result;
		result = scanner->nextToken();
	}

	return result;
}

Node* Parser::parse() {
	parseVisitor->nextToken();

	Node* root = new Node(NodeProg);
	parseVisitor->parseNode(root);
	return root;
}

Parser::~Parser() {
	delete symbolTable;
	delete scanner;
	delete parseVisitor;
}

bool Parser::isErrored() const{
	return parseVisitor->isErrored();
}

ParseVisitor::ParseVisitor(ITokenGenerator* tokenGenerator): tokenGenerator(tokenGenerator) {
	currentToken = nullptr;
	errored = false;
}

void ParseVisitor::nextToken() {

	this->currentToken = tokenGenerator->nextToken();

	if (currentToken) {
		if (currentToken->tokenType == TokenUnknown) {
			printError(String("Unknown token"));
		} else if (ErrorToken* err_token = dynamic_cast<ErrorToken*>(currentToken)) {
			std::cout<<"Error parsing token: "<<err_token->err_msg<<std::endl;
			errored = true;
		}
//		std::cout<<"current token: "<<tokenToString(currentToken->tokenType)<<std::endl;
	} else {
//		std::cout<<"current token: empty"<<std::endl;
	}

}

void ParseVisitor::parseNode(Node* node) {
	if (node->getNodeType() == NodeProg) {

		if (Set::FirstProg->contains(currentToken)) {
			Node* declsChild = new Node(NodeDecls);
			declsChild->parse(this);
			node->addChild(declsChild);

			Node* statementsChild = new Node(NodeStatements);
			statementsChild->parse(this);
			node->addChild(statementsChild);
		} else {
			printError(String("Unexpected token PROG"));
		}

	} else if (node->getNodeType() == NodeDecls) {

		if (Set::FirstDecl->contains(currentToken)) {
			Node* declChild = new Node(NodeDecl);
			declChild->parse(this);
			node->addChild(declChild);

			if (currentToken->tokenType == TokenSemicolon) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				Node* declsNode = new Node(NodeDecls);
				declsNode->parse(this);
				node->addChild(declsNode);

			} else {
				printError(String("Expected ';'"));
			}

		} else if (!Set::FollowDecls->contains(currentToken)) {
			std::cout<<Set::FollowDecls->getSize()<<std::endl;
			for (unsigned i = 0; i < Set::FollowDecls->getSize(); i++) {
				std::cout<<tokenToString(Set::FollowDecls->get(i))<<std::endl;
			}
			printError(String("Unexpected token DECLS"));
		}

	} else if (node->getNodeType() == NodeDecl){

		if (Set::FirstDecl->contains(currentToken)) {
			if (currentToken->tokenType == TokenKeyWordInt) {
				node->addChild(new Leaf(*currentToken));
				nextToken();


				Node* arrayNode = new Node(NodeArray);
				arrayNode->parse(this);
				node->addChild(arrayNode);

				if (currentToken->tokenType == TokenIdentifier) {
					node->addChild(new Leaf(*currentToken));
					nextToken();
				} else {
					printError(String("Expected identifier"));
				}
			} else {
				printError(String("Expected int"));
			}
		}

	} else if (node->getNodeType() == NodeArray) {

		if (Set::FirstArray->contains(currentToken)) {
			if (currentToken->tokenType == TokenBracketOpen3) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				if(currentToken->tokenType == TokenInteger) {
					node->addChild(new Leaf(*currentToken));
					nextToken();

					if (currentToken->tokenType == TokenBracketClose3) {
						node->addChild(new Leaf(*currentToken));
						nextToken();
					} else {
						printError("Expected ]");
					}
				} else {
					printError(String("Expected integer"));
				}
			} else {
				printError(String("Expected ["));
			}

		} else if(!Set::FollowArray->contains(currentToken)) {
			printError(String("Expected identifier"));
		}
	} else if (node->getNodeType() == NodeStatements) {
		if (Set::FirstStatement->contains(currentToken)) {
			Node* statementChild = new Node(NodeStatement);
			statementChild->parse(this);
			statementChild->addChild(statementChild);

			if (currentToken->tokenType == TokenSemicolon) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				Node* statementsChild = new Node(NodeStatements);
				statementsChild->parse(this);
				node->addChild(statementsChild);
			}
		} else if (!Set::FollowStatements->contains(currentToken)) {
			printError(String("Unexpected token STATEMENTS"));
		}
	} else if (node->getNodeType() == NodeStatement) {
		if (Set::FirstStatement->contains(currentToken)) {
			if (currentToken->tokenType == TokenIdentifier) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				Node* indexChild = new Node(NodeIndex);
				indexChild->parse(this);
				node->addChild(indexChild);

				if (currentToken->tokenType == TokenEquals2) {
					node->addChild(new Leaf(*currentToken));
					nextToken();

					Node* expChild = new Node(NodeExp);
					expChild->parse(this);
					node->addChild(expChild);
				} else {
					printError(String("Expected ':='"));
				}
			} else if (currentToken->tokenType == TokenKeyWordWrite) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				if (currentToken->tokenType == TokenBracketOpen1) {
					node->addChild(new Leaf(*currentToken));
					nextToken();

					Node* expChild = new Node(NodeExp);
					expChild->parse(this);
					node->addChild(expChild);

					if (currentToken->tokenType == TokenBracketClose1) {
						node->addChild(new Leaf(*currentToken));
						nextToken();
					} else {
						printError(String("Expected ')'"));
					}
				} else {
					printError(String("Expected '('"));
				}
			} else if (currentToken->tokenType == TokenKeyWordRead) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				if (currentToken->tokenType == TokenBracketOpen1) {
					node->addChild(new Leaf(*currentToken));
					nextToken();

					if (currentToken->tokenType == TokenIdentifier) {
						node->addChild(new Leaf(*currentToken));
						nextToken();

						Node* indexChild = new Node(NodeIndex);
						indexChild->parse(this);
						node->addChild(indexChild);

						if (currentToken->tokenType == TokenBracketClose1) {
							node->addChild(new Leaf(*currentToken));
							nextToken();
						} else {
							printError(String("Expected ')'"));
						}
					} else {
						printError(String("Expected identifier"));
					}
				} else {
					printError(String("Expected '('"));
				}
			} else if (currentToken->tokenType == TokenBracketOpen2) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				Node* statementsNode = new Node(NodeStatements);
				statementsNode->parse(this);
				node->addChild(statementsNode);

				if (currentToken->tokenType == TokenBracketClose2) {
					node->addChild(new Leaf(*currentToken));
					nextToken();
				} else {
					printError("Expected '}'");
				}
			} else if (currentToken->tokenType == TokenKeyWordIf) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				if (currentToken->tokenType == TokenBracketOpen1) {
					node->addChild(new Leaf(*currentToken));
					nextToken();

					Node* expNode = new Node(NodeExp);
					expNode->parse(this);
					node->addChild(expNode);

					if (currentToken->tokenType == TokenBracketClose1) {
						node->addChild(new Leaf(*currentToken));
						nextToken();

						Node* statementChild = new Node(NodeStatement);
						statementChild->parse(this);
						node->addChild(statementChild);

						if (currentToken->tokenType == TokenKeyWordElse) {
							node->addChild(new Leaf(*currentToken));
							nextToken();

							Node* statement2Child = new Node(NodeStatement);
							statement2Child->parse(this);
							node->addChild(statement2Child);
						} else {
							printError(String("Expected 'else'"));
						}
					} else {
						printError(String("Expected ')'"));
					}
				} else {
					printError(String("Expected '('"));
				}
			} else if (currentToken->tokenType == TokenKeyWordWhile) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				if (currentToken->tokenType == TokenBracketOpen1) {
					node->addChild(new Leaf(*currentToken));
					nextToken();

					Node* expChild = new Node(NodeExp);
					expChild->parse(this);
					node->addChild(expChild);

					if (currentToken->tokenType == TokenBracketClose1) {
						node->addChild(new Leaf(*currentToken));
						nextToken();

						Node* statementChild = new Node(NodeStatement);
						statementChild->parse(this);
						node->addChild(statementChild);
					} else {
						printError("Expected ')'");
					}
				} else {
					printError("Expected '('");
				}
			} else {
				printError("Unexpected token STATEMENT (while)");
			}
		} else {
			printError(String("Unexpected token STATEMENT"));
		}
	} else if (node->getNodeType() == NodeExp) {
		if (Set::FirstExp2->contains(currentToken)) {
			Node* exp2child = new Node(NodeExp2);
			exp2child->parse(this);
			node->addChild(exp2child);

			Node* opExpChild = new Node(NodeOpExp);
			opExpChild->parse(this);
			node->addChild(opExpChild);
		} else {
			printError(String("Unexpected token EXP"));
		}
	} else if (node->getNodeType() == NodeExp2) {
		if (Set::FirstExp2->contains(currentToken)) {
			if (currentToken->tokenType == TokenBracketOpen1) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				Node* expChild = new Node(NodeExp);
				expChild->parse(this);
				node->addChild(expChild);

				if (currentToken->tokenType == TokenBracketClose1) {
					node->addChild(new Leaf(*currentToken));
					nextToken();
				} else {
					printError(String("Expected ')'"));
				}
			} else if (currentToken->tokenType == TokenIdentifier) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				Node* indexChild = new Node(NodeIndex);
				indexChild->parse(this);
				node->addChild(indexChild);
			} else if (currentToken->tokenType == TokenInteger) {
				node->addChild(new Leaf(*currentToken));
				nextToken();
			} else if (currentToken->tokenType == TokenMinus || currentToken->tokenType == TokenExclamation ) {
				node->addChild(new Leaf(*currentToken));
				nextToken();

				Node* exp2Child = new Node(NodeExp2);
				exp2Child->parse(this);
				node->addChild(exp2Child);
			} else {
				printError(String("Unexpected token EXP2"));
			}
		} else {
			printError(String("Unexpected token EXP2"));
		}
	} else if (node->getNodeType() == NodeIndex) {
		if (currentToken->tokenType == TokenBracketOpen3) {
			node->addChild(new Leaf(*currentToken));
			nextToken();

			Node* expChild = new Node(NodeExp);
			expChild->parse(this);
			node->addChild(expChild);

			if (currentToken->tokenType == TokenBracketClose3) {
				node->addChild(new Leaf(*currentToken));
				nextToken();
			} else {
				printError(String("Expected ']'"));
			}
		} else if (!Set::FollowIndex->contains(currentToken)) {
			printError(String("Unexpected token INDEX"));
		}
	} else if (node->getNodeType() == NodeOpExp) {
		if (Set::FirstOp->contains(currentToken)) {
			Node* opChild = new Node(NodeOp);
			opChild->parse(this);
			node->addChild(opChild);

			Node* expChild = new Node(NodeExp);
			expChild->parse(this);
			node->addChild(expChild);
		} else if (!Set::FollowOpExp->contains(currentToken)) {
			printError(String("Unexpected token OP_EXP"));
		}
	} else if (node->getNodeType() == NodeOp) {
		if (Set::FirstOp->contains(currentToken)) {
			node->addChild(new Leaf(*currentToken));
			nextToken();
		} else {
			printError(String("Unexpected token OP"));
		}
	}
}

bool ParseVisitor::isErrored() const {
	return errored;
}

void ParseVisitor::printError(String msg) {
	errored = true;
	std::cout<<msg<<", token: "<<tokenToString(currentToken->tokenType)<<" at: line - "<<currentToken->tokenInfo->line<<", column - "<<currentToken->tokenInfo->col<<std::endl;
}


int main(int argc, char **argv) {
	std::cout<<"-------------------------------------"<<std::endl;
	std::cout<<Set::FollowDecls->getSize()<<std::endl;
	std::cout<<"-------------------------------------"<<std::endl;

	if (argc < 2) {
		std::cout<<"No file specified  to work with. Exiting..."<<std::endl;
		return -1;
	} else if (argc > 2){
		std::cout<<"Warning. Too much arguments. Arguments after 2nd one will be ignored"<<std::endl;
	}

	Parser parser = Parser(argv[1]);
	std::cout<<"Parsing"<<std::endl;
	/*Node* rootNode = */parser.parse();
	if (parser.isErrored()) {
		std::cout<<"Errors obtained, while generating parse tree. Aborting..."<<std::endl;
	}

	return 0;
}



/*scheme:

 	FIRST
	PROG:
		t -> FIRST(PROG)+e merged with FOLLOW(PROG) ok? // FIRST (DECLS) && FIRST (STATEMENTS)
			DECLS
			STATEMENTS
		!ok
			error
	DECLS:
		t -> FIRST (DECL) ok?
			DECL
			;
			DECLS
		!ok t -> FOLLOW (DECLS) -> wokring with e, ok?
			ok, skip
		!ok
			error

	DECL:
		t-> FIRST(DECL) ok?
			int
			ARRAY
			identifier
		!ok
			error
	ARRAY:
		t-> FIRST(ARRAY) ok?
			[
			integer
			]
		!ok t-> FOLLOW(ARRAY) ok?
			ok, skip
		!ok
			error

	STATEMENTS:
		t -> FIRST (STATEMENT) ok?
			t-> identifier? ok?
				identifier
				INDEX
				:=
				EXP
			!ok t -> write ok?
				write
				(
				EXP
				)
			!ok t-> read ok?
				read
				(
				identifier
				INDEX
				)
			!ok t-> { ok?
				{
				STATEMENTS
				}
			!ok t -> if ok?
				if
				(
				EXP
				)
				STATEMENT
				else
				STATEMENT
			!ok t ->while ok?
				while
				(
				EXP
				)
				STATEMENT
			!ok
				error
		!ok t -> FOLLOW (STATEMENTS) ok?
			ok, skip
		!ok
			error

	EXP:
		t -> FIRST (EXP2) ok?
			EXP2
			OP_EXP
		!ok
			error
	EXP2:
		t -> ( ok?
			(
			EXP
			)
		!ok t -> identifier ok?
			identifier
			INDEX
		!ok t -> integer ok?
			integer
		!ok t -> - ok?
			EXP2
		!ok t -> ! ok?
			EXP2
		!ok
			error
	INDEX:
		t -> [ ok?
			[
			EXP
			]
		t -> FOLLOW(INDEX) ok?
			ok, skip
		!ok
			error
	OP_EXP:
		t -> FIRST(OP) ok?
			OP
			EXP
		!ok t -> FOLLOW(OP_EXP) ok?
			ok, skip
		!ok
			error
	OP:
		t -> FIRST(OP) ok?
			ok
		!ok
			error


*/

