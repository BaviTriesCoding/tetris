//
// Created by jonas on 18/03/2024.
//

#ifndef TETRIS_MENUSCREEN_HPP
#define TETRIS_MENUSCREEN_HPP


#include "../library.h"
#include "TetrisGame.hpp"


class MenuScreen {
protected:
    bool isActive;
    WINDOW *menu_window;
    int index_choice;
    WINDOW *result_screen;
    string nickName;
    int result;
    double gameTime;
public:
    MenuScreen();
    void isActiveChoice();
    void renderScreen();
    void resultScreen();
    void showMenu();
    void writeResults();
};


#endif //TETRIS_MENUSCREEN_HPP
