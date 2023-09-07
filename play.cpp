#include "checker.h"
#include <stdio.h>
#include <cstdlib>
#include "main.h"

User user1, user2;
Checker chec[24];
Field** field;

Field** init() {
	user1.color = white;
	user1.my_turn = true;
	user1.amount = 12;
	user2.color = black;
	user2.my_turn = false;
	user2.amount = 12;

	for (unsigned int i = 0; i < 12; i++) {
		chec[i].color = black;
		chec[23 - i].color = white;
	}

	field = new Field*[8];
	for (unsigned int i = 0; i < 8; i++)
		field[i] = new Field[8];
	char tmp; //to put colors
	unsigned int index = 0;

	for (unsigned int i = 0; i < 8; i++) {
		if (i < 3)
			tmp = 'b';
		else if (i < 5)
			tmp = '-';
		else tmp = 'w';
		for (unsigned int j = 0; j < 8; j++) {
			if (i % 2 == 0 && j % 2 == 1 || i % 2 == 1 && j % 2 == 0) { //set figs like " i i"j = j;
				field[i][j].value = tmp;
				if (tmp != '-') {
					field[i][j].is_chec = true;
					field[i][j].ptr = &chec[index];
					index++;
					if (tmp == 'b')
						chec[index].color = black;
					else
						chec[index].color = white;
				}
			}
			else {
				field[i][j].value = ' ';
			}
		}
	}
	return field;
}

void deinit() {
	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			if (field[i][j].is_chec) {
				field[i][j].ptr = nullptr;
				field[i][j].is_chec = false;
			}
		}
	}
}

void print_field() {
	unsigned short x = 1;
	printf("\n    ");
	for (unsigned short i = 'A'; i < 'A' + 8; i++)
		printf("_%c_ ", i);

	for (unsigned short i = 0; i < 8; i++) {
		for (unsigned short j = 0; j < 8; j++) {
			if (j == 0)
				printf("\n %hu ", x);
			printf("|_%c_", field[i][j].value);
			if (j == 7) {
				printf("| %hu ", x);
				x++;
			}
		}
	}
	printf("\n    ");
	for (unsigned short i = 'A'; i < 'A' + 8; i++)
		printf(" %c  ", i);
}

void play() {
	int count;
	unsigned int i_start, j_start, i_end, j_end;
	char ch;
	while (user1.amount && user2.amount) {
		count = -1;
		print_field();
		if (user1.my_turn) printf("\n\n\tХод белых.");
		else printf("\n\n\tХод чёрных.");
		printf(" Введите координаты своего хода: ");
		j_start = getchar() - 'A';
		i_start = getchar() - '0' - 1;
		ch = getchar(); //пропускаем пробел
		j_end = getchar() - 'A';
		i_end = getchar() - '0' - 1;
		ch = getchar();

		if (ch == '\n') {
			if (check(i_start, j_start, i_end, j_end)) {
				if (field[i_start][j_start].ptr->king) count = field[i_start][j_start].king(i_start, j_start, i_end, j_end);
				else count = field[i_start][j_start].step(i_start, j_start, i_end, j_end);
			}
		}
		else {
			printf("\tНеправильный формат ввода!\n");
			while (ch != '\n') ch = getchar();
		}
		if (count == 0) {
			if (user1.my_turn) {
				user1.my_turn = false;
				user2.my_turn = true;
			}
			else {
				user1.my_turn = true;
				user2.my_turn = false;
			}
			system("cls");
		}
		else {
			system("cls");
			printf("\n\tДоступен еще один ход шашки.\n");
		}
	}
	if (user1.amount) printf("\n\n\n\t\tЧёрные победили!");
	else printf("\n\n\n\t\tБелые победили!");
}

bool check(unsigned int i_start, unsigned int j_start, unsigned int i_end, unsigned int j_end) {
	if (i_start > 8 || i_end > 8 || j_start > 8 || j_end > 8) {
		printf("\tОшибка! Неверные координаты!\n");
		return false;
	}
	if (!field[i_start][j_start].is_chec) { //is fig here?
		printf("\tОшибка! Неверные координаты!\n");
		return false;
	}
	if (field[i_end][j_end].is_chec) { //is this field empty?
		printf("\tОшибка! Неверные координаты!\n");
		return false;
	}
	if (field[i_end][j_end].value != '-') { //is this field available for step?
		printf("\tОшибка! Неверные координаты!\n");
		return false;
	}
	if (field[i_start][j_start].ptr->king)
		return true; // check_king(i_start, j_start, i_end, j_end, field);
	else { //no steps back for simple fig
		if (field[i_start][j_start].value == 'b' && i_start > i_end && j_start > j_end) {
			if (field[i_start - 1][j_start - 1].value != '-' && //gonna beat?
				field[i_start - 1][j_start - 1].value != 'w' && //can't beat yourself
				field[i_start - 1][j_start - 1].value != 'W') {
				printf("\tОшибка! Неверные координаты!\n");
				return false;
			}
		}
		else
			if (field[i_start][j_start].value == 'w' && i_start < i_end && j_start < j_end) {
				if (field[i_start - 1][j_start - 1].value != '-' && //gonna beat?
					field[i_start - 1][j_start - 1].value != 'b' && //can't beat yourself
					field[i_start - 1][j_start - 1].value != 'B') {
					printf("\tОшибка! Неверные координаты!\n");
					return false;
				}
			}
	}
	return true;
}

