//
// Created by riccardo on 28/02/24.
//

#include "library.h"

int sign(int _n){
    //ritorna il segno del numero in input e ritorna 0 se _n = 0
    if(_n > 0){return 1;}else if(_n < 0){return -1;}else{return 0;}
}

void initializeNcurses(){
    initscr();
    if(has_colors()){
        start_color();
        use_default_colors();
    }
    noecho();
    cbreak();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    curs_set(0);
}