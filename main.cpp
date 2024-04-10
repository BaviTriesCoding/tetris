#include "TetrisGame/TetrisGame.hpp"
#include "TetrisGame/MenuScreen.hpp"
#include "TetrisGame/NicknameScreen.hpp"
int main() {
    srand(time(nullptr));
    initializeNcurses();
    auto Menu = MenuScreen();
    return 0;
}
