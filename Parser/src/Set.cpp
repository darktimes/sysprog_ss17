#include "Set.h"
#include <stdexcept>
#include <iostream>


const TokenType  FirstDeclElems[1] = {TokenKeyWordInt};
const TokenType FirstOpElems[8] = {TokenPlus, TokenMinus, TokenAsterisk, TokenColon, TokenGreaterThan, TokenLessThan, TokenEquals1, TokenEquals3};
const TokenType FirstStatementElems[6] = {TokenIdentifier, TokenKeyWordWrite, TokenKeyWordRead, TokenBracketOpen2, TokenKeyWordIf, TokenKeyWordWhile};
const TokenType FirstExp2Elems[5] = {TokenBracketOpen1, TokenIdentifier, TokenInteger, TokenMinus, TokenExclamation};
const TokenType FirstArrayElems[1] = {TokenBracketOpen3};

const TokenType FollowArrayElems[1] = {TokenIdentifier};
const TokenType FollowStatementsElems[1] = {TokenBracketClose2};
const TokenType FollowOpExpElems[4] = {TokenBracketClose3, TokenBracketClose1, TokenKeyWordElse, TokenSemicolon};





const Set* const Set::FirstDecl = new Set(FirstDeclElems, 1,  false);
//const Set* const Set::FirstDecls = new Set(FirstDeclElems, true);
const Set* const Set::FirstOp = new Set(FirstOpElems, 8, false);
const Set* const Set::FirstStatement = new Set(FirstStatementElems, 6, false);
//const Set* const Set::FirstStatements = new Set(FirstStatementElems, true);
const Set* const Set::FirstExp2 = new Set(FirstExp2Elems, 5, false);
const Set* const Set::FirstArray = new Set(FirstArrayElems, 1, true);


const Set* const Set::FollowDecls = new Set(FirstStatementElems, 6, true);
const Set* const Set::FollowArray = new Set(FollowArrayElems, 1, false);
const Set* const Set::FollowStatements = new Set(FollowStatementsElems, 1, true);
const Set* const Set::FollowOpExp = new Set(FollowOpExpElems, 4, false);

const Set* const Set::FollowIndex = constructFollowIndexSet();
const Set* const Set::FirstProg = constructFirstProgSet();

bool contains(const TokenType* const array, unsigned size, const TokenType elem) {
	for (unsigned int i = 0; i < size; i++) {
		if (elem == array[i]) {
			return true;
		}
	}
	return false;
}


Set::Set(const TokenType* const elems, unsigned size, bool containsEpsilon): size(size), containsEpsilon(containsEpsilon) {

//	unsigned int i = sizeof(elems) / sizeof(TokenType);
//	std::cout<<"i"<<i<<std::endl;
	TokenType* temp_elems = new TokenType[size];
	int l = 0;
	for (unsigned int j = 0; j < size; j++) {
		if (!::contains(temp_elems, size, elems[j])) {
			temp_elems[l++] = elems[j];
		}
	}
	this->elems = new TokenType[size];
	for (l = 0; l < size; l++) {
		this->elems[l] = temp_elems[l];
	}
}

Set::Set(const Set* const toCopy, bool containsEpsilon): containsEpsilon(containsEpsilon) {
	this->size = toCopy->size;
	this->elems = new TokenType[size];
	for (unsigned int i = 0; i < size; i++) {
		this->elems[i] = toCopy->get(i);
	}
}

Set::~Set() {
	delete[] elems;
}

bool Set::insert(TokenType elem) {
	if (!::contains(this->elems, size, elem)) {
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
