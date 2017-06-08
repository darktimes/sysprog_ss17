/*
 * IState.h
 * State's interface. Describes the functionality, that each state should contain.
 *  Created on: Oct 26, 2016
 *      Author: Sergey
 */

#pragma once

#include "Automat.h"

class Automat;

class IState {

public:
	virtual ~IState() {}
	virtual void processChar(const char& c, Automat* automat) = 0;

};
