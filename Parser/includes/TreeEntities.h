#pragma once

#include "Parser.h"
#include "Tokens.h"
#include "String.h"

class ParseVisitor;



typedef enum e_NodeType {
	NodeProg,
	NodeDecls,
	NodeDecl,
	NodeArray,
	NodeStatements,
	NodeStatement,
	NodeExp,
	NodeExp2,
	NodeIndex,
	NodeOpExp,
	NodeOp
} NodeType;

String nodeToString(NodeType);

class ITreeEntity {
	public:
		virtual bool isLeaf() const = 0;
		virtual ~ITreeEntity() {}
};

class TreeDLListElem {
	public:
		TreeDLListElem(ITreeEntity* content);
		virtual ~TreeDLListElem();
		TreeDLListElem* previous;
		TreeDLListElem* next;
		ITreeEntity* getContent();
	private:
		ITreeEntity* content;

};

class TreeDLList {
	public:
		TreeDLList();
		virtual ~TreeDLList();
		void pushFront(ITreeEntity* elem);
		void pushBack(ITreeEntity* elem);
		ITreeEntity* popFront();
		ITreeEntity* popBack();

		const ITreeEntity* at(unsigned int index) const;
		unsigned int getLength() const;
		void removeAt(unsigned int index);

	private:
		unsigned int length;
		TreeDLListElem* first;
		TreeDLListElem* last;

};



class Node: public ITreeEntity {
	public:
		Node(NodeType nodeType);
		void parse(ParseVisitor* parseVisitor);
		bool isLeaf() const override;
		void addChild(ITreeEntity* child);
		NodeType getNodeType() const;
		virtual ~Node();
	private:
		NodeType nodeType;
		TreeDLList children;
};

class Leaf: public ITreeEntity {
	public:
		bool isLeaf() const override;
		const Token& getToken() const;
		Leaf(Token& token);
		virtual ~Leaf();
	private:
		Token token;
};
