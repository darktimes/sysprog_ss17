/*
 * Sets.h
 *
 *  Created on: Jun 21, 2017
 *      Author: fattum
 */

#pragma once

class Set {

	public:
		Set(TokenType* elems);
		Set(Set* set);
		unsigned int getSize();
		bool empty();
		bool insert(TokenType& elem);
		TokenType& get(unsigned int index) const;
		TokenType& operator[](int index) const;

	private:
		unsigned int size;
		TokenType elems[];
};
