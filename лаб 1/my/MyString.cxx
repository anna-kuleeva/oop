#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "MyString.h"
#include <string.h>
#include <string>

MyString::MyString()
{
	//std::cout << "Construct: " << this << std::endl;
	this->str = NULL;
	this->size_ = 0;
	this->capacity_ = 0;
}

MyString::MyString(const char *str)
{
	//std::cout << "Construct: " << this << std::endl;
	this->size_ = strlen(str);
	this->capacity_ = this->size_ + 1;
	this->str = new char[this->size_ + 1];
	strncpy(this->str, str, this->size_);
	this->str[this->size_] = '\0';
}

MyString::MyString(const std::initializer_list<char> &list)
{
	unsigned get_size = list.size();
	this->str = new char[get_size + 1];
	this->size_ = get_size;
	this->capacity_ = get_size + 1;
	unsigned int i = 0;
	for (auto &element : list)
	{
		this->str[i] = element;
		++i;
	}
	this->str[i] = '\0';
}

MyString::MyString(std::string s)
{
	//std::cout << "Construct: " << this << std::endl;
	this->size_ = s.size();
	this->capacity_ = this->size_ + 1;
	this->str = new char[this->capacity_];
	unsigned int i = 0;
	for (; i < this->size_; i++)
		this->str[i] = s[i];
	this->str[i] = '\0';
}

MyString::MyString(const char *str, unsigned int count)
{
	this->str = new char[count + 1];
	this->size_ = count;
	this->capacity_ = count + 1;
	strncpy(this->str, str, count);
	this->str[count] = '\0';
}

MyString::MyString(unsigned int count, const char c)
{
	//std::cout << "Construct: " << this << std::endl;
	this->str = new char[count + 1];
	unsigned int i = 0;
	for (; i < count; i++)
		this->str[i] = c;
	this->str[i] = '\0';
	this->size_ = count;
	this->capacity_ = count + 1;
}

MyString::MyString(const MyString &other)
{
	//std::cout << "Construct: " << this << "; From: " << &other << std::endl;
	this->size_ = other.size_;
	this->capacity_ = other.capacity_;
	if (this->capacity_ == 0)
	{
		this->str = NULL;
	}
	else {
		this->str = new char[other.capacity_];
		strncpy(this->str, other.str, this->size_);
		this->str[this->size_] = '\0';
	}
}

MyString::~MyString()
{
	//std::cout << "Destruct: " << this << std::endl;
	//if (this->str[0] == '\0') return;
	delete[] this->str;
}

MyString MyString::operator + (const MyString &other)
{
	if (other.str == NULL) return *this;
	unsigned int new_size = this->size_ + other.size_;
	MyString new_string;
	new_string.str = new char[new_size + 1];
	new_string.size_ = new_size;
	new_string.capacity_ = new_size + 1;
	unsigned int i = 0;
	for (; i < this->size_; i++)
	{
		new_string.str[i] = this->str[i];
	}
	for (unsigned int j = 0; j < other.size_; j++, i++)
	{
		new_string.str[i] = other.str[j];
	}
	new_string.str[i] = '\0';
	return new_string;
}

MyString MyString::operator + (const char *string)
{
	unsigned int new_size = this->size_ + strlen(string);
	MyString new_string;
	new_string.str = new char[new_size + 1];
	new_string.size_ = new_size;
	new_string.capacity_ = new_size + 1;
	unsigned int i = 0;
	for (; i < this->size_; i++)
	{
		new_string.str[i] = this->str[i];
	}
	for (unsigned int j = 0; j < strlen(string); j++, i++)
	{
		new_string.str[i] = string[j];
	}
	new_string.str[i] = '\0';
	return new_string;
}

MyString MyString::operator + (std::string s)
{
	unsigned int new_size = this->size_ + s.size();
	MyString new_string;
	new_string.str = new char[new_size + 1];
	new_string.size_ = new_size;
	new_string.capacity_ = new_size + 1;
	unsigned int i = 0;
	for (; i < this->size_; i++)
	{
		new_string.str[i] = this->str[i];
	}
	for (unsigned int j = 0; j < s.size(); j++, i++)
	{
		new_string.str[i] = s[j];
	}
	new_string.str[i] = '\0';
	return new_string;
}

//new
MyString MyString::operator += (const char *string)
{
	if (this->capacity_ >= this->size_ + strlen(string))
	{
		for (unsigned int i = this->size_, j = 0; j < strlen(string); j++, i++)
		{
			this->str[i] = string[j];
		}
		return *this;
	}
	unsigned int new_size = this->size_ + strlen(string);
	unsigned int first_size = this->size_;
	char *buf = new char[this->size_];
	memcpy(buf, this->str, this->size_);
	//delete[] this->str;
	this->str = new char[new_size + 1];
	this->capacity_ = new_size + 1;
	this->size_ = new_size;
	unsigned int i = first_size, j = 0;

	memcpy(this->str, buf, this->size_);
	for (; i < new_size; j++, i++)
	{
		this->str[i] = string[j];
	}
	this->str[i] = '\0';
	delete[] buf;
	return *this;
}

