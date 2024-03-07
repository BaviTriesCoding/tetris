//
// Created by riccardo on 04/03/24.
//

#include "Tetramin.hpp"
I_Piece::I_Piece(WINDOW* _screen, short _rotation, short _color): Tetramin(_screen, _rotation, _color){

    //questa matrice serve a ruotare il pezzo nella posizione di default
    // tutti i valori sono quanto bisogna sommare alle coordinate di un pezzo per portarlo nella nuova posizione dopo la rotazione
    int defaultRotation[8][4][2] = {
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
                this->defaultRotation[i][j][k] = defaultRotation[i][j][k];
            }
        }
    }

    if(this->rotation == 0){
        this->blocks[0].y = -1;
        this->blocks[0].x = 3;

        this->blocks[1].y = -1;
        this->blocks[1].x = 4;

        this->blocks[2].y = -1;
        this->blocks[2].x = 5;

        this->blocks[3].y = -1;
        this->blocks[3].x = 6;
    }else if(this->rotation == 1){
        this->blocks[0].y = -2;
        this->blocks[0].x = 4;

        this->blocks[1].y = -1;
        this->blocks[1].x = 4;

        this->blocks[2].y = 0;
        this->blocks[2].x = 4;

        this->blocks[3].y = 1;
        this->blocks[3].x = 4;
    }else if(this->rotation == 2){
        this->blocks[0].y = 0;
        this->blocks[0].x = 6;

        this->blocks[1].y = 0;
        this->blocks[1].x = 5;

        this->blocks[2].y = 0;
        this->blocks[2].x = 4;

        this->blocks[3].y = 0;
        this->blocks[3].x = 3   ;
    }else if(this->rotation == 3){
        this->blocks[0].y = 1;
        this->blocks[0].x = 3;

        this->blocks[1].y = 0;
        this->blocks[1].x = 3;

        this->blocks[2].y = -1;
        this->blocks[2].x = 3;

        this->blocks[3].y = -2;
        this->blocks[3].x = 3;
    }
};

/*int stageAdd[8][5][2] = {
            {{0, 0}, {0, -1},  {0, 2},  {-2,  -1}, {1,  2}},//0>>3
            {{0, 0}, {0, -2}, {0, 1}, {1,  -2}, {-2,  1}},//0>>1
            {{0, 0}, {0, 2}, {0,  -1}, {-1, 2}, {2, -1}},//1>>0
            {{0, 0}, {0, -1}, {0,  2}, {-2, -1}, {1, 2}},//1>>2
            {{0, 0}, {0, 1}, {0, -2}, {2,  1}, {-1,  -2}},//2>>1
            {{0, 0}, {0, 2}, {0, -1}, {-1,  2}, {2,  -1}},//2>>3
            {{0, 0}, {0, -2}, {0,  1}, {1, -2}, {-2, 1}},//3>>2
            {{0, 0}, {0, 1}, {0,  -2}, {2, 1}, {-1, -2}}//3>>0*/
int I_Piece::whatToAdd(bool _clockwise, int _startingRotation, int _testNumber, bool _x){
    int n = _startingRotation*2 + int(_clockwise);
    int stageAdd[5][2] = {{0, 0}, {0, -1},  {0, 2},  {-2,  -1}, {1,  2}};
    int segnoX = 2 * abs(int(ceil(float(n * (-0.75)) + 1)) % 2) - 1;
    int segnoY = 2 * abs(int(ceil(float((n - 2) * (-0.75)) + 1)) % 2) - 1;
    int cambia = abs(int(ceil(float((n - 1) * (-0.5)) + 1)) % 2);
    int nonCambia = abs(int(ceil(float((n + 1) * (-0.5)) + 1)) % 2);
    int a = stageAdd[_testNumber][_x];

    return (_x?segnoX:segnoY) * (cambia * sign(a) * (3-abs(a)) + nonCambia * a);
}

int I_Piece::canRotate(bool _clockwise) {
    int rotationCode = this->rotation * 2 + int(_clockwise);
    bool testPosition, canRotate = false;
    int y, addY, x, addX, test = 0;
    chtype view[4];
    while(test<5 && !canRotate){
        testPosition = true;
        addY = this->whatToAdd(_clockwise, this->rotation, test, false);
        addX = this->whatToAdd(_clockwise, this->rotation, test, true);
        for(int i=0; i<4; i++){
            y = this->blocks[0].y + this->defaultRotation[rotationCode][i][0] + addY;
            x = this->blocks[0].x + this->defaultRotation[rotationCode][i][1] + addX;
            view[i] = mvwinch(this->screen, y, x*2);
            if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[i]=' ';}
            testPosition = testPosition && (view[i] == ('[' | this->color) || view[i]==' ');
        }
        if(testPosition){canRotate = true;}else{test++;}
    }
    if(!canRotate){return -1;}else{return test;}
}

void I_Piece::rotate(bool _clockwise, int _stage) {
    this->clear();
    int rotationCode = this->rotation * 2 + int(_clockwise);
    int addY = this->whatToAdd(_clockwise, this->rotation, _stage, false);
    int addX = this->whatToAdd(_clockwise, this->rotation, _stage, true);

    for(int i=0; i<4; i++){
        this->blocks[i].y = this->blocks[i].y + this->defaultRotation[rotationCode][i][0] + addY;
        this->blocks[i].x = this->blocks[i].x + this->defaultRotation[rotationCode][i][1] + addX;
    }
    if(_clockwise){this->rotation = (this->rotation + 1)%4;}else{this->rotation = (this->rotation + 3)%4;}
    this->show();
}