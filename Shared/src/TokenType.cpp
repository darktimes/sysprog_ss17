/*
 * TokenType.cpp
 *
 *  Created on: Jun 15, 2017
 *      Author: fattum
 */

#include "TokenType.h"

const char* tokenToString(TokenType type) {
	switch (type) {
	case TokenUnknown:
		return "Undefined";
	case TokenIdentifier:
		return "Identifier";
	case TokenInteger:
		return "Integer";
	case TokenKeyWordIf:
		return "If";
	case TokenKeyWordWhile:
		return "While";
	case TokenPlus:
		return "Plus";
	case TokenMinus:
		return "Minus";
	case TokenColon:
		return "Colon";
	case TokenAsterisk:
		return "Asterisk";
	case TokenLessThan:
		return "LessThan";
	case TokenGreaterThan:
		return "GreaterThan";
	case TokenEquals1:
		return "Equals1";
	case TokenEquals2:
		return "Equals2";
	case TokenEquals3:
		return "Equals3";
	case TokenExclamation:
		return "Exclamation";
	case TokenAnd:
		return "And";
	case TokenSemicolon:
		return "Semicolon";
	case TokenBracketOpen1:
		return "BracketOpen1";
	case TokenBracketClose1:
		return "BracketClose1";
	case TokenBracketOpen2:
		return "BracketOpen2";
	case TokenBracketClose2:
		return "BracketClose2";
	case TokenBracketOpen3:
		return "BracketOpen3";
	case TokenBracketClose3:
		return "BracketClose3";
	case TokenEOF:
		return "EOF";
	case TokenComment:
		return "Comment";
	case TokenSeparator:
		return "Separator";
	case TokenLengthExceeded:
		return "LengthExceeded";
	case TokenKeyWordRead:
			return "Read";
	case TokenKeyWordWrite:
			return "Write";
	case TokenKeyWordElse:
			return "Else";
	case TokenKeyWordInt:
			return "Int";
	default: return "error";
	}
}

const char* wrapChar(const char& c) {
	if (c == '\n') {
		return "\\n";
	} else if (c == '\t') {
		return "\\t";
	} else if (c == '\0') {
		return "EOF";
	} else {
		return &c;
	}
}

