/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Symboltable.h"
#include "../Shared/includes/String.h"

Symboltable::Symboltable() {

}

Symboltable::~Symboltable() {
	// TODO Auto-generated destructor stub
}

char* StringTab::insert(char* lexem, int size) {
	char* tmp = this->freeP;
	if (size < this->freeSpace) {
		memcpy(this->freeP, lexem, size + 1);
		this->freeP[size] = ‘\0‘;
		this->freeP += size + 1;
		this->freeSpace -= size + 1;
	} else {
		/* todo */
	}
	return tmp;
}
