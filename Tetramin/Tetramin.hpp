//
// Created by riccardo on 28/02/24.
//

#ifndef TETRIS_TETRAMIN_HPP
#define TETRIS_TETRAMIN_HPP
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
    Tetramin(WINDOW* _screen, short _rotation, short _color);
    void show();
    void clear();
    bool canGoDirection(int _direction);
    void goDirection(int _direction);
    void hardDrop();
    int canRotate(bool _clockwise);
    void rotate(bool _clockwise, int _stage);
};
#endif //TETRIS_TETRAMIN_HPP
