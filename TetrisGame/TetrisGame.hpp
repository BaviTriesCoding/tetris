//
// Created by riccardo on 08/03/24.
//

#ifndef TETRIS_TETRISGAME_HPP
#define TETRIS_TETRISGAME_HPP
#include "../library.h"

struct placedBlock{
    int y;
    int x;
    short color;
    placedBlock* next;
};
typedef placedBlock* placedBlockPtr;

struct gameScreen{
    WINDOW* current_screen;
    Tetramin* current_tetramin;
};

class TetrisGame {
protected:
    int points;
    placedBlockPtr blocks;
    gameScreen main, hold, next[3];
public:
    TetrisGame(WINDOW* _mainScreen);
    int play();
    void show();
    void checkLines();
    void clear();
};


#endif //TETRIS_TETRISGAME_HPP
