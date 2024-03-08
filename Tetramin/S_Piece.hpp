//
// Created by riccardo on 08/03/24.
//

#ifndef TETRIS_S_PIECE_HPP
#define TETRIS_S_PIECE_HPP

#include "Tetramin.hpp"
class S_Piece:public Tetramin {
public:
    S_Piece(WINDOW* _screen, short _rotation, short _color = 40);
};


#endif //TETRIS_S_PIECE_HPP
