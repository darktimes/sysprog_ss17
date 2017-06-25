#include "Parser.h"
#include "Set.h"
#include "TokenType.h"


Parser::Parser(const char* file_path): symbolTable(SymbolTable()),scanner(Scanner(file_path, &symbolTable)),
	parseVisitor(ParseVisitor(this)), root(new Node(NodeProg)) {
//	symbolTable = SymbolTable();
//	scanner = Scanner(file_path, &symbolTable);
//	parseVisitor = ParseVisitor(this);
//	root = Node(NodeProg);

	symbolTable.create(String("while"), TokenKeyWordWhile);
	//	symbolTable->create(String("WHILE"));
	symbolTable.create(String("if"), TokenKeyWordIf);
	symbolTable.create(String("else"), TokenKeyWordElse);
//	symbolTable->create(String("IF"));
	symbolTable.create(String("int"), TokenKeyWordInt);
	symbolTable.create(String("read"), TokenKeyWordRead);
	symbolTable.create(String("write"), TokenKeyWordWrite);
}

bool Parser::isFinished() const{
	return scanner.isFinished();
}

Token* Parser::nextToken() {
	Token* result;
	result = scanner.nextToken();
	while(result && (result->tokenType==TokenSeparator || result->tokenType == TokenEOF || result->tokenType == TokenComment)) {
		delete result;
		result = scanner.nextToken();
	}

	return result;
}

void Parser::parse() {
	parseVisitor.nextToken();
	parseVisitor.parseNode(root);
}

void Parser::typeCheck() {
	parseVisitor.checkNode(root);
//	if (root->type == NotInited) {<
//		std::cout<<"Have to parse syntax tree first. Ignoring..."<<std::endl;
//	} else {
//
//	}
}

Parser::~Parser() {
	delete root;
}

bool Parser::isErrored() const{
	return parseVisitor.isErrored();
}

ParseVisitor::ParseVisitor(ITokenGenerator* tokenGenerator): tokenGenerator(tokenGenerator) {
	currentToken = nullptr;
	errored = false;
}
int v = 0;

void ParseVisitor::nextToken() {

	this->currentToken = tokenGenerator->nextToken();

	if (currentToken) {
		if (currentToken->tokenType == TokenUnknown) {
			printParseError(String("Unknown token"));
		} else if (ErrorToken* err_token = dynamic_cast<ErrorToken*>(currentToken)) {
			std::cout<<"Error parsing token: "<<err_token->err_msg<<std::endl;
			errored = true;
		}
//		for (int i = 0; i <v; i++) {
//			std::cout<<"   ";
//		}
//		std::cout<<"current token: "<<tokenToString(currentToken->tokenType)<<std::endl;
	} else {
//		for (int i = 0; i <v; i++) {
//					std::cout<<"   ";
//				}
//		std::cout<<"current token: empty"<<std::endl;
	}

}

bool tokenMatches(Token* token, TokenType type) {
	return ((token) && token->tokenType == type);
}


