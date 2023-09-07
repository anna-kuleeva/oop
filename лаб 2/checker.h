#pragma once

enum Color{black, white};

class Checker {
public:
	Color color;
	bool king;

	Checker();
	Checker(const Checker &other);
	//~Checker();
};

class Field {
public:
	char value;
	Checker *ptr; //there is a fig
	bool is_chec; //is here some fig?

	Field();
	Field(const Field &other);
	~Field();
	int step(unsigned int i_start, unsigned int j_start, unsigned int i_end, unsigned int j_end);
	int king(unsigned int i_start, unsigned int j_start, unsigned int i_end, unsigned int j_end);
};

class User {
public:
	Color color;
	bool my_turn;
	unsigned short amount;
};

typedef struct coord {
	unsigned int i, j;
} coord;
