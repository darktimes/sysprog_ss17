/*
 * TokenType.h
 *
 *  Created on: 25 Oct 2016
 *      Author: fattum
 */

#pragma once

typedef enum e_TokenType {
	TokenUnknown,
	TokenIdentifier,
	TokenPlus,
	TokenMinus,
	TokenColon,
	TokenAsterisk,
	TokenLessThan,		// <
	TokenGreaterThan,	// >
	TokenEquals1,		// =
	TokenEquals2,		// :=
	TokenEquals3,		// =:=
	TokenExclamation,	// !
	TokenAnd,			// &&
	TokenSemicolon,
	TokenBracketOpen1,	// (
	TokenBracketClose1,	// )
	TokenBracketOpen2,	// {
	TokenBracketClose2,	// }
	TokenBracketOpen3,	// [
	TokenBracketClose3,	// ]
	TokenComment,
	TokenEOF,
	TokenSeparator,		// whitespace, \n, \t
	TokenLengthExceeded,
	TokenError,
	TokenInteger,
	TokenKeyWordIf,
	TokenKeyWordWhile,
	TokenKeyWordRead,
	TokenKeyWordWrite,
	TokenKeyWordElse,
	TokenKeyWordInt

} TokenType;

const char* tokenToString(TokenType type);

const char* wrapChar(const char& c);

