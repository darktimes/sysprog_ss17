#include "TreeEntities.h"
#include <stdexcept>




Node::Node(NodeType nodeType): nodeType(nodeType), children(new List<Node>()), leafs(new List<Leaf>()), type(NotInited) {

}

void Node::parse(ParseVisitor* parseVisitor) {
	parseVisitor->parseNode(this);
}

void Node::checkType(ParseVisitor* parseVisitor) {
	parseVisitor->checkNode(this);
}

void Node::makeCode(ParseVisitor* parseVisitor) {
	parseVisitor->makeNode(this);
}

void Node::addChild(Node* child) {
	children->pushBack(child);
}

void Node::addLeaf(Leaf* leaf) {
	leafs->pushBack(leaf);
}

List<Node>* Node::getChildren() {
	return this->children;
}

List<Leaf>* Node::getLeafs() {
	return this->leafs;
}

NodeType Node::getNodeType() const {
	return nodeType;
}

Node::~Node() {
//	std::cout<<"node deleted: "<<nodeToString(nodeType)<<std::endl;
	delete children;
	delete leafs;
}

String& tabulate(String& which, unsigned t) {
	for (unsigned i = 0; i < t; i++) {
		which += "   ";
	}
	return which;
 }

String Node::toString(unsigned t) {
	String result;
	if (t == 0) {
		result = "------------------------------------------";
		result += '\n';
	} else {
		tabulate(result, t);
	}
	result += (String("Node: ") + nodeToString(nodeType));
	result += '\n';


	tabulate(result, t);
	result += (String("CheckType: ") + nodeTypeToString(type));
	result += '\n';

	tabulate(result, t + 1);

	result += "children:";
	result += '\n';

	for (unsigned i = 0; i < getChildren()->getLength(); i++) {
		result += getChildren()->at(i)->toString(t + 2);
	}
	result += '\n';
	tabulate(result, t+1);
	result += "leafs:";
	result += '\n';
	for (unsigned i = 0; i < getLeafs()->getLength(); i++) {
		result += getLeafs()->at(i)->toString(t + 2);
	}
	return result;
}

Leaf::Leaf(Token* token): token(token) {

}

Token* Leaf::getToken() {
	return token;
}

String Leaf::toString(unsigned t) {
	String result;
	tabulate(result, t);
	result += (String("Leaf:") + tokenToString(token->tokenType));
	if (LexemToken* lexemTokem = dynamic_cast<LexemToken*>(token)) {
		result += String(", ") + nodeTypeToString(lexemTokem->symbolTableKeyReference->checkType);
	}
	result += '\n';
	return result;
}
Leaf::~Leaf() {
//	std::cout<<"leaf deleted: "<<tokenToString(token->tokenType)<<std::endl;
}


String nodeToString(NodeType nodeType) {
	switch (nodeType) {
		case NodeUnknown: return "NOT_INITED";
		case NodeProg: return "PROG";
		case NodeDecls: return "DECLS";
		case NodeDecl: return "DECL";
		case NodeArray: return "ARRAY";
		case NodeStatements: return "STATEMENTS";
		case NodeStatement: return "STATEMENT";
		case NodeExp: return "EXP";
		case NodeExp2: return "EXP2";
		case NodeIndex: return "Index";
		case NodeOpExp: return "OP_EXP";
		case NodeOp: return "OP";
		default: return "unknown";
	}
}

String nodeTypeToString(NodeCheckType t) {
	switch (t) {
	case NotInited: return String ("NotInited");
	case IntType: return String ("IntType");
	case IntArrayType: return String ("IntArrayType");
	case ArrayType: return String("ArrayType");
	case NoType: return String("NoType");
	case ErrorType: return String("ErrorType");
	case OpPlus: return String("OpPlus");
	case OpMinus: return String("OpPlus");
	case OpMult: return String("OpMult");
	case OpDiv: return String("OpDiv");
	case OpLess: return String("OpLess");
	case OpGreater: return String("OpGreater");
	case OpEqual: return String("OpEqual");
	case OpUnequal: return String("OpUnequal");
	case OpAnd: return String("OpAnd");
	default: return String("Eblan");
	}
}

