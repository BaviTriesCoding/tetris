//
// Created by riccardo on 11/03/24.
//

#ifndef TETRIS_GAMESCREEN_HPP
#define TETRIS_GAMESCREEN_HPP
#include "../library.h"

class GameScreen {
protected:
    int columns;
    int rows;
    int yStart;
    int xStart;
public:
    WINDOW* current_screen;
    Tetramin* current_tetramin;
    int current_tetramin_code;
    GameScreen(WINDOW* _mainScreen, int _nLines, int _nColumns, int _yStart, int _xStart);
    void clear();
    void pairTetramin(int _code);
};

#endif //TETRIS_GAMESCREEN_HPP
