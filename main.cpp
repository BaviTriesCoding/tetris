#include "Tetramin/Tetramin.hpp"
#include "Tetramin/I_Piece.hpp"
#include "Tetramin/O_Piece.hpp"
#include "Tetramin/L_Piece.hpp"
#include "Tetramin/J_Piece.hpp"
#include "Tetramin/T_Piece.hpp"
#include "Tetramin/S_Piece.hpp"
#include "Tetramin/Z_Piece.hpp"
using namespace std;
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
    Tetramin start_tetramin = L_Piece(screen, 0);
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
