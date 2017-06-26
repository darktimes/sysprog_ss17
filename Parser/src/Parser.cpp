#include "Parser.h"
#include "Set.h"
#include "TokenType.h"

bool DEBUG;

Parser::Parser(const char* file_path): symbolTable(SymbolTable()),scanner(Scanner(file_path, &symbolTable)),
	parseVisitor(ParseVisitor(this)), outputFileName(String("output-") + String(file_path)),
	outputStream(new std::ofstream), root(new Node(NodeProg)) {
//	symbolTable = SymbolTable();
//	scanner = Scanner(file_path, &symbolTable);
//	parseVisitor = ParseVisitor(this);
//	root = Node(NodeProg);

	symbolTable.create(String("while"), TokenKeyWordWhile);
	symbolTable.create(String("WHILE"), TokenKeyWordWhile);
	symbolTable.create(String("if"), TokenKeyWordIf);
	symbolTable.create(String("IF"), TokenKeyWordIf);
	symbolTable.create(String("else"), TokenKeyWordElse);
	symbolTable.create(String("ELSE"), TokenKeyWordElse);
//	symbolTable->create(String("IF"));
	symbolTable.create(String("int"), TokenKeyWordInt);
	symbolTable.create(String("INT"), TokenKeyWordInt);
	symbolTable.create(String("read"), TokenKeyWordRead);
	symbolTable.create(String("READ"), TokenKeyWordRead);
	symbolTable.create(String("write"), TokenKeyWordWrite);
	symbolTable.create(String("WRITE"), TokenKeyWordWrite);


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

std::ofstream& Parser::getStream() {
	return *outputStream;
}

void Parser::makeCode() {
	remove(outputFileName.getStr());
	outputStream->open(outputFileName.getStr());
	parseVisitor.makeNode(root);
	outputStream->close();
}

Parser::~Parser() {

	delete root;
	delete outputStream;

}

bool Parser::isErrored() const{
	return parseVisitor.isErrored();
}

ParseVisitor::ParseVisitor(ITokenGenerator* tokenGenerator): tokenGenerator(tokenGenerator) {
	currentToken = nullptr;
	errored = false;
}

int v = 0;
int labelCount = 1;

String generateLabel() {
	return String("label") + String(labelCount++);
}



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
	if (DEBUG) {
		for (int e = 0; e < v; e ++){
			std::cout<<"   ";
		}
		std::cout<<nodeToString(node->getNodeType())<<std::endl;
		v++;
	}


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
						printParseError(String("Expected ]"));
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
			node->addChild(statementChild);

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
					printParseError(String("Expected '}'"));
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

	if (DEBUG) {
		v--;
		for (int e = 0; e < v; e ++){
			std::cout<<"   ";
		}
		std::cout<<"\\"<<nodeToString(node->getNodeType())<<std::endl;
	}

}

