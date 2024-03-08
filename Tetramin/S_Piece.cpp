//
// Created by riccardo on 08/03/24.
//

#include "S_Piece.hpp"
S_Piece::S_Piece(WINDOW *_screen, int yStart, int xStart, short _rotation, short _color): Tetramin(_screen, _rotation, _color) {

    int defRot[8][4][2]= {
            {{1,1},{0,0},{1,-1},{0,-2}},//0>>3
            {{-1,1},{0,0},{1,1},{2,0}},//0>>1
            {{1,-1},{0,0},{-1,-1},{-2,0}},//1>>0
            {{1,1},{0,0},{1,-1},{0,-2}},//1>>2
            {{-1,-1},{0,0},{-1,1}, {0,2}},//2>>1
            {{1,-1},{0,0},{-1,-1},{-2,0}},//2>>3
            {{-1,1},{0,0},{1,1},{2,0}},//3>>2
            {{-1,-1},{0,0},{-1,1},{0,2}}//3>>0
    };
    for(int i=0; i<8; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<2; k++){
                this->defaultRotation[i][j][k] = defRot[i][j][k];
            }
        }
    }

    if(this->rotation == 0){
        this->blocks[0].y = yStart + 1;
        this->blocks[0].x = xStart - 1;

        this->blocks[1].y = yStart + 1;
        this->blocks[1].x = xStart;


        this->blocks[2].y = yStart;
        this->blocks[2].x = xStart;

        this->blocks[3].y = yStart;
        this->blocks[3].x = xStart + 1;

    }else if(this->rotation == 1){
        this->blocks[0].y = yStart;
        this->blocks[0].x = xStart;

        this->blocks[1].y = yStart + 1;
        this->blocks[1].x = xStart;

        this->blocks[2].y = yStart + 1;
        this->blocks[2].x = xStart + 1;

        this->blocks[3].y = -0;
        this->blocks[3].x = xStart + 1;

    }else if(this->rotation == 2){
        this->blocks[0].y = yStart + 1;
        this->blocks[0].x = xStart + 1;

        this->blocks[1].y = yStart + 1;
        this->blocks[1].x = xStart;

        this->blocks[2].y = yStart + 2;
        this->blocks[2].x = xStart;

        this->blocks[3].y = yStart + 2;
        this->blocks[3].x = xStart - 1;

    }else if(this->rotation == 3){
        this->blocks[0].y = yStart + 2;
        this->blocks[0].x = xStart;

        this->blocks[1].y = yStart + 1;
        this->blocks[1].x = xStart;

        this->blocks[2].y = yStart + 1;
        this->blocks[2].x = xStart - 1;

        this->blocks[3].y = yStart;
        this->blocks[3].x = xStart - 1;

    }
}