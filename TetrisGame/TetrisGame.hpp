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
    WINDOW *time;
    bool gameIsOver;
    bool canHold;
    int acceptedInput[17];
    int milliseconds;
    int ticks;
    double playedSeconds;
public:
    TetrisGame(WINDOW* _mainScreen);
    int play();
    void checkLines();
    void nextTetramin();
    void holdTetramin();
    void placeTetramin();
    int getSafeInput();
    bool evalInput(int _input);
    double returnTime();
};


#endif //TETRIS_TETRISGAME_HPP
