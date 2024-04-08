//
// Created by riccardo on 11/03/24.
//

#ifndef TETRIS_GAMESCREEN_HPP
#define TETRIS_GAMESCREEN_HPP
#include "../Tetramin/I_Piece.hpp"
#include "../Tetramin/O_Piece.hpp"
#include "../Tetramin/L_Piece.hpp"
#include "../Tetramin/J_Piece.hpp"
#include "../Tetramin/T_Piece.hpp"
#include "../Tetramin/S_Piece.hpp"
#include "../Tetramin/Z_Piece.hpp"

class GameScreen {
protected:
    int columns;
    int rows;
    int yStart;
    int xStart;
    int yTetraStart;
    int xTetraStart;
public:
    WINDOW* current_screen;
    Tetramin* current_tetramin;
    int current_tetramin_code;
    GameScreen(int _nLines, int _nColumns, int _yStart, int _xStart, int _yTetraStart, int _xTetraStart);
    void clear();
    void pairTetramin(int _code);
};

#endif //TETRIS_GAMESCREEN_HPP
