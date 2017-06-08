/*
 * IAutomat.h
 * Automat's interface
 *  Created on: Oct 26, 2016
 *      Author: Sergey
 */

#pragma once

class IAutomat {

public:
	virtual void process(const char& c) = 0;
	virtual ~IAutomat() {}
};
