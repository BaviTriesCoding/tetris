//
// Created by riccardo on 28/02/24.
//

#ifndef RANDOM_TESTS_TETRAMIN_HPP
#define RANDOM_TESTS_TETRAMIN_HPP
#include "../library.h"

struct coordinates{
    int y;
    int x;
};

class Tetramin {
protected:
    short rotation;
    WINDOW* screen;
    int defaultRotation[8][4][2];
    int stageRotation[8][5][2];
public:
    coordinates blocks[4];
    short color;
    short originalRotation;
    Tetramin(WINDOW* _screen, short _rotation, short _color);
    //1 = rosso
    //12 = blu
    //5 = viola
    //6 = azzurro
    //10 = verde (non convincente, se ne trovo uno migliore lo cambio)
    //11 = giallo
    void show();
    void clear();
    bool canGoDirection(int _direction);
    void goDirection(int _direction);
    void hardDrop();
    int canRotate(bool _clockwise);
    void rotate(bool _clockwise, int _stage);
    bool evalMove(int _moveCode); //returns true if a move has been done, false otherwise;
};
#endif //RANDOM_TESTS_TETRAMIN_HPP
