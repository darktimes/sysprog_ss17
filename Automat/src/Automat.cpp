/*
 * Automat.cpp
 *
 */

#include "../includes/Automat.h"
#include <iostream>


Automat::Automat(IScanner* iScanner){
	this->scanner = iScanner;
	this->currentState = new StateInit();
	this->lastFinalState = 0;
}

Automat::~Automat() {
	if (this->lastFinalState != this->currentState) {
		delete this->lastFinalState;
	}
	delete this->currentState;
}

void Automat::process(const char& c) {
	this->currentState->processChar(c, this);
}

IScanner* Automat::getScanner() const {
	return this->scanner;
}

void Automat::changeState(State* state) {
	if (currentState->isAcceptable()) {
		delete lastFinalState;
		lastFinalState = currentState;
		currentState = state;
	} else {
		delete currentState;
		currentState = state;
	}
}

State* Automat::getLastFinalState() const{
	return this->lastFinalState;
}
