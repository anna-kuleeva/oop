#pragma once

#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <conio.h>
#include "checker.h"


Field** init();
void play();
void deinit();
void print_field();
bool check(unsigned int i_start, unsigned int j_start, unsigned int i_end, unsigned int j_end); //check if step is possible
coord check_king(unsigned int x_start, unsigned int y_start, unsigned int x_end, unsigned int y_end); //another check for king