void ParseVisitor::parseNode(Node* node) {
//
////	for (int e = 0; e < v; e ++){
////		std::cout<<"   ";
////	}
////	v++;
////	std::cout<<nodeToString(node->getNodeType())<<std::endl;

	if (node->getNodeType() == NodeProg) {

		if (Set::FirstProg->contains(currentToken)) {
			Node* declsChild = new Node(NodeDecls);
			declsChild->parse(this);
			node->addChild(declsChild);

			Node* statementsChild = new Node(NodeStatements);
			statementsChild->parse(this);
			node->addChild(statementsChild);
		} else {
			printParseError(String("Unexpected token in PROG"));
		}

	} else if (node->getNodeType() == NodeDecls) {

		if (Set::FirstDecl->contains(currentToken)) {
			Node* declChild = new Node(NodeDecl);
			declChild->parse(this);
			node->addChild(declChild);

			if (tokenMatches(currentToken, TokenSemicolon)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				Node* declsNode = new Node(NodeDecls);
				declsNode->parse(this);
				node->addChild(declsNode);

			} else {
				printParseError(String("Expected ';'"));
			}

		} else if (!Set::FollowDecls->contains(currentToken)) {
			std::cout<<Set::FollowDecls->getSize()<<std::endl;
			for (unsigned i = 0; i < Set::FollowDecls->getSize(); i++) {
				std::cout<<tokenToString(Set::FollowDecls->get(i))<<std::endl;
			}
			printParseError(String("Unexpected token in DECLS"));
		}

	} else if (node->getNodeType() == NodeDecl){

		if (Set::FirstDecl->contains(currentToken)) {
			if (tokenMatches(currentToken,  TokenKeyWordInt)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				Node* arrayNode = new Node(NodeArray);
				arrayNode->parse(this);
				node->addChild(arrayNode);


				if (tokenMatches(currentToken,  TokenIdentifier)) {
					node->addLeaf(new Leaf(currentToken));
					nextToken();

				} else {
					printParseError(String("Expected identifier"));
				}
			} else {
				printParseError(String("Expected int"));
			}
		}

	} else if (node->getNodeType() == NodeArray) {

		if (Set::FirstArray->contains(currentToken)) {
			if (tokenMatches(currentToken,  TokenBracketOpen3)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				if(tokenMatches(currentToken,  TokenInteger)) {
					node->addLeaf(new Leaf(currentToken));
					nextToken();

					if (tokenMatches(currentToken,  TokenBracketClose3)) {
						node->addLeaf(new Leaf(currentToken));
						nextToken();
					} else {
						printParseError("Expected ]");
					}
				} else {
					printParseError(String("Expected integer"));
				}
			} else {
				printParseError(String("Expected ["));
			}

		} else if(!Set::FollowArray->contains(currentToken)) {
			printParseError(String("Expected identifier"));
		}
	} else if (node->getNodeType() == NodeStatements) {
		if (Set::FirstStatement->contains(currentToken)) {
			Node* statementChild = new Node(NodeStatement);
			statementChild->parse(this);
			statementChild->addChild(statementChild);

			if (tokenMatches(currentToken,  TokenSemicolon)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				Node* statementsChild = new Node(NodeStatements);
				statementsChild->parse(this);
				node->addChild(statementsChild);
			} else {
				printParseError(String("Expected ';'"));
			}
		} else if (!Set::FollowStatements->contains(currentToken)) {
			printParseError(String("Unexpected token in STATEMENTS"));
		}
	} else if (node->getNodeType() == NodeStatement) {
		if (Set::FirstStatement->contains(currentToken)) {
			if (tokenMatches(currentToken,  TokenIdentifier)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				Node* indexChild = new Node(NodeIndex);
				indexChild->parse(this);
				node->addChild(indexChild);

				if (tokenMatches(currentToken,  TokenEquals2)) {
					node->addLeaf(new Leaf(currentToken));
					nextToken();

					Node* expChild = new Node(NodeExp);
					expChild->parse(this);
					node->addChild(expChild);
				} else {
					printParseError(String("Expected ':='"));
				}
			} else if (tokenMatches(currentToken,  TokenKeyWordWrite)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				if (tokenMatches(currentToken,  TokenBracketOpen1)) {
					node->addLeaf(new Leaf(currentToken));
					nextToken();

					Node* expChild = new Node(NodeExp);
					expChild->parse(this);
					node->addChild(expChild);

					if (tokenMatches(currentToken,  TokenBracketClose1)) {
						node->addLeaf(new Leaf(currentToken));
						nextToken();
					} else {
						printParseError(String("Expected ')'"));
					}
				} else {
					printParseError(String("Expected '('"));
				}
			} else if (tokenMatches(currentToken,  TokenKeyWordRead)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				if (tokenMatches(currentToken,  TokenBracketOpen1)) {
					node->addLeaf(new Leaf(currentToken));
					nextToken();

					if (tokenMatches(currentToken,  TokenIdentifier)) {
						node->addLeaf(new Leaf(currentToken));
						nextToken();

						Node* indexChild = new Node(NodeIndex);
						indexChild->parse(this);
						node->addChild(indexChild);

						if (tokenMatches(currentToken,  TokenBracketClose1)) {
							node->addLeaf(new Leaf(currentToken));
							nextToken();
						} else {
							printParseError(String("Expected ')'"));
						}
					} else {
						printParseError(String("Expected identifier"));
					}
				} else {
					printParseError(String("Expected '('"));
				}
			} else if (tokenMatches(currentToken,  TokenBracketOpen2)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				Node* statementsNode = new Node(NodeStatements);
				statementsNode->parse(this);
				node->addChild(statementsNode);

				if (tokenMatches(currentToken,  TokenBracketClose2)) {
					node->addLeaf(new Leaf(currentToken));
					nextToken();
				} else {
					printParseError("Expected '}'");
				}
			} else if (tokenMatches(currentToken,  TokenKeyWordIf)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				if (tokenMatches(currentToken,  TokenBracketOpen1)) {
					node->addLeaf(new Leaf(currentToken));
					nextToken();

					Node* expNode = new Node(NodeExp);
					expNode->parse(this);
					node->addChild(expNode);

					if (tokenMatches(currentToken,  TokenBracketClose1)) {
						node->addLeaf(new Leaf(currentToken));
						nextToken();

						Node* statementChild = new Node(NodeStatement);
						statementChild->parse(this);
						node->addChild(statementChild);

						if (tokenMatches(currentToken,  TokenKeyWordElse)) {
							node->addLeaf(new Leaf(currentToken));
							nextToken();

							Node* statement2Child = new Node(NodeStatement);
							statement2Child->parse(this);
							node->addChild(statement2Child);
						} else {
							printParseError(String("Expected 'else'"));
						}
					} else {
						printParseError(String("Expected ')'"));
					}
				} else {
					printParseError(String("Expected '('"));
				}
			} else if (tokenMatches(currentToken,  TokenKeyWordWhile)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				if (tokenMatches(currentToken,  TokenBracketOpen1)) {
					node->addLeaf(new Leaf(currentToken));
					nextToken();

					Node* expChild = new Node(NodeExp);
					expChild->parse(this);
					node->addChild(expChild);

					if (tokenMatches(currentToken,  TokenBracketClose1)) {
						node->addLeaf(new Leaf(currentToken));
						nextToken();

						Node* statementChild = new Node(NodeStatement);
						statementChild->parse(this);
						node->addChild(statementChild);
					} else {
						printParseError(String("Expected ')'"));
					}
				} else {
					printParseError(String("Expected '('"));
				}
			} else {
				printParseError(String("Unexpected token in STATEMENT (while)"));
			}
		} else {
			printParseError(String("Unexpected token in STATEMENT"));
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
			printParseError(String("Unexpected token in EXP"));
		}
	} else if (node->getNodeType() == NodeExp2) {
		if (Set::FirstExp2->contains(currentToken)) {
			if (tokenMatches(currentToken,  TokenBracketOpen1)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				Node* expChild = new Node(NodeExp);
				expChild->parse(this);
				node->addChild(expChild);

				if (tokenMatches(currentToken,  TokenBracketClose1)) {
					node->addLeaf(new Leaf(currentToken));
					nextToken();
				} else {
					printParseError(String("Expected ')'"));
				}
			} else if (tokenMatches(currentToken,  TokenIdentifier)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				Node* indexChild = new Node(NodeIndex);
				indexChild->parse(this);
				node->addChild(indexChild);
			} else if (tokenMatches(currentToken,  TokenInteger)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();
			} else if (tokenMatches(currentToken,  TokenMinus) || tokenMatches(currentToken,  TokenExclamation )) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();

				Node* exp2Child = new Node(NodeExp2);
				exp2Child->parse(this);
				node->addChild(exp2Child);
			} else {
				printParseError(String("Unexpected token in EXP2"));
			}
		} else {
			printParseError(String("Unexpected token in EXP2"));
		}
	} else if (node->getNodeType() == NodeIndex) {
		if (tokenMatches(currentToken,  TokenBracketOpen3)) {
			node->addLeaf(new Leaf(currentToken));
			nextToken();

			Node* expChild = new Node(NodeExp);
			expChild->parse(this);
			node->addChild(expChild);

			if (tokenMatches(currentToken,  TokenBracketClose3)) {
				node->addLeaf(new Leaf(currentToken));
				nextToken();
			} else {
				printParseError(String("Expected ']'"));
			}
		} else if (!Set::FollowIndex->contains(currentToken)) {
			printParseError(String("Unexpected token in INDEX"));
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
			printParseError(String("Unexpected token in OP_EXP"));
		}
	} else if (node->getNodeType() == NodeOp) {
		if (Set::FirstOp->contains(currentToken)) {
			node->addLeaf(new Leaf(currentToken));
			nextToken();
		} else {
			printParseError(String("Unexpected token in OP"));
		}
	}

}