//new
MyString MyString::operator += (std::string s)
{
	if (this->capacity_ >= this->size_ + s.size())
	{
		for (unsigned int i = this->size_, j = 0; j < s.size(); j++, i++)
		{
			this->str[i] = s[j];
		}
		return *this;
	}
	unsigned int new_size = this->size_ + s.size();
	unsigned int first_size = this->size_;
	char *buf = new char[this->size_];
	memcpy(buf, this->str, this->size_);
	//delete[] this->str;
	this->str = new char[new_size + 1];
	this->capacity_ = new_size + 1;
	this->size_ = new_size;
	unsigned int i = first_size, j = 0;

	memcpy(this->str, buf, this->size_);
	for (; i < new_size; j++, i++)
	{
		this->str[i] = s[j];
	}
	this->str[i] = '\0';
	delete[] buf;
	return *this;
}

MyString MyString::operator = (MyString &&other)
{
	this->operator = (other.c_str());
	return *this;
}

//new
MyString MyString::operator = (const char *string)
{
	unsigned int new_size = strlen(string);
	if (this->capacity_ < strlen(string))
	{
		delete[] this->str;
		this->str = new char[new_size + 1];
		this->capacity_ = new_size + 1;
		this->size_ = new_size;
	}
	memcpy(this->str, string, strlen(string));
	this->str[new_size] = '\0';
	return *this;
}

//new
MyString MyString::operator = (std::string s) //std::string assignment
{
	return *this = s.c_str();
}

//new
MyString MyString::operator = (const char c) //char assignment
{
	if (this->capacity_ < 2)
	{
		delete[] this->str;
		this->str = new char[2];
		this->capacity_ = 2;
	}
	this->size_ = 1;
	this->str[0] = c;
	this->str[1] = '\0';
	return *this;
}

char MyString::operator[] (unsigned int index) //index operator
{
	if (this->size_ >= index)
	{
		return this->str[index];
	}
	else {
		std::cout << "Error!" << std::endl;
		return 1;
	}
}

//all lexic. comp are new
bool MyString::operator > (const MyString &other)
{
	unsigned int i = 0;
	for (; (this->str[i] != this->str[this->size_]) && (other.str[i] != other.str[other.size_]); i++)
	{
		if (this->str[i] > other.str[i]) return true;
		if (this->str[i] < other.str[i]) return false;
	}
	return (this->str[i] == this->str[this->size_]) && (other.str[i] != other.str[other.size_]);
}

bool MyString::operator < (const MyString &other)
{
	return !(this->str > other.str);
}

bool MyString::operator >= (const MyString &other)
{
	if (this->str > other.str || this->str == other.str)
		return true;
	else
		return false;
}

bool MyString::operator <= (const MyString &other)
{
	if (this->str < other.str || this->str == other.str)
		return true;
	else
		return false;
}

bool MyString::operator != (const MyString &other)
{
	if (this->size_ != other.size_)
	{
		std::cout << "Size of strings is different" << std::endl;
		return true;
	}
	else
	{
		for (unsigned int i = 0; i < this->size_; i++)
		{
			if (this->str[i] == other.str[i]) continue;
			else
			{
				std::cout << "Contents of strings is different" << std::endl;
				return true;
			}
		}
		return false;
	}
}

bool MyString::operator == (const MyString &other)
{
	return !(this->str != other.str);
}

char* MyString::c_str()
{
	return this->str;
}

char* MyString::data()
{
	return this->str;
}

unsigned int MyString::size()
{
	return this->size_;
}

unsigned int MyString::length()
{
	return size();
}

unsigned int MyString::capacity()
{
	return this->capacity_;
}

bool MyString::empty()
{
	return (this->size_ == 0);
}

//new
void MyString::shrink_to_fit()
{
	this->capacity_ = this->size_ + 1;
	char *buf = new char[this->size_];
	memcpy(buf, this->str, this->size_);
	delete[] this->str;
	this->str = new char[this->capacity_];
	memcpy(this->str, buf, this->capacity_);
}

void MyString::clear()
{
	this->size_ = 0;
	for (unsigned int i = 0; i < this->capacity_; i++)
	{
		this->str[i] = 0;
	}
}

std::ostream& operator << (std::ostream& out, MyString tmp)
{
	if (tmp.size_ == 0) out << "";
	else out << tmp.str;
	return out;
}

