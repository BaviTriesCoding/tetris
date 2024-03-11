//
// Created by riccardo on 08/03/24.
//

#ifndef TETRIS_TETRISGAME_HPP
#define TETRIS_TETRISGAME_HPP
#include "GameScreen.hpp"

class TetrisGame {
protected:
    int points;
    GameScreen *main, *hold, *next[3];
    bool gameIsOver;
    bool canHold;
public:
    TetrisGame(WINDOW* _mainScreen);
    int play();
    void checkLines();
    void nextTetramin();
    void holdTetramin();
    void placeTetramin();
};


#endif //TETRIS_TETRISGAME_HPP
