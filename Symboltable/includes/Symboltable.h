/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

class Symboltable {
private:
	static const int tableSize = 100	;
	StringTab strTab;

public:
	int hash(char* key);

	Symboltable();
	virtual ~Symboltable();

};

#endif /* SYMBOLTABLE_H_ */
