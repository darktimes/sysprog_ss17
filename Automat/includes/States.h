/*
 * States.h
 * State's abstract class
 *  Created on: Oct 26, 2016
 *      Author: Sergey
 */

#ifndef STATES_SRC_H_
#define STATES_SRC_H_

#include "IState.h"

static const int MAX_CHAR_COUNT = 255;

class State : public IState{
protected:
	const bool _isAcceptable;
	String * const _lexem;
public:
	State();
	State(bool isAcceptable, const char& lexem);
	State(bool isAcceptable, String * const lexem);
	virtual ~State();
	bool isAcceptable();
	void fallback(const int& count, Automat* automat);
	virtual void createToken(Automat* automat) = 0;
};

class StateInit: public State {
public:
	StateInit() : State(true, '\0') {}
	void createToken(Automat* automat);
	void processChar(const char&, Automat* automat);
};

class StateAutoFallback: public State {
public:
	StateAutoFallback(bool isFinal, const char& c) : State(isFinal, c) {}
	StateAutoFallback(bool isFinal, String * const c) : State(isFinal, c) {}
	void processChar(const char&, Automat* automat);
};

class StateSeparator: public StateAutoFallback {
public:
	StateSeparator(const char& c) : StateAutoFallback(true, c) {}
	void createToken(Automat* automat);
};

class StateFinished: public State {
public:
	StateFinished() : State(true, '\0') {}
	void createToken(Automat* automat);
	void processChar(const char&, Automat* automat);
};

class StateIdentifier: public State {
public:
	StateIdentifier(const char& c) : State(true, c) {}
	void createToken(Automat* automat);
	void processChar(const char&, Automat* automat);
};

class StateInteger: public State {
public:
	StateInteger(const char& c) : State(true, c) {}
	void createToken(Automat* automat);
	void processChar(const char&, Automat* automat);
};

class StateColon: public State {
public:
	StateColon(const char& c) : State(true, c) {}
	void createToken(Automat* automat);
	void processChar(const char&, Automat* automat);
};

class StateEquals: public State {
public:
	StateEquals(const char& c) : State(true, c) {}
	void createToken(Automat* automat);
	void processChar(const char&, Automat* automat);
};

class StateSigns: public StateAutoFallback {
public:
	StateSigns(const char& c) : StateAutoFallback(true, c) {}
	void createToken(Automat* automat);
};

class StateAmp: public State {
public:
	StateAmp(const char& c) : State(false, c){}
	void createToken(Automat* automat);
	void processChar(const char&, Automat* automat);
};

class StateAmpAmp: public StateAutoFallback {
public:
	StateAmpAmp(String * const c) : StateAutoFallback(true, c){}
	void createToken(Automat* automat);
};


class StateColonEquals: public StateAutoFallback {
public:
	StateColonEquals(String * const c) : StateAutoFallback(true, c){}
	void createToken(Automat* automat);
};

class StateEqualsColon: public State {
public:
	StateEqualsColon(String * const c) : State(false, c){}
	void createToken(Automat* automat);
	void processChar(const char&, Automat* automat);
};


class StateEqualsColonEquals: public StateAutoFallback {
public:
	StateEqualsColonEquals(String * const c) : StateAutoFallback(true, c){}
	void createToken(Automat* automat);
};

class StateColonAsterix: public State {
public:
	StateColonAsterix(String * const c) : State(false, c){}
	void createToken(Automat* automat);
	void processChar(const char&, Automat* automat);
};

class StateColonAsterixAsterix: public State {
public:
	StateColonAsterixAsterix(String * const c) : State(false, c){}
	void createToken(Automat* automat);
	void processChar(const char&, Automat* automat);
};

class StateColonAsterixAsterixColon: public StateAutoFallback {
public:
	StateColonAsterixAsterixColon(String * const c) : StateAutoFallback(true, c){}
	void createToken(Automat* automat);
};


#endif /* States_H_ */
