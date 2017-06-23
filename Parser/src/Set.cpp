#include "Set.h"
#include <stdexcept>
#include <iostream>


const TokenType FirstDeclElems[1] = {TokenKeyWordInt};
const TokenType FirstOpElems[8] = {TokenPlus, TokenMinus, TokenAsterisk, TokenColon, TokenGreaterThan, TokenLessThan, TokenEquals1, TokenEquals3};
const TokenType FirstStatementElems[6] = {TokenIdentifier, TokenKeyWordWrite, TokenKeyWordRead, TokenBracketOpen2, TokenKeyWordIf, TokenKeyWordWhile};
const TokenType FirstExp2Elems[5] = {TokenBracketOpen1, TokenIdentifier, TokenInteger, TokenMinus, TokenExclamation};
const TokenType FirstArrayElems[1] = {TokenBracketOpen3};

const TokenType FollowArrayElems[1] = {TokenIdentifier};
const TokenType FollowStatementsElems[1] = {TokenBracketClose2};
const TokenType FollowOpExpElems[4] = {TokenBracketClose3, TokenBracketClose1, TokenKeyWordElse, TokenSemicolon};





const Set* const Set::FirstDecl = new Set(FirstDeclElems, false);
//const Set* const Set::FirstDecls = new Set(FirstDeclElems, true);
const Set* const Set::FirstOp = new Set(FirstOpElems, false);
const Set* const Set::FirstStatement = new Set(FirstStatementElems, false);
//const Set* const Set::FirstStatements = new Set(FirstStatementElems, true);
const Set* const Set::FirstExp2 = new Set(FirstExp2Elems, false);
const Set* const Set::FirstArray = new Set(FirstArrayElems, true);


const Set* const Set::FollowDecls = new Set(FirstStatementElems, true);
const Set* const Set::FollowArray = new Set(FollowArrayElems, false);
const Set* const Set::FollowStatements = new Set(FollowStatementsElems, true);
const Set* const Set::FollowOpExp = new Set(FollowOpExpElems, false);

const Set* const Set::FollowIndex = constructFollowIndexSet();
const Set* const Set::FirstProg = constructFirstProgSet();

bool contains(const TokenType* const array, const TokenType elem) {
	for (unsigned int i = 0; i < sizeof(array) / sizeof(TokenType*); i++) {
		if (elem == array[i]) {
			return true;
		}
	}
	return false;
}


Set::Set(const TokenType* const elems, bool containsEpsilon): containsEpsilon(containsEpsilon) {
	unsigned int i = sizeof(elems) / sizeof(TokenType*);
	TokenType* temp_elems = new TokenType[i];
	size = 0;
	for (unsigned int j = 0; j < i; j++) {
		if (!::contains(temp_elems, elems[j])) {
			temp_elems[size++] = elems[j];
		}
	}
	this->elems = new TokenType[size];
	for (i = 0; i < size; i++) {
		this->elems[i] = temp_elems[i];
	}
}

Set::Set(const Set* const toCopy, bool containsEpsilon): containsEpsilon(containsEpsilon) {
	this->size = toCopy->size;
	this->elems = new TokenType[size];
	for (unsigned int i = 0; i < size; i++) {
		this->elems[i] = toCopy->get(i);
	}
}

//Set::Set(std::initializer_list<TokenType> list, bool containsEpsilon = false): containsEpsilon(containsEpsilon) {
//	this->size = list.size();
//	this->elems = new TokenType[size];
//	int i = 0;
//	for (TokenType t : list) {
//		elems[i++] = t;
//	}
//}

Set::~Set() {
	delete[] elems;
}

bool Set::insert(TokenType elem) {
	if (!::contains(this->elems, elem)) {
		TokenType* new_elems = new TokenType[size + 1];
		for (unsigned int i = 0; i < size; i++) {
			new_elems[i] = elems[i];
		}
		new_elems[size] = elem;
		delete[] elems;
		this->elems = new_elems;
		size++;
		return true;
	}
	return false;
}

TokenType Set::get(unsigned int index) const{
	if (index < size) {
		return elems[index];
	} else {
		throw std::range_error("Index out of bound exception at Set::get()");
	}
}

TokenType Set::operator[](unsigned int index) const {
	return get(index);
}

bool Set::isEmpty() const{
	return size == 0;
}

bool Set::contains(const Token* elem) const{
//	std::cout<<"contains; existence: "<<(!elem)<<std::endl;
	if (!elem) {
		return containsEpsilon;
	}
	for (unsigned i = 0; i < size; i++) {
//		std::cout<<"contains; elem:"<<tokenToString(get(i))<<std::endl;
		if (get(i) == elem->tokenType) {
			return true;
		}
	}
	return false;
}

unsigned int Set::getSize() const {
	return size;
}

Set* Set::FirstOf(const Set* const firstSet, const Set* const followSet) {
	Set* result = new Set(firstSet);
	if (result->containsEpsilon) {
		for (unsigned int i = 0; i < followSet->size; i++) {
			result->insert(followSet->get(i));
		}
	}
	return result;
}

void Set::mergeWith(const Set* const anotherSet, bool containsEpsilon) {
	for (unsigned int i = 0; i < anotherSet->size; i++) {
		this->insert(anotherSet->get(i));
	}
	this->containsEpsilon = containsEpsilon;
}

const Set* const Set::constructFollowIndexSet() {
	Set* result = new Set(FirstOp, false);
	result->mergeWith(Set::FollowOpExp,false);
	result->insert(TokenEquals2);
	return result;
}

const Set* const Set::constructFirstProgSet() {
	Set* result = new Set(FirstDecl, true);
	result->mergeWith(FirstStatement, true);
	return result;
}
