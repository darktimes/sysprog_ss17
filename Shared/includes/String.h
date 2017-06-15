#pragma once

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

	char& operator[](int index) const;
	bool compare(char &c);
	bool compare(const String &s) const;
	String& operator=(const String&);
	String& operator+=(const String&);
	String& operator+=(const char&);

	friend const String operator+(const String&, const char&);
	friend const String operator+(const String&, const String&);
	operator const char*();

	int getSize() const;
	char* getStr();

};
