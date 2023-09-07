#include "MyString.h"
#include <string>
#include <iostream>
//#include "string.cpp"

int main() {
	MyString a1;
	std::cout << a1 << " " << a1.size() << " " << a1.capacity() << std::endl; //fix stdout

	MyString a2("Hello world!");
	std::cout << a2 << " " << a2.size() << " " << a2.capacity() << std::endl;

	MyString a3({ 'h','e','l','l','o' });
	std::cout << a3 << " " << a3.size() << " " << a3.capacity() << std::endl;

	std::string s = "hello";
	MyString a4(s);
	std::cout << a4 << " " << a4.size() << " " << a4.capacity() << std::endl;

	MyString a5("hello", 4);
	std::cout << a5 << " " << a5.size() << " " << a5.capacity() << std::endl;

	MyString a6(5, '!');
	std::cout << a6 << " " << a6.size() << " " << a6.capacity() << std::endl;

	MyString a7("hello");
	MyString a8(a7);
	std::cout << a8 << " " << a8.size() << " " << a8.capacity() << std::endl << std::endl << std::endl;
	
	MyString a9(2, 'a');
	MyString a10(3, 'b');
	MyString a11;
	a11 = a9 + a10;
	std::cout << a11 << std::endl;

	MyString testing2 = a2 + "It is char array test.";
	std::cout << testing2 << std::endl;

	std::string s1 = "It is std::string test for + operator.";
	MyString testing3;
	testing3 = a2 + s1;
	std::cout << testing3 << std::endl;

	MyString testing4("I am char array.");
	testing4 += "Let's test += operator.";
	std::cout << testing4 << std::endl;

	std::string s2 = "It is std::string test for += operator.";
	MyString testing5("I am string.");
	testing5 += s2;
	std::cout << testing5 << std::endl;

	MyString testing6;
	testing6 = "Hello! I am char array string.";
	std::cout << testing6 << std::endl;

	std::string s3 = "Hello! I am std::string.";
	MyString testing7;
	testing7 = s3;
	std::cout << testing7 << std::endl;

	MyString testing8;
	testing8 = 's';
	std::cout << testing8 << std::endl;

	std::cout << testing6[0] << ' ' << testing6[3] << ' ' << testing6[5] << std::endl << std::endl << std::endl;

	bool check;
	check = testing5 > testing6;
	if (check)
		std::cout << "testing5 > testing6" << std::endl;
	else
		std::cout << "testing5 < testing6" << std::endl;

	check = testing5 < testing6;
	if (check)
		std::cout << "testing5 < testing6" << std::endl;
	else
		std::cout << "testing5 > testing6" << std::endl;

	check = testing5 >= testing6;
	if (check)
		std::cout << "testing5 >= testing6" << std::endl;
	else
		std::cout << "testing5 < testing6" << std::endl;

	check = testing5 <= testing6;
	if (check)
		std::cout << "testing5 <= testing6" << std::endl;
	else
		std::cout << "testing5 > testing6" << std::endl;

	check = testing5 == testing6;
	if (check)
		std::cout << "testing5 == testing6" << std::endl;
	else
		std::cout << "testing5 !+ testing6" << std::endl;

	check = testing5 != testing6;
	if (check)
		std::cout << "testing5 != testing6" << std::endl;
	else
		std::cout << "testing5 == testing6" << std::endl;

	check = testing5.empty();
	if (check)
		std::cout << "Srting is empty" << std::endl;
	else
		std::cout << "String is not empty" << std::endl;

	check = a1.empty();
	if (check)
		std::cout << "Srting is empty" << std::endl;
	else
		std::cout << "String is not empty" << std::endl << std::endl << std::endl;

	MyString ins_test = a4;
	ins_test.insert(3, 5, '.');
	std::cout << ins_test << std::endl;
	a4.insert(3, " ibks ");
	std::cout << a4 << std::endl;
	ins_test.insert(5, "UUUUUUUUUUUU", 3);
	std::cout << ins_test << std::endl;
	std::string si = "i am std::string to insert ";
	a3.insert(0, si);
	std::cout << a3 << std::endl;
	a2.insert(6, si, 10);
	std::cout << a2 << std::endl;

	//MyString io;
	//std::cin >> io;

	a2.erase(6, 10);
	std::cout << a2 << std::endl;
	MyString ss("i am it specialist");
	ss.replace(5, 2, "security");
	std::cout << ss << std::endl;
	std::string ss3 = "cyber";
	ss.replace(5, 8, ss3);
	std::cout << ss << std::endl;
	MyString ss1 = ss.substr(5);
	std::cout << ss1 << std::endl;
	ss1 = ss.substr(5, 5);
	std::cout << ss1 << std::endl;

	a4.append(3, '!');
	std::cout << a4 << std::endl;
	MyString n1(s);
	n1.append(s);
	std::cout << n1 << std::endl;
	MyString n2(s);
	n2.append(s, 3, 2);
	std::cout << n2 << std::endl;
	MyString n3(s);
	n3.append("@@@@@");
	std::cout << n3 << std::endl;
	MyString n4(s);
	n4.append("world", 2, 3);
	std::cout << n4 << std::endl;

	unsigned int res = n1.find(s);
	std::cout << res << std::endl;
	res = n1.find(s, 5);
	std::cout << res << std::endl;
	res = n1.find("hel");
	std::cout << res << std::endl;
	res = n4.find("wo", 2);
	std::cout << res << std::endl;

	return 0;
}
