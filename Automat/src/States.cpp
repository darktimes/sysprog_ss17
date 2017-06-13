#include "States.h"
#include "Automat.h"
#include "String.h"
#include <iostream>

State::State(bool isAcceptable, const char& letter) : _isAcceptable(isAcceptable), _lexem(new String(letter)){

}

State::State(bool isAcceptable, String * const str) : _isAcceptable(isAcceptable), _lexem(new String(*str)) {

}

State::~State() {
	delete this->_lexem;
}

bool State::isAcceptable() {
	return _isAcceptable;
}

void State::fallback(const int& count, Automat* automat) {
	automat->getScanner()->ungetChar(count);
	if (count == 1) {

		createToken(automat);

	} else {
		automat->getLastFinalState()->createToken(automat);
	}
	automat->changeState(new StateInit());
}

//------------------------------------------------------------------------------------------------------------------------------------
// Utility functions
//------------------------------------------------------------------------------------------------------------------------------------

bool isDigit(const char& c) {
	return (int)c >= 48 && (int)c <= 57;
}

bool isCapital(const char& c) {
	return (int)c >= 65 && (int)c <= 90;
}

bool isLetter(const char& c) {
	return isCapital(c) || ((int)c >= 97 && (int)c <= 122);
}

bool isAcceptableSign(const char& c) {
	switch (c) {
		case '+': return true;
		case '-': return true;
		case ':': return true;
		case '*': return true;
		case '>': return true;
		case '<': return true;
		case '=': return true;
		case '!': return true;
		case '&': return true;
		case ';': return true;
		case '[': return true;
		case ']': return true;
		case '(': return true;
		case ')': return true;
		case '{': return true;
		case '}': return true;
	default: return false;
	}
}
//------------------------------------------------------------------------------------------------------------------------------------
// StateInit
//------------------------------------------------------------------------------------------------------------------------------------
void StateInit::processChar(const char& c, Automat* automat) {
	if (isDigit(c)) {
		automat->changeState(new StateInteger(c));
	} else if (isLetter(c)) {
		automat->changeState(new StateIdentifier(c));
	} else if (isAcceptableSign(c)) {
		if (c == ':') {
			automat->changeState(new StateColon(c));
		} else if (c == '=') {
			automat->changeState(new StateEquals(c));
		} else if (c == '&') {
			automat->changeState(new StateAmp(c));
		} else {
			automat->changeState(new StateSigns(c));
		}
	} else if (c == ' ' || c == '\n' || c == '\t')  {
		automat->changeState(new StateSeparator(c));
	} else if (c == '\0') {
		//automat->getScanner()->mkToken(TokenEOF, '\0');
		createToken(automat);
		automat->changeState(new StateFinished());
	} else {
		//adding single character on the empty string works wrong
		*_lexem = String(c);
		createToken(automat);
		automat->changeState(new StateInit());
	}
}

void StateInit::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenEOF, _lexem);
}
//------------------------------------------------------------------------------------------------------------------------------------
// StateFinished
//------------------------------------------------------------------------------------------------------------------------------------
void StateFinished::processChar(const char& c, Automat* automat) {
		//throw exception or something
}

void StateFinished::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenEOF, '\0');
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateIdentifier
//------------------------------------------------------------------------------------------------------------------------------------
void StateIdentifier::processChar(const char& c, Automat* automat) {
	if (isDigit(c) | isLetter(c)) {
		*(_lexem) += c;
	} else {
		fallback(1, automat);
	}
}

