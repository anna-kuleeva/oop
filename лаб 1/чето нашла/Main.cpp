#include <iostream>
#include "StringClass.h"

using namespace std;

int main() {

    StringClass test1("test1");
    StringClass test2("test2");
    StringClass test3({ 't', 'e', 's', 't', '3' });
    //StringClass test3(list3);
    StringClass test4("hello", 4);
    StringClass test5("hello amazing world");
    
    test5 = test3 + test2;
    cout << test5 << endl;
    
    return 0;
}