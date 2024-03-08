//
// Created by riccardo on 08/03/24.
//

#include "Z_Piece.hpp"
Z_Piece::Z_Piece(WINDOW *_screen, short _rotation, short _color): Tetramin(_screen, _rotation, _color) {

    int defRot[8][4][2]= {
            {{-1,-1},{0,0},{1,-1},{2,0}},//0>>3
            {{1,-1},{0,0},{1,1},{0,2}},//0>>1
            {{-1,1},{0,0},{-1,-1},{0,-2}},//1>>0
            {{-1,-1},{0,0},{1,-1},{2,0}},//1>>2
            {{1,1},{0,0},{-1,1}, {-2,0}},//2>>1
            {{-1,1},{0,0},{-1,-1},{0,-2}},//2>>3
            {{1,-1},{0,0},{1,1},{0,2}},//3>>2
            {{1,1},{0,0},{-1,1},{-2,0}}//3>>0
    };
    for(int i=0; i<8; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<2; k++){
                this->defaultRotation[i][j][k] = defRot[i][j][k];
            }
        }
    }

    if(this->rotation == 0){
        this->blocks[0].y = -1;
        this->blocks[0].x = 6;

        this->blocks[1].y = -1;
        this->blocks[1].x = 5;

        this->blocks[2].y = -2;
        this->blocks[2].x = 5;

        this->blocks[3].y = -2;
        this->blocks[3].x = 4;

    }else if(this->rotation == 1){
        this->blocks[0].y = 0;
        this->blocks[0].x = 5;

        this->blocks[1].y = -1;
        this->blocks[1].x = 5;

        this->blocks[2].y = -1;
        this->blocks[2].x = 6;

        this->blocks[3].y = -2;
        this->blocks[3].x = 6;

    }else if(this->rotation == 2){
        this->blocks[0].y = -1;
        this->blocks[0].x = 4;

        this->blocks[1].y = -1;
        this->blocks[1].x = 5;

        this->blocks[2].y = 0;
        this->blocks[2].x = 5;

        this->blocks[3].y = 0;
        this->blocks[3].x = 6;

    }else if(this->rotation == 3){
        this->blocks[0].y = -2;
        this->blocks[0].x = 5;

        this->blocks[1].y = -1;
        this->blocks[1].x = 5;

        this->blocks[2].y = -1;
        this->blocks[2].x = 4;

        this->blocks[3].y = 0;
        this->blocks[3].x = 4;

    }
}
