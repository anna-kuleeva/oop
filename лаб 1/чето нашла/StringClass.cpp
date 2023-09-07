#include "StringClass.h"

StringClass::StringClass() {
    size_variable = 0;
    string_variable = NULL;
}

StringClass::StringClass(const StringClass& tmp) {

    if (tmp.string_variable != NULL)
    {
        size_variable = tmp.size_variable;
        string_variable = new char[size_variable + 1];
        strcpy(string_variable, tmp.string_variable);
    }
    else
    {
        size_variable = 0;
        string_variable = NULL;
    }
}

StringClass::StringClass(const char* str) {

    if (str != NULL)
    {
        size_variable = strlen(str);
        string_variable = new char[size_variable + 1];
        strcpy(string_variable, str);
    }
    else {
        string_variable = NULL;
        size_variable = 0;
    }
    string_variable[size_variable] = '\0';
}

StringClass::StringClass(const std::initializer_list<int>& char_list) {

    size_variable = char_list.size();
    string_variable = new char[size_variable + 1];
    int string_counter = 0;
    for (auto list_counter : char_list)
    {
        string_variable[string_counter] = list_counter;
        ++string_counter;
    }
    string_variable[string_counter] = '\0';
}

StringClass::StringClass(string str)
{
    size_variable = str.size();
    string_variable = new char[size_variable + 1];
    int string_counter = 0;
    for (auto char_counter : str)
    {
        string_variable[string_counter] = char_counter;
        ++string_counter;
    }
    string_variable[size_variable] = '\0';
}

StringClass::StringClass(const char* str, size_t count)
{
    if (str != NULL)
    {
        size_variable = count;
        string_variable = new char[count + 1];
        strncpy(string_variable, str, count);
    }
    else {
        string_variable = NULL;
        size_variable = 0;
    }
    string_variable[size_variable] = '\0';
}

StringClass::StringClass(size_t count, char symbol)
{
    if (count > 0)
    {
        size_variable = count;
        string_variable = new char[count + 1];
        memset(string_variable, symbol, count);
    }
    else {
        string_variable = NULL;
        size_variable = 0;
    }
    string_variable[size_variable] = '\0';
}

StringClass::~StringClass() {
    delete[] string_variable;
}

const StringClass& StringClass::operator+ (const StringClass& str) {

    return this->operator+(str.string_variable);
}

const StringClass& StringClass::operator+ (const char* str) {

    if (str == NULL) return *this;
    if (string_variable == NULL)
    {
        size_variable = strlen(str);
        string_variable = new char[size_variable + 1];
        strcpy(string_variable, str);
    }
    else
    {
        size_variable += strlen(str);
        string_variable = (char*)realloc(string_variable, (size_variable + 1) * sizeof(char));
        strcat(string_variable, str);
    }

    return *this;
}

const StringClass& StringClass::operator+ (string str) {

    return this->operator+((char*)str.c_str());
}

const StringClass& StringClass::operator+= (const char* str) {

    if (str == NULL) return *this;
    if (string_variable == NULL)
    {
        size_variable = strlen(str);
        string_variable = new char[size_variable + 1];
        strcpy(string_variable, str);
    }
    else
    {
        size_variable += strlen(str);
        string_variable = (char*)realloc(string_variable, (size_variable + 1) * sizeof(char));
        strcat(string_variable, str);
    }

    return *this;
}

const StringClass& StringClass::operator+= (string str) {

    return this->operator+=((char*)str.c_str());
}

const StringClass& StringClass::operator= (const char* str) {

    if (str == NULL) return *this;

    size_variable = strlen(str);
    if (string_variable == NULL) delete[] string_variable;
    string_variable = new char[size_variable + 1];
    strcpy(string_variable, str);

    return *this;
}

const StringClass& StringClass::operator= (StringClass tmp) {

    clear(); 
    this->operator+(tmp.string_variable);
    return *this;
}

