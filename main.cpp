#include "main.h"

void print_msg() {
	//rules
	printf("\n\t\t\t����� ���������� � ���� \"�����\"!\n\n\t�������:\n");
	printf("\t1. �����������:\n\t\tw -- ����� �����\n\t\tb -- ������ �����\n\t\tW -- ����� �����\n\t\tB -- ������ �����\n");
	printf("\t\t- -- ����, �� ������� ��� �����, �� ��� ����� ���� ���\n\t\t�� ������ ���� ������ ������!\n");
	printf("\t2. �� ������ ���� ������ ������!\n");
	//printf("\t3. ����� ������� ����� ���� (���� ��� ��� ������) ���������� ������ � ���������� ����� 1 ��� 2 �������������.\n");
	printf("\t3. ����� ������� ��������� ���, ������������ ������ � ���������� ����� ����, ������������ �� �����,\n\t");
	printf("   ������� �� ����� �� �����������, � ����� ����, ���� �� ����� �� � ����������� ����� ������.\n");
	printf("\t4. ����� ���� ������� �� ����� ������� � ������ ������, ���������� �� ������� ����� ������ (��������, �1 �2).\n");
	printf("\t5. ������� ����� �� ����� ������ �����.\n");
	printf("\t6. ���� ����� �����.\n");
	printf("\t7. ����� ����� ������ � ����� ����������� �� ����� ���������� ������, � ��� ����� � �����. \n");

}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	print_msg(); //welcome message for players
	init(); //initialize playground and all figures
	play(); // go play!
	deinit();
}