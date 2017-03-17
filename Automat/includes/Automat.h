/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_SRC_H_
#define Automat_SRC_H_

#include "../../Scanner/includes/IScanner.h"
#include "../../Shared/includes/String.h"
#include "../../Shared/includes/TokenType.h"

class State;

#include "States.h"
#include "IAutomat.h"


class Automat : public IAutomat{
private:
	IScanner* scanner;
	State* lastFinalState;
	State* currentState;
	//String * const currentLexem;

public:
	Automat(IScanner* iScanner);
	virtual ~Automat();
	IScanner* getScanner() const;
	void changeState(State* state);

	/*Override from parent*/
	void process(const char& c);
	
	State* getLastFinalState() const;
};

#endif /* Automat_H_ */
