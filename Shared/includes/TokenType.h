#pragma once

#include "String.h"

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

typedef enum e_NodeType {
	NodeUnknown,
	NodeProg,
	NodeDecls,
	NodeDecl,
	NodeArray,
	NodeStatements,
	NodeStatement,
	NodeExp,
	NodeExp2,
	NodeIndex,
	NodeOpExp,
	NodeOp
} NodeType;

typedef enum e_NodeCheckType {
	NotInited,
	IntType,
	IntArrayType,
	ArrayType,
	NoType,
	ErrorType,
	OpPlus,
	OpMinus,
	OpMult,
	OpDiv,
	OpLess,
	OpGreater,
	OpEqual,
	OpUnequal,
	OpAnd
} NodeCheckType;


const char* tokenToString(TokenType type);

const char* wrapChar(const char& c);