const StringClass& StringClass::operator= (string str) {

    return this->operator=((char*)str.c_str());
}

const StringClass& StringClass::operator= (char symbol) {

    char* tmp = new char[2];
    tmp[0] = symbol;
    tmp[1] = '\0';

    return this->operator=(tmp);
}

bool StringClass::operator> (const StringClass& tmp) {
    return !operator<=(tmp);
}

bool StringClass::operator< (const StringClass& tmp) {

    return !operator>=(tmp);
}

bool StringClass::operator>= (const StringClass& tmp) {

    for (size_t i = 0; i < tmp.size_variable; i++)
        if (string_variable[i] < tmp.string_variable[i])
            return false;
    return true;
}

bool StringClass::operator<= (const StringClass& tmp) {

    for (size_t i = 0; i < tmp.size_variable; i++)
        if (string_variable[i] > tmp.string_variable[i])
            return false;
    return true;
}

bool StringClass::operator!= (const StringClass& tmp) {
    return !operator==(tmp);
}

bool StringClass::operator== (const StringClass& tmp) {
    for (size_t i = 0; i < tmp.size_variable; i++)
        if (string_variable[i] > tmp.string_variable[i])
            return false;
    return true;

}

char& StringClass::operator[](size_t index) {
    return string_variable[index];
};

const char* StringClass::c_str() {
    return string_variable;
}

const char* StringClass::data() {
    return string_variable;
}

size_t StringClass::length() {
    return strlen(string_variable);
}

size_t StringClass::size() {
    return strlen(string_variable);
}

bool StringClass::empty() {
    return ((size_variable == 0) ? true : false);
}

size_t StringClass::capacity() {
    return sizeof(string_variable);
}

void StringClass::shrink_to_fit() {
    size_t new_size = strlen(string_variable);
    string_variable = (char*)realloc(string_variable, (new_size + 1) * sizeof(char));
    string_variable[new_size] = '\0';
}

void StringClass::clear() {
    delete[] string_variable;
    string_variable = NULL;
    size_variable = 0;
}

std::ostream& operator<< (std::ostream& out, const StringClass& tmp)
{
    if (tmp.string_variable == NULL) out << "";
    else out << tmp.string_variable;
    return out;
}

std::istream& operator>> (std::istream& in, StringClass& tmp)
{
    tmp.string_variable = new char[MAX_INPUT_STR_SIZE];
    in.getline(tmp.string_variable, MAX_INPUT_STR_SIZE, '\n');
    size_t new_size = tmp.length();
    tmp.string_variable = (char*)realloc(tmp.string_variable, (new_size + 1) * sizeof(char));
    tmp.string_variable[new_size] = '\0';
    return in;
}

StringClass& StringClass::insert(size_t index, size_t count, char symbol) {

    size_t tmp_size = size_variable + count + 1;
    char* tmp = new char[tmp_size];
    int counter;
    for (counter = 0; counter < index; counter++)
        tmp[counter] = string_variable[counter];
    for (counter = index; counter < count + index; counter++)
        tmp[counter] = symbol;
    if (count + index + 1 != tmp_size) {
        for (counter = count + index; counter < tmp_size; counter++)
            tmp[counter] = string_variable[counter - count];
    }

    if (string_variable)
        string_variable = (char*)realloc(string_variable, sizeof(char) * tmp_size);
    else string_variable = new char[tmp_size];
    string_variable = tmp;
    string_variable[tmp_size - 1] = '\0';
    tmp_size--;
    size_variable = tmp_size;

    return *this;
}

StringClass& StringClass::insert(size_t index, char* str) {

    size_t tmp_size = size_variable + strlen(str) + 1;
    char* tmp = new char[tmp_size];
    int counter;
    for (counter = 0; counter < index; counter++)
        tmp[counter] = string_variable[counter];
    for (counter = index; counter < strlen(str) + index; counter++)
        tmp[counter] = str[counter - index];
    for (counter = strlen(str) + index; counter < tmp_size; counter++)
        tmp[counter] = string_variable[counter - strlen(str)];

    tmp_size--;
    size_variable = tmp_size;
    string_variable = (char*)realloc(string_variable, sizeof(char) * tmp_size);
    string_variable = tmp;

    return *this;
};

