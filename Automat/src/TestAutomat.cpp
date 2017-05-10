#include "Automat.h"
#include "iostream"
#include "String.h"

const char* testString = "nrwejr32[ßewrr=(015_abc hey!2 :*huuuge comment*:\0";

const char* tokenToString(TokenType type) {
	switch (type) {
	case TokenUnknown:
		return "Undefined";
	case TokenIdentifier:
		return "Identifier";
	case TokenInteger:
		return "Integer";
	case TokenIf:
		return "If";
	case TokenWhile:
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
		return "Error: LengthExceeded";
	default: return "error";
	}
}

class IScannerStub: public IScanner {
public:
	int readPos;

	IScannerStub() {
		readPos = 0;
	}
	virtual ~IScannerStub() {
	}

	void mkToken(TokenType tType, String  *  lexem) {
		String abc = *lexem;
		if (abc[0] == '\n') {
			std::cout<<"TokenType: "<<tokenToString(tType)<<", lexem: \'"<<"\\n"<<"\'"<<std::endl;
		} else {
			std::cout<<"TokenType: "<<tokenToString(tType)<<", lexem: \'"<<abc<<"\'"<<std::endl;
		}
	}

	void mkToken(TokenType tType, const char& c) {
		if (c != '\n') {
			std::cout<<"TokenType: "<<tokenToString(tType)<<", symbol: \'"<<c<<"\'"<<std::endl;
		} else {
			std::cout<<"TokenType: "<<tokenToString(tType)<<", symbol: \'"<<"\\n"<<"\'"<<std::endl;
		}
	}

	void ungetChar(int count) {
		readPos-=count;
	}
};

int main (int argc, char* argv[]) {
	IScannerStub* scanner = new IScannerStub();
	Automat* automat = new Automat(scanner);
	String* abc = new String("aaa234\n\nkorrekt\nein Identifier aaa234\n\nxxxxxx\n\n1234bbb\n\nkorrekt\nein Integer 1234 und ein Identifier bbb:**************: :*********");
	*(abc) += '\0';

	for (; scanner->readPos < abc->getSize(); scanner->readPos++) {
		automat->process((*abc)[scanner->readPos]);
	}
}


