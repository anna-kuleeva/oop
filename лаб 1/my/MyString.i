/* File : MyString.i */
%module MyString

%{
#include "MyString.h"
%}

/* Let's just grab the original header file here */
%include "MyString.h"