void ParseVisitor::checkNode(Node* node) {
	std::cout<<"Checking..."<<nodeToString(node->getNodeType())<<std::endl;
	if (node->getNodeType() == NodeProg) {
		node->type = NoType;
		for (unsigned i = 0; i < node->getChildren()->getLength(); i++) {
			Node* current = node->getChildren()->at(i);
			current->checkType(this);
		}
	} else if (node->getNodeType() == NodeDecls) {
		node->type = NoType;
		for (unsigned i = 0; i < node->getChildren()->getLength(); i++) {
			Node* current = node->getChildren()->at(i);
			current->checkType(this);
		}
	} else if (node->getNodeType() == NodeDecl) {
		Node* arrayNode = node->getChildren()->at(0);
		arrayNode->checkType(this);
		Token* token = node->getLeafs()->at(1)->getToken();
		if (token->tokenInfo->checkType != NoType) {
			printParseError("Identifier already defined");
			node->type = ErrorType;
		} else if (arrayNode->type == ErrorType) {
			node->type = ErrorType;
		} else {
			node->type = NoType;
			if (arrayNode->type == ArrayType) {
				token->tokenInfo->checkType = IntArrayType;
			} else {
				token->tokenInfo->checkType = IntType;
			}
		}
	} else if (node->getNodeType() == NodeArray) {

		if (node->getLeafs()->getLength() != 0) {

			Leaf* leaf = node->getLeafs()->at(1);

			Token* token = leaf->getToken();

			IntegerToken* a = dynamic_cast<IntegerToken*>(token);
			if (a) {
				std::cout<<"a"<<std::endl;
			} else {
				std::cout<<"b"<<std::endl;
			}

			if (static_cast<IntegerToken*>(leaf->getToken())->value > 0) {

				node->type = ArrayType;
			} else {
				printParseError("Invalid dimension");
				node->type = ErrorType;
			}
		} else {
			node->type = NoType;
		}
	} else if (node->getNodeType() == NodeStatements){
		node->type = NoType;
		for (unsigned i = 0; i < node->getChildren()->getLength(); i++) {
			node->getChildren()->at(i)->checkType(this);
		}
	} else if (node->getNodeType() == NodeStatement) {
		Leaf* firstLeaf = node->getLeafs()->at(0);
		Node* firstNode = node->getChildren()->at(0);
		if (firstLeaf->getToken()->tokenType == TokenIdentifier) {
			for (unsigned i = node->getChildren()->getLength() - 1; i <= 0; i--) {
				node->getChildren()->at(i)->checkType(this);
			}
			if (firstLeaf->getToken()->tokenInfo->checkType == NoType) {
				node->type = ErrorType;
				printParseError("Identifier not found");
			} else if (node->getChildren()->at(1)->type == IntType &&
					((firstLeaf->getToken()->tokenInfo->checkType == IntType && firstNode->type == NoType) ||
					(firstLeaf->getToken()->tokenInfo->checkType == IntArrayType && firstNode->type == ArrayType))) {
				node->type = NoType;
			} else {
				node->type = ErrorType;
				printParseError("Incompatible types");
			}
		} else if (firstLeaf->getToken()->tokenType == TokenKeyWordWrite) {
			firstNode->checkType(this);
			node->type = NoType;
		} else if (firstLeaf->getToken()->tokenType == TokenKeyWordRead) {
			node->getChildren()->at(1)->checkType(this);
			if (node->getLeafs()->at(2)->getToken()->tokenInfo->checkType == NoType) {
				printParseError("Identifier not found");
				node->type = ErrorType;
			} else if ((node->getLeafs()->at(2)->getToken()->tokenInfo->checkType == IntType && node->getChildren()->at(1)->type == NoType) ||
					(node->getLeafs()->at(2)->getToken()->tokenInfo->checkType == IntArrayType && node->getChildren()->at(1)->type == ArrayType)) {
				node->type = NoType;
			} else {
				printParseError("Incompatible types");
				node->type = ErrorType;
			}
		} else if (firstLeaf->getToken()->tokenType == TokenBracketOpen2) {
			node->type = NoType;
			node->getChildren()->at(0)->checkType(this);
		} else if (firstLeaf->getToken()->tokenType == TokenKeyWordIf) {
			for (unsigned i = 0; i < node->getChildren()->getLength(); i++) {
				node->getChildren()->at(i)->checkType(this);
			}
			if (node->getChildren()->at(0)->type == ErrorType) {
				node->type = ErrorType;
			} else {
				node->type = NoType;
			}
		} else if (firstLeaf->getToken()->tokenType == TokenKeyWordWhile) {
			for (unsigned i = 0; i < node->getChildren()->getLength(); i++) {
				node->getChildren()->at(i)->checkType(this);
			}
			if (node->getChildren()->at(0)->type == ErrorType) {
				node->type = ErrorType;
			} else {
				node->type = NoType;
			}
		}
	} else if (node->getNodeType() == NodeIndex) {
		if (node->getLeafs()->getLength() != 0) {
			node->getChildren()->at(0)->checkType(this);
			if (node->getChildren()->at(0)->type == ErrorType) {
				node->type = ErrorType;
			} else {
				node->type = NoType;
			}
		} else {
			node->type = NoType;
		}
	} else if (node->getNodeType() == NodeExp) {
		for (unsigned i = 0; i < node->getChildren()->getLength(); i++) {
			node->getChildren()->at(i)->checkType(this);
		}
		if (node->getChildren()->at(1)->type == NoType) {
			node->type = node->getChildren()->at(0)->type;
		} else if (node->getChildren()->at(1)->type != node->getChildren()->at(0)->type) {
			node->type = ErrorType;
		} else {
			node->type = node->getChildren()->at(1)->type;
		}
	} else if(node->getNodeType() == NodeExp2) {
		Node* firstChild = node->getChildren()->at(0);
		if (firstChild->getNodeType() == NodeExp) {
			firstChild->checkType(this);
			node->type = firstChild->type;
		} else if (firstChild->getNodeType() == NodeIndex) {
			firstChild->checkType(this);
			Token* token = node->getLeafs()->at(0)->getToken();
			if (token->tokenInfo->checkType == NoType) {
				printParseError("Identifier not found");
				node->type = ErrorType;
			} else if (token->tokenInfo->checkType == IntType && firstChild->type == NoType) {
				//TODO:: prolly, IntType
				node->type = token->tokenInfo->checkType;
			} else if (token->tokenInfo->checkType == IntArrayType && firstChild->type == ArrayType) {
				//TODO: prolly IntArrayType
				node->type = IntType;
			} else {
				node->type = ErrorType;
				printParseError("Not a primitive type");
			}
		} else if (dynamic_cast<IntegerToken*>(node->getLeafs()->at(0)->getToken())) {
			node->type = IntType;
		} else if (node->getLeafs()->at(0)->getToken()->tokenType == TokenMinus) {
			node->getChildren()->at(0)->checkType(this);
			node->type = node->getChildren()->at(0)->type;
		} else if (node->getLeafs()->at(0)->getToken()->tokenType == TokenExclamation) {
			node->getChildren()->at(0)->checkType(this);
			if (node->getChildren()->at(0)->type != IntType) {
				node->type = ErrorType;
			} else {
				node->type = IntType;
			}
		}
	} else if (node->getNodeType() == NodeOpExp) {
		if (node->getChildren()->getLength() != 0) {
			for (unsigned i = 0; i <= node->getChildren()->getLength(); i++) {
				node->getChildren()->at(i)->checkType(this);
			}
			node->type = node->getChildren()->at(1)->type;
		} else {
			node->type = NoType;
		}
	} else if (node->getNodeType() == NodeOp) {
			switch (node->getLeafs()->at(0)->getToken()->tokenType) {
			case TokenPlus: node->type = OpPlus; break;
			case TokenMinus: node->type = OpMinus; break;
			case TokenAsterisk: node->type = OpMult; break;
			case TokenColon: node->type = OpDiv; break;
			case TokenLessThan: node->type = OpLess; break;
			case TokenGreaterThan: node->type = OpGreater; break;
			case TokenAnd: node->type = OpAnd; break;
			case TokenEquals1: node->type = OpEqual; break;
			case TokenEquals3: node->type = OpUnequal; break;
			default: node->type = ErrorType;
		}
	}
	std::cout<<"Exiting..."<<nodeToString(node->getNodeType())<<std::endl;
}

