#define WIN32_LEAN_AND_MEAN

#include <ostream>
#include <istream>
#include <iostream>

#include "MyString.h"

MyString::MyString() {
    string_ = new char[1];
    string_[0] = 0;
    capacity_ = 1;
    length_ = 0;
}

MyString::MyString(const MyString& to_copy) {
    string_ = new char[to_copy.length() + 1];

    for (size_t i = 0; i < to_copy.length() + 1; ++i) {
        string_[i] = to_copy[i];
    }

    capacity_ = to_copy.length() + 1;
    length_ = to_copy.length();
}

MyString::MyString(const char* array) {
    MyString new_string;
    new_string = array;
    *this = new_string;
}

MyString::MyString(const char* array, size_t count) {
    string_ = new char[count + 1];

    for (size_t i = 0; i < count; ++i) {
        string_[i] = array[i];
    }

    string_[count] = 0;

    capacity_ = count + 1;
    length_ = count;
}

MyString::MyString(size_t count, char character) {
    string_ = new char[count + 1];

    for (size_t i = 0; i < count; ++i) {
        string_[i] = character;
    }

    string_[count] = 0;

    capacity_ = count + 1;
    length_ = count;
}

MyString::MyString(const std::string& string) {
    MyString new_string;
    new_string = string;
    *this = new_string;
}

MyString::~MyString() {
    delete[] string_;
}

MyString MyString::operator+(const MyString& second) const {
    MyString new_string;

    new_string.length_ = this->length_ + second.length_;
    new_string.capacity_ = new_string.length_ + 1;
    new_string.string_ = new char[new_string.capacity_]();
    new_string.string_[new_string.length_] = 0;

    size_t i;

    for (i = 0; i < length_; ++i) {
        new_string.string_[i] = string_[i];
    }

    for (size_t j = 0; j < second.length_; ++j) {
        new_string.string_[i + j] = second.string_[j];
    }

    return new_string;
}

MyString MyString::operator+(char* second) const {
    MyString new_string(second);
    MyString old_string(string_);
    return old_string + new_string;
}

MyString MyString::operator+(const std::string& second) const {
    MyString new_string(second);
    MyString old_string(string_);
    return old_string + new_string;
}

MyString MyString::operator+=(const char* second) {
    size_t second_length = 0;
    size_t i = 0;

    while (second[i++] != 0) {
        ++second_length;
    }

    if (capacity_ - length_ > second_length) {
        for (i = 0; i < second_length; ++i) {
            string_[length_ + i] = second[i];
        }

        length_ += second_length;
    }
    else {
        auto tmp = new char[length_ + 1];

        for (i = 0; i < length_; ++i) {
            tmp[i] = string_[i];
        }

        tmp[length_] = 0;

        delete[] string_;
        string_ = new char[length_ + second_length + 1];

        auto previous_length = length_;
        length_ += second_length;
        capacity_ = length_ + 1;

        for (i = 0; i < previous_length; ++i) {
            string_[i] = tmp[i];
        }
        for (i = 0; i < second_length; ++i) {
            string_[previous_length + i] = second[i];
        }

        string_[length_] = 0;

        delete[] tmp;
    }

    return *this;
}

MyString MyString::operator+=(const std::string& second) {
    MyString new_string(second);
    MyString old_string(string_);
    return old_string += new_string;
}

MyString MyString::operator +=(const MyString& second) {
    return *this += second.string_;
}

MyString& MyString::operator=(const char second) {
    if (capacity_ <= 1) {
        delete[] string_;
        string_ = new char[2];
        capacity_ = 2;
    }

    string_[0] = second;
    string_[1] = 0;
    length_ = 1;

    return *this;
}

MyString& MyString::operator=(const char* second) {
    size_t second_length = 0;
    size_t i = 0;

    while (second[i++]) {
        ++second_length;
    }

    if (capacity_ > second_length) {
        for (i = 0; i < second_length; ++i) {
            string_[i] = second[i];
        }

        length_ = second_length;
    }
    else {
        delete[] string_;

        string_ = new char[second_length + 1];
        length_ = second_length;
        capacity_ = second_length + 1;

        for (i = 0; i < second_length; ++i) {
            string_[i] = second[i];
        }
    }

    string_[second_length] = 0;

    return *this;
}

