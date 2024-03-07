//
// Created by riccardo on 07/03/24.
//

#include "Tetramin.hpp"

O_Piece::O_Piece(WINDOW *_screen, short _rotation, short _color): Tetramin(_screen, _rotation, _color){
    for(int i=0; i<8; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<2; k++){
                this->defaultRotation[i][j][k] = 0;
            }
        }
    }
    this->blocks[0].y = -1;
    this->blocks[0].x = 3;

    this->blocks[1].y = 0;
    this->blocks[1].x = 3;

    this->blocks[2].y = -1;
    this->blocks[2].x = 4;

    this->blocks[3].y = 0;
    this->blocks[3].x = 4;
}

int O_Piece::whatToAdd(bool _clockwise, int _startingRotation, int _testNumber, bool _x){return 0;}

int O_Piece::canRotate(bool _clockwise) {return 0;}

void O_Piece::rotate(bool _clockwise, int _stage) {}
