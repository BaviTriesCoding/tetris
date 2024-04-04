//
// Created by riccardo on 07/03/24.
//

#include "O_Piece.hpp"

O_Piece::O_Piece(WINDOW *_screen, int yStart, int xStart, short _rotation, short _color): Tetramin(_screen, _rotation, _color){
    for(int i=0; i<8; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<2; k++){
                this->defaultRotation[i][j][k] = 0;
            }
        }
    }

    for(int n = 0; n<8; n++){
        for(int _testNumber = 0; _testNumber < 5; _testNumber++){
            for(int x = 0; x<2; x++){
                this->stageRotation[n][_testNumber][x] =  0;
            }
        }
    }
    this->blocks[0].y = yStart + 1;
    this->blocks[0].x = xStart - 1;

    this->blocks[1].y = yStart + 2;
    this->blocks[1].x = xStart - 1;

    this->blocks[2].y = yStart + 1;
    this->blocks[2].x = xStart;

    this->blocks[3].y = yStart + 2;
    this->blocks[3].x = xStart;
}