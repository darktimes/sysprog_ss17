/*
 * Sets.h
 *
 *  Created on: Jun 21, 2017
 *      Author: fattum
 */

#pragma once

#include "TokenType.h"

class Set {

	public:
		Set(TokenType* elems);
		Set(Set* set);
		virtual ~Set();
		bool insert(TokenType elem);

		bool isEmpty() const;
		unsigned int getSize() const;
		TokenType get(unsigned int index) const;
		TokenType operator[](unsigned int index) const;

	private:
		unsigned int size;
		TokenType* elems;
};