void StateIdentifier::createToken(Automat* automat) {
	if (_lexem->getSize() <= MAX_CHAR_COUNT) {
		automat->getScanner()->mkToken(TokenIdentifier, _lexem);
	} else {
		//should be _lexem + $?
		automat->getScanner()->mkToken(TokenLengthExceeded, new String("$"));
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateInteger
//------------------------------------------------------------------------------------------------------------------------------------

void StateInteger::processChar(const char& c, Automat* automat) {
	if (isDigit(c)) {
		*(_lexem) += c;
	} else {
		fallback(1, automat);
	}
}

void StateInteger::createToken(Automat* automat) {
	if (_lexem->getSize() <= MAX_CHAR_COUNT) {
		automat->getScanner()->mkToken(TokenInteger, _lexem);
	} else {
		automat->getScanner()->mkToken(TokenLengthExceeded, new String("$"));
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateFallback
//------------------------------------------------------------------------------------------------------------------------------------
void StateAutoFallback::processChar(const char&, Automat* automat) {
	fallback(1, automat);
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateSigns
//------------------------------------------------------------------------------------------------------------------------------------

void StateSigns::createToken(Automat* automat) {
	char c = *(_lexem)[0];
	switch (c) {
		case '+' : automat->getScanner()->mkToken(TokenPlus, _lexem); break;
		case '-' : automat->getScanner()->mkToken(TokenMinus, _lexem); break;
		case '*' : automat->getScanner()->mkToken(TokenAsterisk, _lexem); break;
		case '!' : automat->getScanner()->mkToken(TokenExclamation, _lexem); break;
		case '(' : automat->getScanner()->mkToken(TokenBracketOpen1, _lexem); break;
		case ')' : automat->getScanner()->mkToken(TokenBracketClose1, _lexem); break;
		case '{' : automat->getScanner()->mkToken(TokenBracketOpen2, _lexem); break;
		case '}' : automat->getScanner()->mkToken(TokenBracketClose2, _lexem); break;
		case '[' : automat->getScanner()->mkToken(TokenBracketOpen3, _lexem); break;
		case ']' : automat->getScanner()->mkToken(TokenBracketClose3, _lexem); break;
		case ';' : automat->getScanner()->mkToken(TokenSemicolon, _lexem); break;
		case '>' : automat->getScanner()->mkToken(TokenGreaterThan, _lexem); break;
		case '<' : automat->getScanner()->mkToken(TokenLessThan, _lexem); break;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateColon
//------------------------------------------------------------------------------------------------------------------------------------
void StateColon::processChar(const char& c, Automat* automat) {
	if (c == '=') {
		//*(_lexem) += c;
		automat->changeState(new StateColonEquals(new String(*(_lexem) + c)));
	} else if (c == '*') {
		//*(_lexem) += c;
		automat->changeState(new StateColonAsterix(new String(*(_lexem) + c)));
	} else {
		fallback(1, automat);
	}
}

void StateColon::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenColon, _lexem);
}
//------------------------------------------------------------------------------------------------------------------------------------
// StateSeparator
//------------------------------------------------------------------------------------------------------------------------------------
void StateSeparator::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenSeparator, _lexem);
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateColonEquals
//------------------------------------------------------------------------------------------------------------------------------------
void StateColonEquals::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenEquals2, _lexem);
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateColonAstrix
//------------------------------------------------------------------------------------------------------------------------------------
void StateColonAsterix::processChar(const char& c, Automat* automat) {
	if (c == '*') {
		automat->changeState(new StateColonAsterixAsterix(new String(*(_lexem) + c)));
	} else if (c != '\0'){
		*(_lexem) += c;
	} else {
		fallback(1, automat);
	}
}

void StateColonAsterix::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenComment, _lexem);
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateColonAstrixAsterix
//------------------------------------------------------------------------------------------------------------------------------------
void StateColonAsterixAsterix::processChar(const char& c, Automat* automat) {
	if (c == ':') {
		automat->changeState(new StateColonAsterixAsterixColon(new String(*(_lexem) + c)));
	} else if (c != '\0'){
		automat->changeState(new StateColonAsterix(new String(*(_lexem) + c)));
	} else {
		fallback(1, automat);
	}
}

void StateColonAsterixAsterix::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenComment, _lexem);
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateColonAstrixAsterixColon
//------------------------------------------------------------------------------------------------------------------------------------
void StateColonAsterixAsterixColon::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenComment, _lexem);
}


//------------------------------------------------------------------------------------------------------------------------------------
// StateEquals
//------------------------------------------------------------------------------------------------------------------------------------
void StateEquals::processChar(const char& c, Automat* automat) {
	if (c == ':') {
		//*(_lexem) += c;
		automat->changeState(new StateEqualsColon(new String(*(_lexem) + c)));
	} else {
		fallback(1, automat);
	}
}

void StateEquals::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenEquals1, _lexem);
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateEqualsColon
//------------------------------------------------------------------------------------------------------------------------------------
void StateEqualsColon::processChar(const char& c, Automat* automat) {
	if (c == '=') {
		//*(_lexem) += c;
		automat->changeState(new StateEqualsColonEquals(new String(*(_lexem) + c)));
	} else {
		fallback(2, automat);
	}
}

void StateEqualsColon::createToken(Automat* automat) {
	//is actually a stub
	automat->getScanner()->mkToken(TokenEquals1, _lexem);
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateEqualsColonEquals
//------------------------------------------------------------------------------------------------------------------------------------
void StateEqualsColonEquals::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenEquals3, _lexem);
}

//------------------------------------------------------------------------------------------------------------------------------------
// StateAmp
//------------------------------------------------------------------------------------------------------------------------------------
void StateAmp::processChar(const char& c, Automat* automat) {
	if (c == '&') {
		//*(_lexem) += c;
		automat->changeState(new StateAmpAmp(new String(*(_lexem) + c)));
	} else {
		fallback(1, automat);
	}
}

void StateAmp::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenUnknown, _lexem);
}
//------------------------------------------------------------------------------------------------------------------------------------
// StateAmpAmp
//------------------------------------------------------------------------------------------------------------------------------------
void StateAmpAmp::createToken(Automat* automat) {
	automat->getScanner()->mkToken(TokenAnd, _lexem);
}


