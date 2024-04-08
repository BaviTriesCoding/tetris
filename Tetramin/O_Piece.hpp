//
// Created by riccardo on 07/03/24.
//

#ifndef TETRIS_O_PIECE_HPP
#define TETRIS_O_PIECE_HPP

#include "Tetramin.hpp"

class O_Piece: public Tetramin{
public:
    O_Piece(WINDOW* _screen, int yStart, int xStart, short _rotation, short _color = 9);
};


#endif //TETRIS_O_PIECE_HPP
