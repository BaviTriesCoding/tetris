//
// Created by riccardo on 28/02/24.
//
#ifdef _WIN32
#include <ncurses/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

int sign(int _n);
void initializeNcurses();
