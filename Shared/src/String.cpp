#include "../includes/String.h"
// Default constructor (own implementation)
String::String() {
	size = 0;
	str = new char[1];
	str[0] = '\0';
}
// Constructor for 1 parameter of type char
String::String(char c) {
	size = 1;
	str = new char[2];
	str[0] = c;
	str[1] = '\0';
}
// Constructor for 1 parameter of type const char* (pointing to a string constant)
String::String(const char* s) {
	// Get size of string
	size = 1;
	int i;
	for (i = 0; s[i] != '\0'; i++) {
		size++;
	}

	// Copy string which was passed via parameter to new char array (private pointer)
	str = new char[size];
	for (int j = 0; j < size; j++) {
		str[j] = s[j];
	}
}
// Constructor with parameter via object of same class, & = passing by reference
String::String(const String& s) {
	this->size = s.size;
	str = new char[size + 1]; // new can throw exceptions
	int i;
	for (i = 0; i < size + 1; i++) {
		str[i] = s.str[i];
	}
}
// Destructor
String::~String() {
	delete[] str; // Free memory all elements (in this case of type char) directly following the pointer address
}
// Access array via '[]' operator
char& String::operator[](int index) const {
	if ((index <= size) && (index >= 0)) {
		return str[index];
	}
	return str[size];
}

//compare with a char
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
				break;
			}
		}
	} return true;
}

// Assign String via '=' operator
String& String::operator=(const String& s) {
	char* tempStr = new char[s.size + 1]; // new can throw exceptions --> prevent memory leak
	delete[] str; // free currently used memory for string
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
	int newSize = this->size + s.size;
	char* tempStr = new char[newSize + 1];
	int i;
	for (i = 0; i < this->size; i++) { // First null terminator is not copied
		tempStr[i] = str[i];
	}
	int j = 0;
	for (i = this->size; i < newSize + 1; i++) { // Second null terminator is copied
		tempStr[i] = s.str[j];
		j++;
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

String::operator const char*() {
	return this->str;
}

int String::getSize() const{
	return size;
}
char* String::getStr(){
	return str;
}