std::istream& operator >> (std::istream& in, MyString& tmp)
{
	while (1)
	{
		unsigned int i = 0;
		char *buf = new char[1024];
		for (; i < 1024; i++)
		{
			buf[i] = in.get();
			if (buf[i] == '\n')
			{
				buf[i] = '\0';
				break;
			}
		}

		if (i < 1024)
		{
			tmp.str = new char[i];
			tmp.str = buf;
			tmp.size_ = i - 1;
			tmp.capacity_ = i;
			break;
		}
		else tmp.str += *buf;
	}
	/*tmp.str = new char[1024];
	in.getline(tmp.str, 1024, '\n');

	size_t new_size = tmp.length();
	tmp.str = (char*)realloc(tmp.str, (new_size + 1) * sizeof(char));
	tmp.str[new_size] = '\0';*/
	return in;
}

//new
MyString MyString::insert(unsigned int index, unsigned int count, char c)
{
	char *buf = new char[count];
	for (unsigned int i = 0; i < count; i++)
	{
		buf[i] = c;
	}
	buf[count] = '\0';
	//delete[] buf;
	return insert(index, buf, count);
}

MyString MyString::insert(unsigned int index, const char* string)
{
	return insert(index, string, strlen(string));
}

//new
MyString MyString::insert(unsigned int index, const char* string, unsigned int count)
{
	unsigned int i = index, j = 0;
	char *buf = new char[this->size_];
	memcpy(buf, this->str, this->size_);
	unsigned int new_size = this->size_ + count;
	unsigned int old_cap = this->capacity_;
	this->capacity_ = new_size + 1;
	this->size_ = new_size;
	if (old_cap <= this->size_ + count)
	{
		unsigned int first_size = this->size_;
		this->str = new char[new_size + 1];
		memcpy(this->str, buf, index);
	}
	for (; j < count; i++, j++)
	{
		this->str[i] = string[j];
	}
	for (j = index; i < new_size; j++, i++)
	{
		this->str[i] = buf[j];
	}
	this->str[i] = '\0';
	delete[] buf;
	return *this;
}

MyString MyString::insert(unsigned int index, std::string s)
{
	return insert(index, s, s.size());
}

//new
MyString MyString::insert(unsigned int index, std::string s, unsigned int count) //c_str() ->
{
	const char *buf = s.c_str();
	//delete[] buf;
	return insert(index, buf, count);
}

MyString MyString::erase(unsigned int index, unsigned int count)
{
	unsigned int next_index = index + count;
	for (unsigned int i = index, j = next_index; j < this->capacity_; i++, j++)
	{
		this->str[i] = this->str[j];
		if (this->str[j] == '\0') break;
	}
	return *this;
}

MyString MyString::replace(unsigned int index, unsigned int count, const char *string)
{
	this->erase(index, count);
	this->insert(index, string);
	return *this;
}

MyString MyString::replace(unsigned int index, unsigned int count, std::string s)
{
	this->erase(index, count);
	this->insert(index, s);
	return *this;
}

//new
MyString MyString::substr(unsigned int index)
{
	MyString new_str(&str[index]);
	return new_str;
	// new_str;
}

//new
MyString MyString::substr(unsigned int index, unsigned int count)
{
	MyString new_str(&str[index], count);
	return new_str;
}

MyString MyString::append(unsigned int count, char c)
{
	return this->insert(this->size_, count, c);
}

MyString MyString::append(const char *string)
{
	return this->insert(this->size_, string);
}

MyString MyString::append(const char *string, unsigned int index, unsigned int count)
{
	return this->insert(index, string, count);
}

MyString MyString::append(std::string s)
{
	return this->insert(this->size_, s);
}

MyString MyString::append(std::string s, unsigned int index, unsigned int count)
{
	return this->insert(index, s, count);
}

unsigned int MyString::find(const char *string)
{
	unsigned int r = this->find(string, 0);
	return r;
}

unsigned int MyString::find(const char *string, unsigned int index)
{
	if (strlen(string) > this->size_)
	{
		std::cout << "No such substr" << std::endl;
		return 0;
	}

	unsigned int t;
	bool flag = false;
	for (unsigned int i = index, j = 0; i < this->size_; i++)
	{
		if (this->str[i] == string[j])
		{
			flag = true;
			j++;
			t = i;
		}
		else {
			flag = false;
			j = 0;
		}
		if (j == strlen(string)) break;
	}
	if (flag) return t + 1 - strlen(string);
	else {
		std::cout << "No such substr" << std::endl;
		return 0;
	}
}

unsigned int MyString::find(std::string s)
{
	unsigned int r = this->find(s, 0);
	return r;
}

unsigned int MyString::find(std::string s, unsigned int index)
{
	if (s.size() > this->size_)
	{
		std::cout << "No such substr" << std::endl;
		return 0;
	}

	unsigned int t;
	bool flag = false;
	for (unsigned int i = index, j = 0; i < this->size_; i++)
	{
		if (this->str[i] == s[j])
		{
			flag = true;
			j++;
			t = i;
		}
		else {
			flag = false;
			j = 0;
		}
		if (j == s.size()) break;
	}
	if (flag) return t + 1 - s.size();
	else {
		std::cout << "No such substr" << std::endl;
		return 0;
	}
}
