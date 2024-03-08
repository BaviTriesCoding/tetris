//
// Created by riccardo on 08/03/24.
//

#ifndef TETRIS_L_PIECE_HPP
#define TETRIS_L_PIECE_HPP

#include "Tetramin.hpp"
class L_Piece : public Tetramin {
public:
    L_Piece(WINDOW* _screen, int yStart, int xStart, short _rotation, short _color = 208);
};


#endif //TETRIS_L_PIECE_HPP
