//
// Created by riccardo on 04/03/24.
//

#include "I_Piece.hpp"

I_Piece::I_Piece(WINDOW* _screen, int yStart, int xStart, short _rotation, short _color): Tetramin(_screen, _rotation, _color){

    //questa matrice serve a ruotare il pezzo nella posizione di default
    // tutti i valori sono quanto bisogna sommare alle coordinate di un pezzo per portarlo nella nuova posizione dopo la rotazione
    int defRot[8][4][2]= {
            {{2,1},{1,0},{0,-1},{-1,-2}},
            {{-1,2},{0,1},{1,0},{2, -1}},
            {{1,-2},{0,-1},{-1,0},{-2,1}},
            {{2,1},{1,0},{0,-1},{-1,-2}},
            {{-2,-1},{-1,0},{0,1},{1,2}},
            {{1,-2},{0,-1},{-1,0},{-2,1}},
            {{-1,2},{0,1},{1,0},{2,-1}},
            {{-2,-1},{-1,0},{0,1},{1,2}}
    };
    for(int i=0; i<8; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<2; k++){
                this->defaultRotation[i][j][k] = defRot[i][j][k];
            }
        }
    }

    for(int n = 0; n<8; n++){
        for(int _testNumber = 0; _testNumber < 5; _testNumber++){
            for(int x = 0; x<2; x++){
                /*int stageAdd[8][5][2] = {
            {{0, 0}, {0, -1},  {0, 2},  {-2,  -1}, {1,  2}},//0>>3
            {{0, 0}, {0, -2}, {0, 1}, {1,  -2}, {-2,  1}},//0>>1
            {{0, 0}, {0, 2}, {0,  -1}, {-1, 2}, {2, -1}},//1>>0
            {{0, 0}, {0, -1}, {0,  2}, {-2, -1}, {1, 2}},//1>>2
            {{0, 0}, {0, 1}, {0, -2}, {2,  1}, {-1,  -2}},//2>>1
            {{0, 0}, {0, 2}, {0, -1}, {-1,  2}, {2,  -1}},//2>>3
            {{0, 0}, {0, -2}, {0,  1}, {1, -2}, {-2, 1}},//3>>2
            {{0, 0}, {0, 1}, {0,  -2}, {2, 1}, {-1, -2}}//3>>0*/

                int stageAdd[5][2] = {{0,  0},
                                      {0,  -1},
                                      {0,  2},
                                      {-2, -1},
                                      {1,  2}};
                int segnoX = 2 * abs(int(ceil(float(n * (-0.75)) + 1)) % 2) - 1;
                int segnoY = 2 * abs(int(ceil(float((n - 2) * (-0.75)) + 1)) % 2) - 1;
                int cambia = abs(int(ceil(float((n - 1) * (-0.5)) + 1)) % 2);
                int nonCambia = abs(int(ceil(float((n + 1) * (-0.5)) + 1)) % 2);
                int a = stageAdd[_testNumber][x];

                this->stageRotation[n][_testNumber][x] =  (x==1 ? segnoX : segnoY) * (cambia * sign(a) * (3 - abs(a)) + nonCambia * a);
            }
        }
    }


    if(this->rotation == 0){
        this->blocks[0].y = yStart + 1;
        this->blocks[0].x = xStart - 2;

        this->blocks[1].y = yStart + 1;
        this->blocks[1].x = xStart - 1;

        this->blocks[2].y = yStart + 1;
        this->blocks[2].x = xStart;

        this->blocks[3].y = yStart + 1;
        this->blocks[3].x = xStart + 1;
    }else if(this->rotation == 1){
        this->blocks[0].y = yStart;
        this->blocks[0].x = xStart - 1;

        this->blocks[1].y = yStart + 1;
        this->blocks[1].x = xStart - 1;

        this->blocks[2].y = yStart + 2;
        this->blocks[2].x = xStart - 1;

        this->blocks[3].y = yStart + 3;
        this->blocks[3].x = xStart - 1;
    }else if(this->rotation == 2){
        this->blocks[0].y = yStart + 2;
        this->blocks[0].x = xStart + 1;

        this->blocks[1].y = yStart + 2;
        this->blocks[1].x = xStart;

        this->blocks[2].y = yStart + 2;
        this->blocks[2].x = xStart - 1;

        this->blocks[3].y = yStart + 2;
        this->blocks[3].x = xStart - 2   ;
    }else if(this->rotation == 3){
        this->blocks[0].y = yStart + 3;
        this->blocks[0].x = xStart - 2;

        this->blocks[1].y = yStart + 2;
        this->blocks[1].x = xStart - 2;

        this->blocks[2].y = yStart + 1;
        this->blocks[2].x = xStart - 2;

        this->blocks[3].y = yStart;
        this->blocks[3].x = xStart - 2;
    }
};