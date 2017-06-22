#include "TreeEntities.h"
#include <stdexcept>

String nodeToString(NodeType nodeType) {
	switch (nodeType) {
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

TreeDLListElem::TreeDLListElem(ITreeEntity* content): previous(nullptr), next(nullptr),content(content)  {

}

ITreeEntity* TreeDLListElem::getContent(){
	return content;
}

TreeDLListElem::~TreeDLListElem() {
}

TreeDLList::TreeDLList(): length(0), first(nullptr), last(nullptr) {

}

TreeDLList::~TreeDLList() {
	TreeDLListElem* current = first;
	if (length == 1) {
		delete first;
	} else if (length == 2) {
		delete first;
		delete last;
	} else {
		while (current != last) {
			TreeDLListElem* next = current->next;
			delete current;
			current = next;
		}
		delete last;
	}
}

const ITreeEntity* TreeDLList::at(unsigned int index) const{
	if (index < length) {
		unsigned int i = 0;
		TreeDLListElem* current = first;
		while (i != index) {
			current = first->next;
		}
		return current->getContent();
	} else {
		throw std::range_error("Index out of bound error at TreeDLList.at()");
	}
}

unsigned int TreeDLList::getLength() const {
	return length;
}

void TreeDLList::pushFront(ITreeEntity* elem) {
	if (length == 0) {
		first = last = new TreeDLListElem(elem);
	} else if (length == 1) {
		first = new TreeDLListElem(elem);
		first->next = last;
		last->previous = first;
	} else {
		TreeDLListElem* listElem = new TreeDLListElem(elem);
		first->previous = listElem;
		listElem->next = first;
		first = listElem;
	}
	length++;
}

void TreeDLList::pushBack(ITreeEntity* elem) {
	if (length == 0) {
		first = last = new TreeDLListElem(elem);
	} else if (length == 1) {
		last = new TreeDLListElem(elem);
		first->next = last;
		last->previous = first;
	} else {
		TreeDLListElem* listElem = new TreeDLListElem(elem);
		last->next = listElem;
		listElem->previous = last;
		last = listElem;
	}
	length++;
}

ITreeEntity* TreeDLList::popFront() {
	if (length == 0) {
		return nullptr;
	}
	if (length == 1) {
		ITreeEntity* result = first->getContent();
		delete first;
		first = last = nullptr;
		length--;
		return result;
	}
	ITreeEntity* result = first->getContent();
	first = first->next;
	delete first->previous;
	first->previous = nullptr;
	length--;
	return result;
}

ITreeEntity* TreeDLList::popBack() {
	if (length == 0) {
		return nullptr;
	}
	if (length == 1) {
		ITreeEntity* result = first->getContent();
		delete last;
		first = last = nullptr;
		length--;
		return result;
	}
	ITreeEntity* result = last->getContent();
	last = last->previous;
	delete last->next;
	last->next= nullptr;
	length--;
	return result;
}

void TreeDLList::removeAt(unsigned int index) {
	if (index >= length) {
		throw std::range_error("Out of bound error at TreeDLList.removeAt()");
	}
	if (index == 0) {
		popFront();
	}
	if (index == length - 1) {
		popBack();
	}

	TreeDLListElem* currentListElem = last;
	unsigned int currentIndex = length - 1;
	while (currentIndex != index) {
		currentIndex--;
		currentListElem = currentListElem->previous;
	}
	currentListElem->previous->next = currentListElem->next;
	currentListElem->next->previous = currentListElem->previous;
	delete currentListElem;

}

Node::Node(NodeType nodeType): nodeType(nodeType) {
	children = TreeDLList();
}

bool Node::isLeaf() const {
	return false;
}

void Node::parse(ParseVisitor* parseVisitor) {
	parseVisitor->parseNode(this);
}

void Node::addChild(ITreeEntity* child) {
	children.pushBack(child);
}

NodeType Node::getNodeType() const {
	return nodeType;
}

Node::~Node() {

}

Leaf::Leaf(Token& token): token(token) {

}

bool Leaf::isLeaf() const {
	return true;
}

const Token& Leaf::getToken() const {
	return token;
}

Leaf::~Leaf() {

}


