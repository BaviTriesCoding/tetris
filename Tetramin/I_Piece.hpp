//
// Created by riccardo on 04/03/24.
//

#ifndef FALLING_BLOCK_I_PIECE_HPP
#define FALLING_BLOCK_I_PIECE_HPP

#include "Tetramin.hpp"

class I_Piece: public Tetramin{
public:
    I_Piece(WINDOW* _screen, short _rotation, short _color = 6);
};

#endif //FALLING_BLOCK_I_PIECE_HPP
