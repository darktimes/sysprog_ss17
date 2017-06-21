#include "Set.h"

Set::Set(TokenType* elems) {
	int i = 0;
	while (elems[i]) {
		i++;
	}
	this->size = i + 1;
	i = 0;
	this->elems = new TokenType[size];
	while (elems[i]) {
		this->elems[i] = elems[i];
	}
}

bool Set::insert(TokenType& elem) {

}

