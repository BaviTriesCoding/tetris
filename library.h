//
// Created by riccardo on 28/02/24.
//
#ifdef _WIN64
#include <curses/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

int sign(int _n);
void initializeNcurses();
