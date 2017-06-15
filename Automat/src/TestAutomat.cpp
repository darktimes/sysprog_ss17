#include "Automat.h"
#include "iostream"
#include "String.h"

const char* testString = "nrwejr32[ßewrr=(015_abc hey!2 :*huuuge comment*:\0";


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


	void ungetChar(int count) {
		readPos-=count;
	}
};

int main (int argc, char* argv[]) {
	IScannerStub* scanner = new IScannerStub();
	Automat* automat = new Automat(scanner);
	String* abc = new String("aaa234\n\nkorrekt\nein Identifier aaa234\n\nxxxxxx\n\n1234bbb\n\nkorrekt\nein Integer 1234 und ein Identifier bbb:**************: :*********");
	//String* abc = new String("aaa234");
	for (; scanner->readPos < abc->getSize(); scanner->readPos++) {
		//std::cout<<"Processing char["<<scanner->readPos<<"]"<<std::endl;
		automat->process((*abc)[scanner->readPos]);
	}
}


