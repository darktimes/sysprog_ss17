#pragma once

#include "Parser.h"
#include "Tokens.h"
#include "String.h"
#include "TokenType.h"

class ParseVisitor;


String nodeToString(NodeType);


template<typename T>
class ListItem {
	public:
		ListItem(T* content);
		virtual ~ListItem();
		ListItem<T>* previous;
		ListItem<T>* next;
		T* getContent();
	private:
		T content;

};

template<typename T>
class List {
	public:
		List();
		virtual ~List();
		void pushFront(T* elem);
		void pushBack(T* elem);
		T* popFront();
		T* popBack();

		T* at(unsigned int index);
		unsigned int getLength() const;
		void removeAt(unsigned int index);

	private:
		unsigned int length;
		ListItem<T>* first;
		ListItem<T>* last;
};



class Leaf {
	public:
		Token* getToken();
		Leaf(Token* token);
		virtual ~Leaf();
	private:
		Token token;
};

class Node {
	public:
		Node(NodeType nodeType);
		void parse(ParseVisitor* parseVisitor);
		void checkType(ParseVisitor* parseVisitor);
		void makeCode(ParseVisitor* parseVisitor);
		void addChild(Node* child);
		void addLeaf(Leaf* child);
		NodeType getNodeType() const;
		virtual ~Node();
		List<Node>* getChildren();
		List<Leaf>* getLeafs();


	private:
		NodeType nodeType;
		List<Node>* children;
		List<Leaf>* leafs;

	public:
		NodeCheckType type;

};


template<class T>
ListItem<T>::ListItem(T* content): previous(nullptr), next(nullptr), content(*content)  {

}

template<class T>
T* ListItem<T>::getContent(){
	return &content;
}

template<class T>
ListItem<T>::~ListItem() {
	std::cout<<"list item deleted"<<std::endl;
}
template<class T>
List<T>::List(): length(0), first(nullptr), last(nullptr) {

}

template<class T>
List<T>::~List() {
	std::cout<<"list deleted"<<std::endl;
	ListItem<T>* current = first;
	if (length == 1) {
		delete first;
	} else if (length == 2) {
		delete first;
		delete last;
	} else {
		while (current != last) {
			ListItem<T>* next = current->next;
			delete current;
			current = next;
		}
		delete last;
		last = nullptr;
	}
}

template<class T>
T* List<T>::at(unsigned int index){
	if (index < length) {
		unsigned int i = 0;
		ListItem<T>* current = first;
		while (i != index) {
			current = first->next;i++;
		}
		return current->getContent();
	} else {
		throw std::range_error("Index out of bound error at List.at()");
	}
}

template<class T>
unsigned List<T>::getLength() const {
	return length;
}

template<class T>
void List<T>::pushFront(T* elem) {
	if (length == 0) {
		first = last = new ListItem<T>(elem);
	} else if (length == 1) {
		first = new ListItem<T>(elem);
		first->next = last;
		last->previous = first;
	} else {
		ListItem<T>* listElem = new ListItem<T>(elem);
		first->previous = listElem;
		listElem->next = first;
		first = listElem;
	}
	length++;
}


template<class T>
void List<T>::pushBack(T* elem) {
	if (length == 0) {
		first = last = new ListItem<T>(elem);
	} else if (length == 1) {

		last = new ListItem<T>(elem);

		first->next = last;
		last->previous = first;
	} else {
		ListItem<T>* listElem = new ListItem<T>(elem);
		last->next = listElem;
		listElem->previous = last;
		last = listElem;
	}
	length++;
}

template<class T>
T* List<T>::popFront() {
	if (length == 0) {
		return nullptr;
	}
	if (length == 1) {
		T* result = first->getContent();
		delete first;
		first = last = nullptr;
		length--;
		return result;
	}
	T* result = first->getContent();
	first = first->next;
	delete first->previous;
	first->previous = nullptr;
	length--;
	return result;
}

template<class T>
T* List<T>::popBack() {
	if (length == 0) {
		return nullptr;
	}
	if (length == 1) {
		T* result = first->getContent();
		delete last;
		first = last = nullptr;
		length--;
		return result;
	}
	T* result = last->getContent();
	last = last->previous;
	delete last->next;
	last->next= nullptr;
	length--;
	return result;
}

template<class T>
void List<T>::removeAt(unsigned int index) {
	if (index >= length) {
		throw std::range_error("Out of bound error at TreeDLList.removeAt()");
	}
	if (index == 0) {
		popFront();
		return;
	}
	if (index == length - 1) {
		popBack();
		return;
	}

	ListItem<T>* currentListElem = last;
	unsigned int currentIndex = length - 1;
	while (currentIndex != index) {
		currentIndex--;
		currentListElem = currentListElem->previous;
	}
	currentListElem->previous->next = currentListElem->next;
	currentListElem->next->previous = currentListElem->previous;
	delete currentListElem;

}