int Field::step(unsigned int i_start, unsigned int j_start, unsigned int i_end, unsigned int j_end) {
	char tmp;
	//check for king
	if (i_end == 7 && user2.my_turn) {
		this->value = 'B';
		this->ptr->king = true;
	}
	else if	(i_end == 0 && user1.my_turn) {
		this->value = 'W';
		this->ptr->king = true;
	}
	if (user1.my_turn && i_start - 1 == i_end || user2.my_turn && i_start == i_end - 1) { //simple step
		tmp = this->value;
		field[i_end][j_end].value = tmp;
		this->value = '-';
		this->is_chec = false;
		field[i_end][j_end].is_chec = true;
		field[i_end][j_end].ptr = this->ptr;
		this->ptr = NULL;
		return 0;
	} //beat
	else if ((j_start + 1 == j_end - 1 || j_start - 1 == j_end + 1) && (i_start + 1 == i_end - 1 || i_start - 1 == i_end + 1)) {
		//move fig
		tmp = this->value;
		field[i_end][j_end].value = tmp;
		this->value = '-';
		this->is_chec = false;
		field[i_end][j_end].is_chec = true;
		field[i_end][j_end].ptr = this->ptr;
		this->ptr = NULL;
		//del fig
		unsigned int i_mid, j_mid;
		if (i_start + 1 == i_end - 1) i_mid = i_start + 1;
		else i_mid = i_start - 1;
		if (j_start + 1 == j_end - 1) j_mid = j_start + 1;
		else j_mid = j_start - 1;

		field[i_mid][j_mid].value = '-';
		field[i_mid][j_mid].is_chec = false;
		this->ptr = NULL;
		if (user1.my_turn) user2.amount--;
		else user1.amount--;
		return 1;
	}
	else {
		printf("\tОшибка! Неверные координаты!\n");
		return -1;
	}
}

int Field::king(unsigned int i_start, unsigned int j_start, unsigned int i_end, unsigned int j_end) {
	coord c = check_king(i_start, j_start, i_end, j_end); //check this step is available
	char tmp;
	if (c.i == 0 && c.j == 0)
		return -1;
	else if (c.i == 10 && c.j == 10) { //simple step
		tmp = this->value;
		field[i_end][j_end].value = tmp;
		this->value = '-';
		this->is_chec = false;
		field[i_end][j_end].is_chec = true;
		field[i_end][j_end].ptr = this->ptr;
		this->ptr = NULL;
		return 0;
	} //beat
	else {
		//move fig
		tmp = this->value;
		field[i_end][j_end].value = tmp;
		this->value = '-';
		this->is_chec = false;
		field[i_end][j_end].is_chec = true;
		field[i_end][j_end].ptr = this->ptr;
		this->ptr = NULL;
		//del fig
		unsigned int i_mid, j_mid;
		i_mid = c.i;
		j_mid = c.j;

		field[i_mid][j_mid].value = '-';
		field[i_mid][j_mid].is_chec = false;
		this->ptr = NULL;
		if (user1.my_turn) user2.amount--;
		else user1.amount--;
		return 1;
	}
}

