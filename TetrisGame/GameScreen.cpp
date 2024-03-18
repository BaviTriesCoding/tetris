//
// Created by riccardo on 11/03/24.
//

#include "GameScreen.hpp"
GameScreen::GameScreen(int _nLines, int _nColumns, int _yStart, int _xStart, int _yTetraStart, int _xTetraStart) {
    this->current_screen = newwin(_nLines, _nColumns, _yStart, _xStart);
    keypad(this->current_screen, true);
    nodelay(this->current_screen, true);

    this->rows = _nLines;
    this->columns = _nColumns;
    this->yStart = _yStart;
    this->xStart = _xStart;
    this->yTetraStart = _yTetraStart;
    this->xTetraStart = _xTetraStart;
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
//crea un nuovo tetramino a seconda della rotazione, ogni pezo ha 4 rotazioni
void GameScreen::pairTetramin(int _code){
    this->current_tetramin_code = _code;
    delete this->current_tetramin;
    if(_code < 0 || _code > 27){
        this->current_tetramin_code = -1;
        this->current_tetramin = nullptr;
    }else if(_code < 4){
        this->current_tetramin = new I_Piece(this->current_screen, this->yTetraStart, this->xTetraStart, _code%4);
        this->current_tetramin->show();
    }else if(_code < 8){
        this->current_tetramin = new J_Piece(this->current_screen, this->yTetraStart, this->xTetraStart, _code%4);
        this->current_tetramin->show();
    }else if(_code < 12){
        this->current_tetramin = new L_Piece(this->current_screen, this->yTetraStart, this->xTetraStart, _code%4);
        this->current_tetramin->show();
    }else if(_code < 16){
        this->current_tetramin = new O_Piece(this->current_screen, this->yTetraStart, this->xTetraStart, _code%4);
        this->current_tetramin->show();
    }else if(_code < 20){
        this->current_tetramin = new S_Piece(this->current_screen, this->yTetraStart, this->xTetraStart, _code%4);
        this->current_tetramin->show();
    }else if(_code < 24){
        this->current_tetramin = new T_Piece(this->current_screen, this->yTetraStart, this->xTetraStart, _code%4);
        this->current_tetramin->show();
    }else if(_code < 28){
        this->current_tetramin = new Z_Piece(this->current_screen, this->yTetraStart, this->xTetraStart, _code%4);
        this->current_tetramin->show();
    }
    wrefresh(this->current_screen);

}