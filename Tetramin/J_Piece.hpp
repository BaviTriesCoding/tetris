//
// Created by riccardo on 08/03/24.
//

#ifndef TETRIS_J_PIECE_HPP
#define TETRIS_J_PIECE_HPP

#include "Tetramin.hpp"
class J_Piece :public Tetramin{
public:
    J_Piece(WINDOW* _screen, int yStart, int xStart, short _rotation, short _color = 21);
};


#endif //TETRIS_J_PIECE_HPP
