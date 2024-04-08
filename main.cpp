#include "TetrisGame/TetrisGame.hpp"
#include "TetrisGame/MenuScreen.hpp"
#include "TetrisGame/NicknameScreen.hpp"
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
