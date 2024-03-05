#include "library.h"
int main() {
    initscr();
    start_color();
    use_default_colors();
    noecho();
    curs_set(0);
    WINDOW* screen = newwin(20, 20, LINES/2 - 10, COLS/2 - 10);
    WINDOW* cornice = newwin(22, 22, LINES/2 - 11, COLS/2 - 11);
    box(cornice, 0, 0);
    wrefresh(cornice);
    keypad(screen, true);
    I_Piece start_tetramin = I_Piece(screen, 2);
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
