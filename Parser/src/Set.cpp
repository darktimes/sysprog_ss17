#include "Set.h"
#include <stdexcept>
#include <iostream>

bool contains(TokenType* array, TokenType elem) {
	for (unsigned int i = 0; i < sizeof(array); i++) {
		if (elem == array[i]) {
			return true;
		}
	}
	return false;
}


Set::Set(TokenType* elems) {
	unsigned int i = sizeof(elems);
	TokenType* temp_elems = new TokenType[i];
	size = 0;
	for (unsigned int j = 0; j < i; j++) {
		if (!contains(temp_elems, elems[j])) {
			temp_elems[size++] = elems[j];
		}
	}
	this->elems = new TokenType[size];
	for (i = 0; i < size; i++) {
		this->elems[i] = temp_elems[i];
	}
}

Set::~Set() {
	delete[] elems;
}

bool Set::insert(TokenType elem) {
	if (!contains(this->elems, elem)) {
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

unsigned int Set::getSize() const {
	return size;
}
