//
// Created by jonas on 18/03/2024.
//

#ifndef TETRIS_MENUSCREEN_HPP
#define TETRIS_MENUSCREEN_HPP


#include <ncurses/ncurses.h>
#include "TetrisGame.hpp"


class MenuScreen {
protected:
    bool isActive;
    WINDOW *menu_window;
    int index_choice;
public:
    MenuScreen();
    void isActiveChoice();
    void renderScreen();

};


#endif //TETRIS_MENUSCREEN_HPP