coord check_king(unsigned int i_start, unsigned int j_start, unsigned int i_end, unsigned int j_end) {
	unsigned short i, j;
	bool flag = false; //chek that we gonna beat only one fig
	coord c;
	c.i = 10;
	c.j = 10;
	if (i_start > i_end) { //влево
		if (j_start > j_end) { //вверх
			if (i_start - i_end == j_start - j_end) { //is this diagonal?
				for (i = i_start - 1, j = j_start - 1; i > i_end && j > j_end; i--, j--) {
					if (user1.my_turn) {
						if (field[i][j].value == 'W' || field[i][j].value == 'w') {
							printf("\tОшибка! Нельзя бить свои фигуры!\n");
							c.i = 0;
							c.j = 0;
						}
						if (field[i][j].value != '-') { //if this is not step but kill
							if (flag) { //can't beat two figs at once
								c.i = 0;
								c.j = 0;
							}
							else{
								c.i = i;
								c.j = j;
								flag = true;
							}
						}
					}
					else {
						if (field[i][j].value == 'B' || field[i][j].value == 'b') {
							printf("\tОшибка! Нельзя бить свои фигуры!\n");
							c.i = 0;
							c.j = 0;
						}
						if (field[i][j].value != '-') { //if this is not step but kill
							if (flag) { //can't beat two figs at once
								c.i = 0;
								c.j = 0;
							}
							else {
								c.i = i;
								c.j = j;
								flag = true;
							}
						}
					}
				}
			}
			else {
				printf("\tОшибка! Неверные координаты!\n");
				c.i = 0;
				c.j = 0;
			}
		}
		else if (j_start < j_end) { //вниз
			if (i_start - i_end == j_end - j_start) { //is this diagonal?
				for (i = i_start - 1, j = j_start + 1; i > i_end && j < j_end; i--, j++) {
					if (user1.my_turn) {
						if (field[i][j].value == 'W' || field[i][j].value == 'w') {
							printf("\tОшибка! Нельзя бить свои фигуры!\n");
							c.i = 0;
							c.j = 0;
						}
						if (field[i][j].value != '-') { //if this is not step but kill
							if (flag) { //can't beat two figs at once
								c.i = 0;
								c.j = 0;
							}
							else {
								c.i = i;
								c.j = j;
								flag = true;
							}
						}
					}
					else {
						if (field[i][j].value == 'B' || field[i][j].value == 'b') {
							printf("\tОшибка! Нельзя бить свои фигуры!\n");
							c.i = 0;
							c.j = 0;
						}
						if (field[i][j].value != '-') { //if this is not step but kill
							if (flag) { //can't beat two figs at once
								c.i = 0;
								c.j = 0;
							}
							else {
								c.i = i;
								c.j = j;
								flag = true;
							}
						}
					}
				}
			}
			else {
				printf("\tОшибка! Неверные координаты!\n");
				c.i = 0;
				c.j = 0;
			}
		}
	}
	else if (i_start < i_end) { //вправо
		if (j_start > j_end) { //вверх
			if (i_end - i_start == j_start - j_end) { //is this diagonal?
				for (i = i_start + 1, j = j_start - 1; i < i_end && j > j_end; i++, j--) {
					if (user1.my_turn) {
						if (field[i][j].value == 'W' || field[i][j].value == 'w') {
							printf("\tОшибка! Нельзя бить свои фигуры!\n");
							c.i = 0;
							c.j = 0;
						}
						if (field[i][j].value != '-') { //if this is not step but kill
							if (flag) { //can't beat two figs at once
								c.i = 0;
								c.j = 0;
							}
							else {
								c.i = i;
								c.j = j;
								flag = true;
							}
						}
					}
					else {
						if (field[i][j].value == 'B' || field[i][j].value == 'b') {
							printf("\tОшибка! Нельзя бить свои фигуры!\n");
							c.i = 0;
							c.j = 0;
						}
						if (field[i][j].value != '-') { //if this is not step but kill
							if (flag) { //can't beat two figs at once
								c.i = 0;
								c.j = 0;
							}
							else {
								c.i = i;
								c.j = j;
								flag = true;
							}
						}
					}
				}
			}
			else {
				printf("\tОшибка! Неверные координаты!\n");
				c.i = 0;
				c.j = 0;
			}
		}
		else if (j_start < j_end) { //вниз
			if (i_end - i_start == j_end - j_start) { //is this diagonal?
				for (i = i_start + 1, j = j_start + 1; i < i_end && j < j_end; i++, j++) {
					if (user1.my_turn) {
						if (field[i][j].value == 'W' || field[i][j].value == 'w') {
							printf("\tОшибка! Нельзя бить свои фигуры!\n");
							c.i = 0;
							c.j = 0;
						}
						if (field[i][j].value != '-') { //if this is not step but kill
							if (flag) { //can't beat two figs at once
								c.i = 0;
								c.j = 0;
							}
							else {
								c.i = i;
								c.j = j;
								flag = true;
							}
						}
					}
					else {
						if (field[i][j].value == 'B' || field[i][j].value == 'b') {
							printf("\tОшибка! Нельзя бить свои фигуры!\n");
							c.i = 0;
							c.j = 0;
						}
						if (field[i][j].value != '-') { //if this is not step but kill
							if (flag) { //can't beat two figs at once
								c.i = 0;
								c.j = 0;
							}
							else {
								c.i = i;
								c.j = j;
								flag = true;
							}
						}
					}
				}
			}
			else {
				printf("\tОшибка! Неверные координаты!\n");
				c.i = 0;
				c.j = 0;
			}
		}
	}
	return c;
}
