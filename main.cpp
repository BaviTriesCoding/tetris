
#include "library.h"
#include "TetrisGame/MenuScreen.hpp"
int main() {
    srand(time(nullptr));
    initializeNcurses();
    auto Menu = MenuScreen();
    nodelay(stdscr, false);
    getch();
    mvprintw(0,0, "press any button to exit");
    getch();
    endwin();
    return 0;
}