MyString& MyString::operator=(const std::string& second) {
    return *this = second.c_str();
}

MyString& MyString::operator=(const MyString& second) {
    return *this = second.string_;
}

char MyString::operator[](size_t index) const {
    return string_[index];
}

bool MyString::operator >(const MyString& second) const {
    if (StrCmp(string_, second.string_) > 0) {
        return true;
    }

    return false;
}

bool MyString::operator >=(const MyString& second) const {
    if (StrCmp(string_, second.string_) > 0 || StrCmp(this->string_, second.string_) == 0) {
        return true;
    }

    return false;
}

bool MyString::operator <(const MyString& second) const {
    if (StrCmp(string_, second.string_) < 0) {
        return true;
    }

    return false;
}

bool MyString::operator <=(const MyString& second) const {
    if (StrCmp(string_, second.string_) < 0 || StrCmp(string_, second.string_) == 0) {
        return true;
    }

    return false;
}

bool MyString::operator ==(const MyString& second) const {
    if (StrCmp(string_, second.string_) == 0)
    {
        return true;
    }

    return false;
}

bool MyString::operator !=(const MyString& second) const {
    if (StrCmp(string_, second.string_) != 0) {
        return true;
    }

    return false;
}

char* MyString::c_str() const {
    return string_;
}

char* MyString::data() const {
    return string_;
}

size_t MyString::capacity() const {
    return capacity_;
}

size_t MyString::size() const {
    return length_;
}

bool MyString::empty() const {
    if (string_[0] == 0) {
        return true;
    }

    return false;
}

void MyString::clear() {
    for (size_t i = 0; i < length_; ++i) {
        string_[i] = 0;
    }

    length_ = 0;
}

void MyString::shrink_to_fit() {
    auto tmp = new char[length_ + 1];

    for (size_t i = 0; i < length_ + 1; ++i) {
        tmp[i] = string_[i];
    }

    delete[] string_;

    string_ = new char[length_ + 1];
    capacity_ = length_ + 1;

    for (size_t i = 0; i < length_ + 1; ++i) {
        string_[i] = tmp[i];
    }

    capacity_ = length_ + 1;

    delete[] tmp;
}

size_t MyString::length() const {
    return length_;
}

void MyString::insert(size_t index, size_t count, char character) {
    if (capacity_ - length_ > count) {
        auto temp = new char[length_ - index];

        for (size_t i = index; i < length_; ++i) {
            temp[i - index] = string_[i];
        }

        for (size_t i = index; i < index + count; ++i) {
            string_[i] = character;
        }

        length_ += count;

        for (size_t i = 0; i < length_ - index; ++i) {
            string_[i + index + count] = temp[i];
        }

        string_[length_] = 0;

        delete[] temp;
    }
    else {
        auto temp = new char[length_ + count + 1];

        for (size_t i = 0; i < index; ++i) {
            temp[i] = string_[i];
        }

        for (auto i = index; i < index + count; ++i) {
            temp[i] = character;
        }

        for (auto i = index + count, j = index; i < length_ + count; ++i, ++j) {
            temp[i] = string_[j];
        }

        temp[length_ + count] = 0;
        delete[] string_;

        string_ = new char[length_ + count + 1];
        length_ += count;
        capacity_ = length_ + 1;

        for (size_t i = 0; i < length_ + 1; ++i) {
            string_[i] = temp[i];
        }

        delete[] temp;
    }
}

