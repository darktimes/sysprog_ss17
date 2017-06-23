/*
 * Sets.h
 *
 *  Created on: Jun 21, 2017
 *      Author: fattum
 */

#pragma once

#include "Tokens.h"
#include "TokenType.h"

class Set {

	public:

		static const Set* const FirstProg;
		static const Set* const FirstDecl;
//		static const Set* const FirstDecls;
		static const Set* const FirstOp;
		static const Set* const FirstStatement;
//		static const Set* const FirstStatements;
		static const Set* const FirstExp2;
		static const Set* const FirstArray;

		static const Set* const FollowDecls;
		static const Set* const FollowArray;
		static const Set* const FollowStatements;
		static const Set* const FollowIndex;
		static const Set* const FollowOpExp;



//		Set(std::initializer_list<TokenType> list, bool containsEpsilon = false);
		Set(const TokenType* const elems, bool containsEpsilon = false);
		Set(const Set* const set, bool containsEpsilon = false);
		virtual ~Set();
		bool insert(TokenType elem);

		bool isEmpty() const;
		bool contains(const Token* elem) const;
		bool contains(const TokenType elem) const;
		unsigned int getSize() const;
		TokenType get(unsigned int index) const;
		TokenType operator[](unsigned int index) const;
		void mergeWith(const Set* const anotherSet, bool);

		static Set* FirstOf(const Set* const firstSet, const Set* const followSet);
	private:
		bool containsEpsilon;
		unsigned int size;
		TokenType* elems;
		static const Set* const constructFollowIndexSet();
		static const Set* const constructFirstProgSet();
};
