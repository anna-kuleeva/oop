#include "checker.h"

Checker::Checker() {
	this->king = false;
}

Checker::Checker(const Checker &other)
{
	this->color = other.color;
	this->king = other.king;
}

Field::Field(const Field &other)
{
	this->value = other.value;
	this->ptr = other.ptr;
	this->is_chec = other.is_chec;
}

Field::Field() {
	this->is_chec = false;
}

Field::~Field() {
	delete this;
}

/*Checker::~Checker() {
	delete this;
}*/

/*bool Checker::check(unsigned int x, unsigned int y) {

}

bool Checker::step(unsigned int x, unsigned int y) {

}

bool Checker::beat(unsigned int x, unsigned int y) {

}*/
