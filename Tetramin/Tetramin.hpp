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
    coordinates blocks[4]{};
    short rotation;
    short color;
    WINDOW* screen;
public:
    Tetramin(WINDOW* _screen, short _rotation, short _color);
    void show();
    void clear();
    bool canGoDirection(int _direction);
    void goDirection(int _direction);
    virtual int whatToAdd(bool _clockwise, int _startingRotation, int _testNumber, bool _x);
    virtual int canRotate(bool _clockwise);
    virtual void rotate(bool _clockwise, int _stage);
    bool evalMove(int _moveCode); //returns true if a move has been done, false otherwise;
};

class I_Piece: public Tetramin{
public:
    I_Piece(WINDOW* _screen, short _rotation, short _color = 6);
    int whatToAdd(bool _clockwise, int _startingRotation, int _testNumber, bool _x) override;
    int canRotate(bool _clockwise) override;
    void rotate(bool _clockwise, int _stage) override;
};
#endif //RANDOM_TESTS_TETRAMIN_HPP
