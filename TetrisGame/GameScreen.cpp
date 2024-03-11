//
// Created by riccardo on 11/03/24.
//

#include "GameScreen.hpp"
GameScreen::GameScreen(WINDOW* _mainScreen, int _nLines, int _nColumns, int _yStart, int _xStart) {
    this->current_screen = derwin(_mainScreen, _nLines, _nColumns, _yStart, _xStart);
    this->rows = _nLines;
    this->columns = _nColumns;
    this->yStart = _yStart;
    this->xStart = _xStart;
    this->current_tetramin = nullptr;
    this->current_tetramin_code = -1;
}

void GameScreen::clear() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            mvwaddch(this->current_screen, i, j, ' ');
        }
    }
}

void GameScreen::pairTetramin(int _code){
    this->current_tetramin_code = _code;
    delete this->current_tetramin;
    if(_code < 0 || _code > 27){
        this->current_tetramin_code = -1;
        this->current_tetramin = nullptr;
    }else if(_code < 4){
        this->current_tetramin = new I_Piece(this->current_screen, this->yStart, this->xStart, _code%4);
    }else if(_code < 8){
        this->current_tetramin = new J_Piece(this->current_screen, this->yStart, this->xStart, _code%4);
    }else if(_code < 12){
        this->current_tetramin = new L_Piece(this->current_screen, this->yStart, this->xStart, _code%4);
    }else if(_code < 16){
        this->current_tetramin = new O_Piece(this->current_screen, this->yStart, this->xStart, _code%4);
    }else if(_code < 20){
        this->current_tetramin = new S_Piece(this->current_screen, this->yStart, this->xStart, _code%4);
    }else if(_code < 24){
        this->current_tetramin = new T_Piece(this->current_screen, this->yStart, this->xStart, _code%4);
    }else if(_code < 28){
        this->current_tetramin = new Z_Piece(this->current_screen, this->yStart, this->xStart, _code%4);
    }
}