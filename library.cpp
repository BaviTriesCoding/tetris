//
// Created by riccardo on 28/02/24.
//

#include "library.h"

int sign(int _n){
    //ritorna il segno del numero in input e ritorna 0 se _n = 0
    if(_n > 0){return 1;}else if(_n < 0){return -1;}else{return 0;}
}

Tetramin* pairTetramin(int _code, WINDOW* _tetraScreen, int _yStart, int _xStart){
    if(_code < 0 || _code > 27){
        return nullptr;
    }else if(_code < 4){
        return new I_Piece(_tetraScreen, _yStart, _xStart, _code%4);
    }else if(_code < 8){
        return new J_Piece(_tetraScreen, _yStart, _xStart, _code%4);
    }else if(_code < 12){
        return new L_Piece(_tetraScreen, _yStart, _xStart, _code%4);
    }else if(_code < 16){
        return new O_Piece(_tetraScreen, _yStart, _xStart, _code%4);
    }else if(_code < 20){
        return new S_Piece(_tetraScreen, _yStart, _xStart, _code%4);
    }else if(_code < 24){
        return new T_Piece(_tetraScreen, _yStart, _xStart, _code%4);
    }else if(_code < 28){
        return new Z_Piece(_tetraScreen, _yStart, _xStart, _code%4);
    }
}