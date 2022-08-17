#ifndef STRING_H
#define STRING_H
#include<iostream>
using namespace std;
#include<fstream>
class String
{
private:
	friend istream& operator >> (istream&, String&);
	//friend ifstream& operator >> (ifstream&, String&);

	char* data;
	int size;

	int findLength(const char* str) const;
	bool findString(const char* str, const int index) const;
	void myMemCpy(void* dest, const void* src, int bytes);
	void myMemMove(void* dest, const void* src, int bytes);
	void strCopy(char* dest, const char* source);
	void swapChar(char& ch1, char& ch2);
	int logTen(int num);
public:
	String();
	String(const char);
	String(const char* str);
	String(const String&);
	~String();
	String& operator=(const String&);
	void shrink();
	char& operator [](const int);
	const char& operator [](const int index) const;
	bool operator ! ()const;
	int getLength() const;
	int getSize() const;
	int find(const String& subStr, const int start = 0) const;
	void insert(const int index, const String& subStr);
	void remove(const int index, const int = 1);
	int replace(const String& old, const String& newSubstr);
	void trimLeft();
	void trimRight();
	void trim();
	void makeUpper();
	void makeLower();
	void reverse();
	void reSize(int);
	int operator==(const String& s2) const;
	String left(const int);
	String right(const int);
	String operator +(const String&) const;
	void operator +=(const String&);
	String& operator=(const long long int);

	String& operator=(const double);

	explicit operator long long int()const;
	explicit operator double ()const;
	explicit operator bool()const;
	String operator()(const String&);
	String(String&&);
	String& operator=(String&&);
};

istream& operator >> (istream&, String&);
ostream& operator << (ostream&, const String&);
#endif // !STRING_H