StringClass& StringClass::insert(size_t index, char* str, size_t count) {

    for (size_t iterator = 0; iterator < count; iterator++)
        insert(index, 1, str[iterator]);
    return *this;
}

StringClass& StringClass::insert(size_t index, string str) {

    insert(index, (char*)str.c_str());
    return *this;
}

StringClass& StringClass::insert(size_t index, string str, size_t count) {

    str = str.substr(0, count);
    insert(index, str);
    return *this;
}

StringClass& StringClass::erase(size_t index, size_t count) {

    char* tmp = new char[size_variable + 1];
    strcpy(tmp, string_variable);
    string_variable = (char*)realloc(string_variable, (size_variable - count + 1) * sizeof(char));
    for (int i = index + count; i < size_variable; i++)

        string_variable[i - count] = tmp[i];
    size_variable -= count;
    string_variable[size_variable] = '\0';

    return *this;
}

StringClass& StringClass::append(size_t count, char symbol) {

    size_t index = size_variable;
    size_t iterator = 0;
    for (iterator = 0; iterator < count; iterator++)
        insert(index + iterator, 1, symbol);
    return *this;
}

StringClass& StringClass::append(char* str) {

    size_t length = strlen(str);
    for (size_t iterator = 0; iterator < length; iterator++)
        append(1, str[iterator]);
    return *this;
}

StringClass& StringClass::append(char* str, size_t index, size_t count) {

    char* tmp = new char[count + 1];
    for (int iterator = index; iterator < index + count; iterator++)
        tmp[iterator - index] = str[iterator];
    tmp[count] = '\0';
    append(tmp);
    return *this;
}

StringClass& StringClass::append(string str) {
    append((char*)str.c_str());
    return *this;
}

StringClass& StringClass::append(string str, size_t index, size_t count) {

    str = str.substr(index, count);
    append(str);
    return *this;
}

StringClass& StringClass::replace(size_t index, size_t count, char* str) {

    erase(index, count);
    insert(index, str);
    return *this;
}

StringClass& StringClass::replace(size_t index, size_t count, string str) {

    replace(index, count, (char*)str.c_str());
    return *this;
}

StringClass StringClass::substr(size_t index) {

    StringClass tmp(string_variable);
    tmp.erase(0, index);
    return tmp;
}

StringClass StringClass::substr(size_t index, size_t count) {

    StringClass tmp(string_variable);
    tmp.erase(0, index);
    tmp.erase(count, tmp.size_variable - count);
    return tmp;
}

bool StringClass::equals(const char* str)
{
    for (size_t iterator = 0; iterator < size_variable; iterator++)
    {
        if (string_variable[iterator] != str[iterator])
            return false;
    }
    return true;
}

long long int StringClass::find(const char* str) {

    size_t find_string_size = strlen(str);

    for (size_t iterator = 0; iterator < size_variable - find_string_size + 1; iterator++)
    {
        StringClass tmp(this->substr(iterator, find_string_size));
        if (tmp.equals(str))
            return iterator;
    }
    return -1;
}

long long int StringClass::find(const char* str, size_t index) {

    size_t find_string_size = strlen(str);

    if (index > size_variable - find_string_size) return -1;

    for (size_t iterator = index; iterator < size_variable - find_string_size; iterator++)
    {
        StringClass tmp(this->substr(iterator, find_string_size));
        if (tmp.equals(str))
            return iterator;
    }
    return -1;
}

long long int StringClass::find(string str) {
    return find((char*)str.c_str());
}

long long int StringClass::find(string str, std::size_t index) {
    return find((char*)str.c_str(), index);
}