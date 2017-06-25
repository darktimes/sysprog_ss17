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
	std::cout<<"node deleted: "<<nodeToString(nodeType)<<std::endl;
	delete children;
	delete leafs;
}

Leaf::Leaf(Token* token): token(*token) {

}

Token* Leaf::getToken() {
	return &token;
}

Leaf::~Leaf() {
	std::cout<<"leaf deleted: "<<tokenToString(token.tokenType)<<std::endl;
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

