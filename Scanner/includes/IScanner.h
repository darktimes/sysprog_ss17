/*
 * IScanner.h
 *
 *  Created on: 27 Oct 2016
 *      Author: David Seifried
 */

#ifndef SCANNER_SRC_ISCANNER_H_
#define SCANNER_SRC_ISCANNER_H_

#include "../../Shared/includes/String.h"
#include "../../Shared/includes/TokenType.h"

/*
 * Interface to be used by 'Automat' (Finite State Machine)
 */
class IScanner {
public:
	virtual ~IScanner() {}
	virtual void mkToken(TokenType tokenType,String* lexem) = 0; // creates the token of given type and lexem
	virtual void mkToken(TokenType tokenType, const char& c) = 0; // creates the token of given type and lexem
	virtual void ungetChar(int number) = 0; // readjust position of scanner

};

#endif /* SCANNER_SRC_ISCANNER_H_ */

