#include "TetrisGame/TetrisGame.hpp"
#include "TetrisGame/MenuScreen.hpp"
int main() {
    srand(time(nullptr));
    initializeNcurses();
    auto menu = MenuScreen();
    //auto game = TetrisGame(stdscr);
    //game.play();
    nodelay(stdscr, false);
    getch();
    mvprintw(0,0, "press any button to exit");
    getch();
    endwin();
    return 0;
}
