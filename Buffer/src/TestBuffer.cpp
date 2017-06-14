#include <iostream>

#include "Buffer.h"

using namespace std;

int main(void) {

	Buffer* buffer = new Buffer("test.txt");

	while (!buffer->isEOF()) {
		char c = buffer->getChar();
		if (c == '\0') {
			cout<<"eof";
		} else if(c == ' ') {
			cout<<"wh_s";
		} else if(c == '\n'){
			cout<<"endl";
		} else {
			cout<<c;
		}
		cout<<", nr: "<<(int)c<<endl;
	}

	buffer->ungetChar(8);

	while (!buffer->isEOF()) {
			char c = buffer->getChar();
			if (c == '\0') {
				cout<<"eof";
			} else if(c == ' ') {
				cout<<"wh_s";
			} else if(c == '\n'){
				cout<<"endl";
			} else {
				cout<<c;
			}
			cout<<", nr: "<<(int)c<<endl;
		}
}

