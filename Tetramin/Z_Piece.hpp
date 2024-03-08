//
// Created by riccardo on 08/03/24.
//

#ifndef TETRIS_Z_PIECE_HPP
#define TETRIS_Z_PIECE_HPP

#include "Tetramin.hpp"
class Z_Piece: public Tetramin{
public:
    Z_Piece(WINDOW* _screen, int yStart, int _xStart, short _rotation, short _color = 1);
};


#endif //TETRIS_Z_PIECE_HPP
