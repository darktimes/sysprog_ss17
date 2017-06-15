#include "String.h"
#include <iostream>

String::String() {
	size = 1;
	str = new char[1];
	str[0] = '\0';
}

String::String(char c) {
	size = 2;
	str = new char[2];
	str[0] = c;
	str[1] = '\0';
}

String::String(const char* s) {
	size = 1;
	int i = 0;
	while (s[i++] != '\0') {
		size++;
	}

	str = new char[size];
	for (int j = 0; j < size; j++) {
		str[j] = s[j];
	}
}

String::String(const String& s) {
	this->size = s.size;
	str = new char[size + 1];
	int i;
	for (i = 0; i < size + 1; i++) {
		str[i] = s.str[i];
	}
}

String::~String() {
	delete[] str;
}

char& String::operator[](int index) const {
	if ((index <= size) && (index >= 0)) {
		return str[index];
	}
	return str[size];
}


bool String::compare(char &c){
	if (this->size > 1){
		return false;
	} else if (this->operator [](0) == c) {
		return true;
	} else {
		return false;
	}
}

//compare with a string
bool String::compare(const String &s) const{
	if (this->size != s.size){
		return false;
	} else {
		for (int i = 0; i < s.size; i++){
			if (this->operator [](i) != s[i]){
				return false;
			}
		}
	} return true;
}

String& String::operator=(const String& s) {
	char* tempStr = new char[s.size];
	delete[] str;
	this->str = tempStr;
	this->size = s.size;
	int i;
	for (i = 0; i < size + 1; i++) {
		str[i] = s.str[i];
	}
	return *this;
}
// String concatenation via '+=' operator
String& String::operator+=(const String& s) {
	int newSize = this->size + s.size - 1;
	char* tempStr = new char[newSize];
	for (int i = 0; i < this->size - 1; i++) {
		tempStr[i] = str[i];
	}
	for (int j = 0; j < s.size; j++) {
		tempStr[j + size - 1] = s.str[j];
	}
	delete[] str;
	this->size = newSize;
	str = tempStr;
	return *this;
}

String& String::operator+=(const char& c) {
	String temp = String(c);
	return (*this+=temp);
}

const String operator+(const String& left, const char& right) {
	String result = String(left);
	return result += right;
}

const String operator+(const String& left, const String& right) {
	String result = String(left);
	return result += right;
}

String::operator const char*() {
	return this->str;
}

int String::getSize() const{
	return size;
}
char* String::getStr(){
	return str;
}
