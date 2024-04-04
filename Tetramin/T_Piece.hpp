//
// Created by riccardo on 08/03/24.
//

#ifndef TETRIS_T_PIECE_HPP
#define TETRIS_T_PIECE_HPP

#include "Tetramin.hpp"
class T_Piece :public Tetramin{
public:
    T_Piece(WINDOW* _screen, int yStart, int xStart, short _rotation, short _color = 5);
};


#endif //TETRIS_T_PIECE_HPP