bool ParseVisitor::isErrored() const {
	return errored;
}

void ParseVisitor::printTypeCheckError() {
	errored = true;
}

void ParseVisitor::printParseError(String msg) {
	errored = true;

	std::cout<<msg<<", token: "<<(currentToken? tokenToString(currentToken->tokenType): "undefined")<<" at: line - "<<currentToken->tokenInfo->line<<", column - "<<currentToken->tokenInfo->col<<std::endl;
}


int main(int argc, char **argv) {

	if (argc < 2) {
		std::cout<<"No file specified  to work with. Exiting..."<<std::endl;
		return -1;
	} else if (argc > 2) {
		std::cout<<"Warning. Too much arguments. Arguments after 2nd one will be ignored"<<std::endl;
	}

	Parser parser = Parser(argv[1]);
	if (parser.isFinished()) {
		std::cout<<"There was an error, opening file. Exiting..."<<std::endl;
		return -1;
	}
	std::cout<<"Parsing..."<<std::endl;
	parser.parse();
	if (parser.isErrored()) {
		std::cout<<"There were errors, while generating parse tree. Aborting..."<<std::endl;
	} else {
		std::cout<<"Checking types..."<<std::endl;



		parser.typeCheck();
		if (parser.isErrored()) {
			std::cout<<"There were errors, while evaluating types. Aborting..."<<std::endl;
		} else {
			std::cout<<"Making code"<<std::endl;
			//make code
		}
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

