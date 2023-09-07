#pragma once
#include <stdlib.h>
#include <string>

class MyString
{
private:
	unsigned int size_;
	unsigned int capacity_;
	char *str;

public:
	//constructors
	MyString(); //default
	MyString(const char *str); //array
	MyString(const std::initializer_list<char> &list); //initializer list
	MyString(std::string s); //std::string constructor
	MyString(const char *str, unsigned int count); //init class with count characters of  “char string”
	MyString(unsigned int count, const char c); //init class with count of characters
	MyString(const MyString &other); //copy constructor
	~MyString(); //destructor

	//operators
	MyString operator + (const MyString &other); //concatenate with Mystring
	MyString operator + (const char *string); //concatenate with char array
	MyString operator + (std::string s); //concatenate with std::string
	MyString operator += (const char *string); //assignment concatenate with char array
	MyString operator += (std::string s); //assignment concatenate with std::string
	MyString operator = (MyString &&other);
	MyString operator = (const char *string); //char string assignment
	MyString operator = (std::string s); //std::string assignment
	MyString operator = (const char c); //char assignment
	char operator[] (unsigned int index); //index operator

	//lexicographically comparing
	bool operator > (const MyString &other);
	bool operator < (const MyString &other);
	bool operator >= (const MyString &other);
	bool operator <= (const MyString &other);
	bool operator != (const MyString &other);
	bool operator == (const MyString &other);

	char* c_str(); //return a pointer to null-terminated character array
	char* data(); //return a pointer to array data that not required to be null-terminated
	unsigned int size(); //return the number of char elements in string
	unsigned int length(); //same as size
	unsigned int capacity(); //return the current amount of allocated memory for array
	bool empty(); //true if string is empty
	void shrink_to_fit();
	void clear();

	//io operators
	friend std::ostream& operator<< (std::ostream&, MyString);
	friend std::istream& operator>> (std::istream&, MyString&);

	//insert
	MyString insert(unsigned int index, unsigned int count, const char c); //insert count of char in index position
	MyString insert(unsigned int index, const char* string); //insert null - terminated char string at index position
	MyString insert(unsigned int index, const char* string, unsigned int count); //insert count of null - terminated char string at index position
	MyString insert(unsigned int index, std::string s);	//insert std::string at index position
	MyString insert(unsigned int index, std::string s, unsigned int count); //insert count of std::string at index position

	MyString erase(unsigned int index, unsigned int count); //erase count of char at index position
	MyString replace(unsigned int index, unsigned int count, const char *string); //replace a count of char at index by “string”
	MyString replace(unsigned int index, unsigned int count, std::string s); //replace a count of char at index by std::string
	MyString substr(unsigned int index); //return a substring starts with index position
	MyString substr(unsigned int index, unsigned int count); //return a count of substring’s char starts with index position

	//append
	MyString append(unsigned int count, char c); //append count of char
	MyString append(const char *string); //append null-terminated char string
	MyString append(const char *string, unsigned int index, unsigned int count); //append a count of null-terminated char string by index position
	MyString append(std::string s); //append std:: string
	MyString append(std::string s, unsigned int index, unsigned int count); //append a count of std:: string by index position

	//find
	unsigned int find(const char *string); //if founded return the index of substring
	unsigned int find(const char *string, unsigned int index); //same as find(“string”) but search starts from index position
	unsigned int find(std::string s); //if founded return the index of substring
	unsigned int find(std::string s, unsigned int index); //same as find(“string”) but search starts from index position

};
