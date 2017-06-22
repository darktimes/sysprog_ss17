/*
 * TokenType.h
 *
 *  Created on: 25 Oct 2016
 *      Author: fattum
 */

#pragma once

typedef enum e_TokenType {
	TokenUnknown,		// automat returns this when symbol (lexem) doesn't belong to language
	TokenIdentifier,	// letter (letter | digit)*
	TokenInteger,		// digit digit*
	TokenIf,			// if | IF
	TokenWhile,			// while | WHILE
	TokenPlus,			// +
	TokenMinus,			// -
	TokenColon,			// :
	TokenAsterisk,		// *
	TokenLessThan,		// <
	TokenGreaterThan,	// >
	TokenEquals1,		// =
	TokenEquals2,		// :=
	TokenEquals3,		// =:=
	TokenExclamation,	// !
	TokenAnd,			// &&
	TokenSemicolon,		// ;
	TokenBracketOpen1,	// (
	TokenBracketClose1,	// )
	TokenBracketOpen2,	// {
	TokenBracketClose2,	// }
	TokenBracketOpen3,	// [
	TokenBracketClose3,	// ]
	TokenComment,		// used by scanner to skip comments and set start position of next Token accordingly
	TokenEOF,		  	// returns at the end of the sequence
	TokenSeparator,		// whitespace, \n
	TokenLengthExceeded,	// if token was too long
	TokenError,
	TokenRead,
	TokenWrite,
	TokenElse
} TokenType;

const char* tokenToString(TokenType type);

const char* wrapChar(const char& c);

