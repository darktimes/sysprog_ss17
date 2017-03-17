/*
 * IAutomat.h
 * Automat's interface
 *  Created on: Oct 26, 2016
 *      Author: Sergey
 */

#ifndef IAUTOMAT_SRC_H_
#define IAUTOMAT_SRC_H_

class IAutomat{

public:
	virtual void process(const char& c) = 0;
	virtual ~IAutomat() {}
};

#endif /* IAutomat_H_ */
