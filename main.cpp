#include "TetrisGame/TetrisGame.hpp"
int main() {
    srand(time(nullptr));
    initializeNcurses();
    auto game = TetrisGame(stdscr);
    game.play();
    nodelay(stdscr, false);
    getch();
    mvprintw(0,0, "press any button to exit");
    getch();
    endwin();
    return 0;
}