void ParseVisitor::checkNode(Node* node) {
	if (DEBUG) {
		for (int e = 0; e < v; e ++){
			std::cout<<"   ";
		}
		std::cout<<nodeToString(node->getNodeType())<<std::endl;
		v++;
	}
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
		LexemToken* token = static_cast<LexemToken*>(node->getLeafs()->at(1)->getToken());
		if (token->symbolTableKeyReference->checkType != NoType) {
			printTypeCheckError(String("Identifier already defined"), token);
			node->type = ErrorType;
		} else if (arrayNode->type == ErrorType) {
			node->type = ErrorType;
		} else {
			node->type = NoType;
			if (arrayNode->type == ArrayType) {
				token->symbolTableKeyReference->checkType = IntArrayType;
			} else {
				token->symbolTableKeyReference->checkType = IntType;
			}
		}
	} else if (node->getNodeType() == NodeArray) {

		if (node->getLeafs()->getLength() != 0) {

			Leaf* leaf = node->getLeafs()->at(1);

			if (static_cast<IntegerToken*>(leaf->getToken())->value > 0) {

				node->type = ArrayType;
			} else {
				printTypeCheckError(String("Invalid dimension"), leaf->getToken());
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
			for (unsigned i = node->getChildren()->getLength(); i > 0; i--) {
				node->getChildren()->at(i - 1)->checkType(this);
			}
			LexemToken* lexemToken = static_cast<LexemToken*>(firstLeaf->getToken());
			if (lexemToken->symbolTableKeyReference->checkType == NoType) {
				node->type = ErrorType;
			} else if (node->getChildren()->at(1)->type == IntType &&
					((lexemToken->symbolTableKeyReference->checkType == IntType && firstNode->type == NoType) ||
					(lexemToken->symbolTableKeyReference->checkType == IntArrayType && firstNode->type == ArrayType))) {
				node->type = NoType;
			} else {
				node->type = ErrorType;
				printTypeCheckError(String("Incompatible types"));
			}
		} else if (firstLeaf->getToken()->tokenType == TokenKeyWordWrite) {
			firstNode->checkType(this);
			node->type = NoType;
		} else if (firstLeaf->getToken()->tokenType == TokenKeyWordRead) {
			node->getChildren()->at(1)->checkType(this);

			if (static_cast<LexemToken*>(node->getLeafs()->at(2)->getToken())->symbolTableKeyReference->checkType == NoType) {
				printTypeCheckError(String("Identifier not found"),node->getLeafs()->at(2)->getToken());
				node->type = ErrorType;
			} else if ((static_cast<LexemToken*>(node->getLeafs()->at(2)->getToken())->symbolTableKeyReference->checkType == IntType && node->getChildren()->at(1)->type == NoType) ||
					(static_cast<LexemToken*>(node->getLeafs()->at(2)->getToken())->symbolTableKeyReference->checkType == IntArrayType && node->getChildren()->at(1)->type == ArrayType)) {
				node->type = NoType;
			} else {
				printTypeCheckError(String("Incompatible types"));
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
		if (node->getChildren()->getLength() == 0) {
			node->type = IntType;
		} else {
			Node* firstChild = node->getChildren()->at(0);
			if (firstChild->getNodeType() == NodeExp) {
				firstChild->checkType(this);
				node->type = firstChild->type;
			} else if (firstChild->getNodeType() == NodeIndex) {
				firstChild->checkType(this);
				LexemToken* token = static_cast<LexemToken*>(node->getLeafs()->at(0)->getToken());
				if (token->symbolTableKeyReference->checkType == NoType) {

					printTypeCheckError(String("Identifier not found"), token);
					node->type = ErrorType;

				} else if (token->symbolTableKeyReference->checkType == IntType && firstChild->type == NoType) {
					node->type = token->symbolTableKeyReference->checkType;
				} else if (token->symbolTableKeyReference->checkType == IntArrayType && firstChild->type == ArrayType) {
					node->type = IntType;
				} else {
					node->type = ErrorType;
					printTypeCheckError(String("Not a primitive type"), token);
				}
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
		}
	} else if (node->getNodeType() == NodeOpExp) {
		for (unsigned i = 0; i < node->getChildren()->getLength(); i++) {
			node->getChildren()->at(i)->checkType(this);
		}
		if (node->getChildren()->getLength() == 2) {
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
	if (DEBUG) {
		v--;
		for (int e = 0; e < v; e ++){
			std::cout<<"   ";
		}
		std::cout<<"\\"<<nodeToString(node->getNodeType())<<std::endl;
	}
}

//TODO makeNode
void ParseVisitor::makeNode(Node* node) {
	if (DEBUG) {
		for (int e = 0; e < v; e ++){
			std::cout<<"   ";
		}
		std::cout<<nodeToString(node->getNodeType())<<std::endl;
		v++;
	}
	if (node->getNodeType() == NodeProg) {
		for (unsigned i = 0; i < node->getChildren()->getLength(); i++) {
			node->getChildren()->at(i)->makeCode(this);
		}
		tokenGenerator->getStream() << "STP" << std::endl;
	} else if (node->getNodeType() == NodeDecls) {
		for (unsigned i = 0; i < node->getChildren()->getLength(); i++) {
			node->getChildren()->at(i)->makeCode(this);
		}
	} else if (node->getNodeType() == NodeDecl) {
		if (node->getLeafs()->getLength() > 1) {
			Token* token = node->getLeafs()->at(1)->getToken();
			tokenGenerator->getStream() << "DS " << "$" << static_cast<LexemToken*>(token)->symbolTableKeyReference->ident<< " ";
		}
		node->getChildren()->at(0)->makeCode(this);//ARRAY
	} else if (node->getNodeType() == NodeArray) {
		if (node->getLeafs()->getLength() == 3) {
			Leaf* leaf = node->getLeafs()->at(1);
			tokenGenerator->getStream() << static_cast<IntegerToken*>(leaf->getToken())->value << std::endl;
		} else {
			tokenGenerator->getStream() << 1 << std::endl;
		}
	} else if (node->getNodeType() == NodeStatements){
		if (node->getChildren()->getLength() != 0) {
			for (unsigned i = 0; i < node->getChildren()->getLength(); i++) {
				node->getChildren()->at(i)->makeCode(this);
			}

		} else {
			tokenGenerator->getStream() << "NOP" << std::endl;
		}
	} else if (node->getNodeType() == NodeStatement) {
		Leaf* firstLeaf = node->getLeafs()->at(0);
		Node* firstNode = node->getChildren()->at(0);
		if (firstLeaf->getToken()->tokenType == TokenIdentifier) {
			Node* secondNode = node->getChildren()->at(1);
			secondNode->makeCode(this); //EXP
			tokenGenerator->getStream() << "LA " << "$" << static_cast<LexemToken*>(firstLeaf->getToken())->symbolTableKeyReference->ident<< " ";
			firstNode->makeCode(this); //INDEX
			tokenGenerator->getStream() << "STR" << std::endl;
		} else if (firstLeaf->getToken()->tokenType == TokenKeyWordWrite) {
			firstNode->makeCode(this); //EXP
			tokenGenerator->getStream() << "PRI " << std::endl;
		} else if (firstLeaf->getToken()->tokenType == TokenKeyWordRead) {
			tokenGenerator->getStream() << "REA " << std::endl;
			Leaf* thirdLeaf = node->getLeafs()->at(2);
			tokenGenerator->getStream() << "LA " << "$" << static_cast<LexemToken*>(thirdLeaf->getToken())->symbolTableKeyReference->ident << " ";
			firstNode->makeCode(this); //INDEX
			tokenGenerator->getStream() << "STR" << std::endl;
		} else if (firstLeaf->getToken()->tokenType == TokenBracketOpen2) {
			firstNode->makeCode(this); //STATEMENTS
		} else if (firstLeaf->getToken()->tokenType == TokenKeyWordIf) {
			firstNode->makeCode(this); //EXP
			String label1 = generateLabel();
			String label2 = generateLabel();
			tokenGenerator->getStream() << "JIN " << " # " << label1 << std::endl;
			node->getChildren()->at(1)->makeCode(this); //STATEMENT
			tokenGenerator->getStream() << "JIN" << " # " << label2 << std::endl;
			tokenGenerator->getStream() << "#" << label1 << " NOP" << std::endl;
			node->getChildren()->at(2)->makeCode(this); //STATEMENT
			tokenGenerator->getStream() << " # " << label2 << " NOP" << std::endl;
		} else if (firstLeaf->getToken()->tokenType == TokenKeyWordWhile) {
			String label1 = generateLabel();
			String label2 = generateLabel();
			tokenGenerator->getStream() << " # " << label1 << "NOP" << std::endl;
			firstNode->makeCode(this); //EXP
			tokenGenerator->getStream() << "JIN " << " # " << label2 << std::endl;
			node->getChildren()->at(1)->makeCode(this); //STATEMENT
			tokenGenerator->getStream() << "JMP " << " # " << label1 << std::endl;
			tokenGenerator->getStream() << "# " << label2 << "NOP" << std::endl;
		}
	} else if (node->getNodeType() == NodeIndex) {
		if (node->getLeafs()->getLength() != 0) {
			node->getChildren()->at(0)->makeCode(this);
			tokenGenerator->getStream() << "ADD " << std::endl;
		}

		//TODO epsilon
	} else if (node->getNodeType() == NodeExp) {
		if (node->getChildren()->at(1)->type == NoType) {
			node->getChildren()->at(0)->makeCode(this); //EXP2
		} else if (node->getChildren()->at(1)->type == OpGreater) {
			node->getChildren()->at(1)->makeCode(this); //OP_EXP
			node->getChildren()->at(0)->makeCode(this); //EXP2
			tokenGenerator->getStream() << "LES" << std::endl;
		} else if (node->getChildren()->at(1)->type == OpUnequal) {
			node->getChildren()->at(0)->makeCode(this); //EXP2
			node->getChildren()->at(1)->makeCode(this); //OP_EXP
			tokenGenerator->getStream() << "NOT" << std::endl;
		} else {
			node->getChildren()->at(0)->makeCode(this); //EXP2
			node->getChildren()->at(1)->makeCode(this); //OP_EXP
		}
	} else if(node->getNodeType() == NodeExp2) {
		Leaf* firstLeaf = node->getLeafs()->at(0);
		if (firstLeaf->getToken()->tokenType == TokenBracketOpen1) {
			node->getChildren()->at(0)->makeCode(this); //EXP
		} else if (firstLeaf->getToken()->tokenType == TokenIdentifier) {
			Token* token = node->getLeafs()->at(0)->getToken();
			tokenGenerator->getStream() << "LA " << "$" << *static_cast<LexemToken*>(token)->symbolTableKeyReference->ident << " ";
			node->getChildren()->at(0)->makeCode(this); //INDEX
			tokenGenerator->getStream() << "LV " << std::endl;
		} else if (firstLeaf->getToken()->tokenType == TokenInteger) {
			//dynamic_cast<IntegerToken*>(node->getLeafs()->at(0)->getToken())
			tokenGenerator->getStream() << "LC " <<  static_cast<IntegerToken*>(node->getLeafs()->at(0)->getToken())->value << std::endl;
		} else if (firstLeaf->getToken()->tokenType == TokenMinus) {
			tokenGenerator->getStream() << "LC " << 0 << std::endl;
			node->getChildren()->at(0)->makeCode(this); //EXP2
			tokenGenerator->getStream() << "SUB " << std::endl;
		} else if (firstLeaf->getToken()->tokenType == TokenExclamation) {
			node->getChildren()->at(0)->makeCode(this); //EXP2
			tokenGenerator->getStream() << "NOT " << std::endl;

		}
	} else if (node->getNodeType() == NodeOpExp) {
		for (unsigned i = 0; i < node->getChildren()->getLength();i++) {
			node->getChildren()->at(i)->makeCode(this);
		}

	} else if (node->getNodeType() == NodeOp) {
		switch (node->getLeafs()->at(0)->getToken()->tokenType) {
			case TokenPlus: tokenGenerator->getStream() << "ADD " << std::endl; break;
			case TokenMinus: tokenGenerator->getStream() << "SUB " << std::endl; break;
			case TokenAsterisk: tokenGenerator->getStream() << "MUL " << std::endl; break;
			case TokenColon: tokenGenerator->getStream() << "DIV " << std::endl; break;
			case TokenLessThan: tokenGenerator->getStream() << "LES " << std::endl; break;
			case TokenGreaterThan: ; break;
			case TokenAnd: tokenGenerator->getStream() << "AND " << std::endl; break;
			case TokenEquals1: tokenGenerator->getStream() << "EQU " << std::endl; break;
			case TokenEquals3: tokenGenerator->getStream() << "EQU " << std::endl; break;
			default: std::cout << "error NodeOp" << std::endl;break;
		}
	}
	if (DEBUG) {
		v--;
		for (int e = 0; e < v; e ++){
			std::cout<<"   ";
		}
		std::cout<<"\\"<<nodeToString(node->getNodeType())<<std::endl;
	}
}



bool ParseVisitor::isErrored() const {
	return errored;
}

void ParseVisitor::printTypeCheckError(String msg, Token* token) {
	errored = true;
	std::cout<<msg;
	if (token) {
		std::cout<<", line:"<<token->tokenInfo->line<<", col: "<<token->tokenInfo->col;
		if (LexemToken* lexemToken = dynamic_cast<LexemToken*>(token)) {
			std::cout<<", lexem: "<<lexemToken->symbolTableKeyReference->ident;
		} else if (IntegerToken* integerToen = dynamic_cast<IntegerToken*>(token)) {
			std::cout<<", value: "<<integerToen->value;
		}
		std::cout<<", tokenType:"<<tokenToString(token->tokenType)<<std::endl;
	}
}

void ParseVisitor::printParseError(String msg) {
	errored = true;
	std::cout<<msg<<", token: "<<(currentToken? tokenToString(currentToken->tokenType): "undefined")<<" at: line - "<<currentToken->tokenInfo->line<<", column - "<<currentToken->tokenInfo->col<<std::endl;
}


int main(int argc, char **argv) {
	DEBUG = false;
	if (argc < 2) {
		std::cout<<"No file specified  to work with. Exiting..."<<std::endl;
		return -1;
	} else if (argc >= 3) {
		String arg1 = String(argv[1]);
		if (arg1.compare(String("--debug"))) {
			DEBUG = true;
			std::cout<<"Printing debug info activated."<<std::endl;
		} else {
			std::cout<<"Warning. Too much arguments. Assuming file argument is the last one."<<std::endl;
		}

	}

	Parser parser = Parser(argv[argc - 1]);
	if (parser.isFinished()) {
		std::cout<<"There was an error, opening file. Exiting..."<<std::endl;
		return -1;
	}
	std::cout<<"Parsing..."<<std::endl;
	parser.parse();
	if (DEBUG) {
		for (unsigned i = 0; i < 3; i++)
			std::cout<<'\n';
	}
	if (parser.isErrored()) {
		std::cout<<"There were errors, while generating parse tree. Aborting..."<<std::endl;
	} else {
		std::cout<<"Checking types..."<<std::endl;

		parser.typeCheck();
		if (DEBUG) {
			for (unsigned i = 0; i < 3; i++)
					std::cout<<'\n';
		}
		if (parser.isErrored()) {
			std::cout<<"There were errors, while evaluating types. Aborting..."<<std::endl;
		} else {
			std::cout<<"Making code..."<<std::endl;
			//make code
			parser.makeCode();
			if (parser.isErrored()) {
				std::cout << "There were errors, while generating code. Aborting.. " << std::endl;
			} else {
				std::cout<<"Done."<<std::endl;
			}
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

