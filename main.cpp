#include "library.h"
#include "TetrisGame/TetrisGame.hpp"
int main() {
    initscr();
    start_color();
    use_default_colors();
    noecho();
    curs_set(0);
    WINDOW* screen = newwin(20, 20, LINES/2 - 10, COLS/2 - 10);
    WINDOW* cornice = newwin(22, 22, LINES/2 - 11, COLS/2 - 11);
    init_pair(7,7,7);
    chtype borderch = ('|'| COLOR_PAIR(7));
    wborder(cornice, borderch, borderch, '_', ' ', '_', '_', ' ', ' ');
    wrefresh(cornice);
    keypad(screen, true);
    Tetramin start_tetramin = O_Piece(screen, -2, 5, 0);
    start_tetramin.show();
    int inputChar;
    do{
        inputChar = wgetch(screen);
        start_tetramin.evalMove(inputChar);
    }while(inputChar!='p');
    wgetch(screen);
    endwin();

    return 0;
}
