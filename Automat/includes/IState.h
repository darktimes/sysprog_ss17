/*
 * IState.h
 * State's interface. Describes the functionality, that each state should contain.
 *  Created on: Oct 26, 2016
 *      Author: Sergey
 */

#ifndef ISTATE_SRC_H_
#define ISTATE_SRC_H_

class Automat;

#include "Automat.h"

class IState {

public:
	virtual ~IState() {}
	virtual void processChar(const char& c, Automat* automat) = 0;

};

#endif /* IState_H_ */
