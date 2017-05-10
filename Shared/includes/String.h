/*
 * String.h
 *
 *  Created on: 1 Nov 2016
 *      Author: David Seifried
 */

#ifndef SHARED_SRC_STRING_H_
#define SHARED_SRC_STRING_H_

/*
 *
 */
class String {
private:
	int size;
	char* str;
public:
	String();
	String(char c);
	String(const char *);
	String(const String&);
	~String();

	char& operator[](int index);
	bool compare(char &c);
	bool compare(String &s);
	String& operator=(const String&);
	String& operator+=(const String&);
	String& operator+=(const char&);

	friend const String operator+(const String&, const char&);
	operator const char*();

	int getSize();


};

#endif