void MyString::insert(size_t index, const char* string) {
    size_t length = 0;
    size_t i = 0;

    while (string[i++]) {
        ++length;
    }

    if (capacity_ - length_ > length) {
        auto temp = new char[length_ - index];

        for (i = index; i < length_; ++i) {
            temp[i - index] = string_[i];
        }

        for (i = index; i < index + length; ++i) {
            string_[i] = string[i - index];
        }

        length_ += length;

        for (i = 0; i < length_ - index; ++i) {
            string_[i + index + length] = temp[i];
        }

        string_[length_] = 0;

        delete[] temp;
    }
    else {
        char* temp = new char[length_ + length + 1];

        for (i = 0; i < index; ++i) {
            temp[i] = string_[i];
        }

        for (i = index; i < index + length; ++i) {
            temp[i] = string[i - index];
        }

        for (auto i = index + length, j = index; i < length_ + length; ++i, ++j) {
            temp[i] = string_[j];
        }

        temp[length_ + length] = 0;
        delete[] string_;

        string_ = new char[length_ + length + 1];
        length_ += length;
        capacity_ = length_ + 1;

        for (size_t i = 0; i < length_ + 1; ++i) {
            string_[i] = temp[i];
        }

        delete[] temp;
    }
}

void MyString::insert(size_t index, const char* string, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        this->insert(index, 1, string[i]);
        ++index;
    }
}

void MyString::insert(size_t index, const std::string& string) {
    this->insert(index, string.c_str());
}

void MyString::insert(size_t index, std::string string, size_t count) {
    this->insert(index, string.c_str(), count);
}

void MyString::erase(size_t index, size_t count) {
    for (auto i = index; i < length_ - count; ++i) {
        string_[i] = string_[i + count];
    }

    string_[length_ - count] = 0;
    length_ -= count;
}

void MyString::append(size_t count, char character) {
    this->insert(this->length(), count, character);
}

void MyString::append(const char* string) {
    this->insert(this->length(), string);
}

void MyString::append(const char* string, size_t index, size_t count) {
    auto tmp = new char[count + 1];

    for (size_t i = index; i < index + count; ++i) {
        tmp[i - index] = string[i];
    }

    tmp[count] = 0;

    this->append(tmp);

    delete[] tmp;
}

void MyString::append(const std::string& string) {
    this->insert(this->length(), string);
}

void MyString::append(const std::string& string, size_t index, size_t count) {
    this->append(string.c_str(), index, count);
}

void MyString::replace(size_t index, size_t count, const char* string) {
    this->erase(index, count);
    this->insert(index, string);
}

void MyString::replace(size_t index, size_t count, const std::string& string) {
    this->replace(index, count, string.c_str());
}

MyString MyString::substr(size_t index) const {
    MyString string;

    string.append(string_, index, length_ - index);

    return string;
}

MyString MyString::substr(size_t index, size_t count) const {
    MyString string;

    string.append(string_, index, count);

    return string;
}

int MyString::find(const char* string) const {
    auto result = StrStr(string_, string);

    if (result == nullptr) {
        return -1;
    }

    return static_cast<int>(result - string_);
}

int MyString::find(const char* string, size_t index) const {
    auto tmp_string = this->substr(index);
    auto tmp = tmp_string.c_str();

    auto result = StrStr(tmp, string);

    if (result == nullptr) {
        return -1;
    }

    return static_cast<int>(result - tmp) + index;
}

int MyString::find(const std::string& string) const {
    return this->find(string.c_str());
}

int MyString::find(const std::string& string, size_t index) const {
    return this->find(string.c_str(), index);
}

std::ostream& operator<<(std::ostream& out, MyString& string) {
    out << string.string_;
    return out;
}

using namespace std;

std::istream& operator>>(std::istream& in, MyString& string) { 
    char temp = '\0';
    while ((temp = in.get()) != '\n')
    {
        string.append(1, temp);
    }
    return in;
}

int MyString::StrCmp(const char* str1, const char* str2) const {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

const char* MyString::StrStr(const char* string, const char* substring) const {
    while (*string) {
        auto start = string;
        auto sub = substring;

        while (*string && *sub && *string == *sub) {
            string++;
            sub++;
        }

        if (!*sub) {
            return start;
        }

        string = start + 1;
    }

    return nullptr;
}