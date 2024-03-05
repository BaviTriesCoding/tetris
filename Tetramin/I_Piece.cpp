//
// Created by riccardo on 04/03/24.
//

#include "Tetramin.hpp"
I_Piece::I_Piece(WINDOW* _screen, short _rotation, short _color): Tetramin(_screen, _rotation, _color){
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
        this->blocks[0].x = 5;

        this->blocks[1].y = 0;
        this->blocks[1].x = 3;

        this->blocks[2].y = -1;
        this->blocks[2].x = 3;

        this->blocks[3].y = -2;
        this->blocks[3].x = 3;
    }
};

int I_Piece::whatToAdd(bool _clockwise, int _startingRotation, int _testNumber, bool _x){
    int stageAdd[8][5][2] = {
            {/* 0>>3 */{0, 0}, {0, -1},  {0, 2},  {-2,  -1}, {1,  2}},
            {/* 0>>1 */{0, 0}, {0, -2}, {0, 1}, {1,  -2}, {-2,  1}},
            {/* 1>>0 */{0, 0}, {0, 2}, {0,  -1}, {-1, 2}, {2, -1}},
            {/* 1>>2 */{0, 0}, {0, -1}, {0,  2}, {-2, -1}, {1, 2}},
            {/* 2>>1 */{0, 0}, {0, 1}, {0, -2}, {2,  1}, {-1,  -2}},
            {/* 2>>3 */{0, 0}, {0, 2}, {0, -1}, {-1,  2}, {2,  -1}},
            {/* 3>>2 */{0, 0}, {0, -2}, {0,  1}, {1, -2}, {-2, 1}},
            {/* 3>>0 */{0, 0}, {0, 1}, {0,  -2}, {2, 1}, {-1, -2}}
    };
    return stageAdd[_startingRotation*2 + int(_clockwise)][_testNumber][_x];
}

int I_Piece::canRotate(bool _clockwise) {
    int rotationCode = this->rotation * 2 + int(_clockwise);
    bool testPosition, canRotate = false;
    int y, x, test = 0;
    chtype view[4];
    WINDOW* screen = this->screen;
    switch (rotationCode){
        default:
            break;
        case 0://0>>3
            while(test<5 && !canRotate){
                testPosition = true;
                y = this->blocks[0].y + 2 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[0].x + 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[0] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[0]=' ';}

                y = this->blocks[1].y + 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[1].x + 0 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[1] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[1]=' ';}

                y = this->blocks[2].y + 0 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[2].x - 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[2] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[2]=' ';}

                y = this->blocks[3].y - 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[3].x - 2 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[3] = mvwinch(screen, y, x);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[3]=' ';}

                for(int i=0; i<4; i++){
                    testPosition = testPosition && (view[i] == ('[' | this->color) || view[i]==' ');
                }
                if(testPosition){canRotate = true;}else{test++;}
            }
            break;
        case 1://0>>1
            while(test<5 && !canRotate){
                testPosition = true;

                y = this->blocks[0].y - 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[0].x + 2 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[0] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[0]=' ';}

                y = this->blocks[1].y + 0 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[1].x + 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[1] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[1]=' ';}

                y = this->blocks[2].y + 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[2].x + 0 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[2] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[2]=' ';}

                y = this->blocks[3].y + 2 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[3].x - 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[3] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[3]=' ';}

                for(int i=0; i<4; i++){
                    testPosition = testPosition && (view[i] == ('[' | this->color) || view[i]==' ');
                }
                if(testPosition){canRotate = true;}else{test++;}
            }
            break;
        case 2://1>>0
            while(test<5 && !canRotate){
                testPosition = true;
                y = this->blocks[0].y + 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[0].x - 2 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[0] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[0]=' ';}

                y = this->blocks[1].y + 0 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[1].x - 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[1] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[1]=' ';}

                y = this->blocks[2].y - 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[2].x + 0 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[2] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[2]=' ';}

                y = this->blocks[3].y - 2 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[3].x + 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[3] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[3]=' ';}

                for(int i=0; i<4; i++){
                    testPosition = testPosition && (view[i] == ('[' | this->color) || view[i]==' ');
                }
                if(testPosition){canRotate = true;}else{test++;}
            }
            break;
        case 3://1>>2
            while(test<5 && !canRotate){
                testPosition = true;
                y = this->blocks[0].y + 2 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[0].x + 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[0] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[0]=' ';}

                y = this->blocks[1].y + 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[1].x + 0 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[1] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[1]=' ';}

                y = this->blocks[2].y + 0 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[2].x - 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[2] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[2]=' ';}

                y = this->blocks[3].y - 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[3].x - 2 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[3] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[3]=' ';}

                for(int i=0; i<4; i++){
                    testPosition = testPosition && (view[i] == ('[' | this->color) || view[i]==' ');
                }
                if(testPosition){canRotate = true;}else{test++;}
            }
            break;
        case 4://2>>1
            while(test<5 && !canRotate){
                testPosition = true;
                y = this->blocks[0].y - 2 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[0].x - 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[0] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[0]=' ';}

                y = this->blocks[1].y - 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[1].x + 0 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[1] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[1]=' ';}

                y = this->blocks[2].y + 0 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[2].x + 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[2] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[2]=' ';}

                y = this->blocks[3].y + 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[3].x + 2 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[3] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[3]=' ';}

                for(int i=0; i<4; i++){
                    testPosition = testPosition && (view[i] == ('[' | this->color) || view[i]==' ');
                }
                if(testPosition){canRotate = true;}else{test++;}
            }
            break;
        case 5://2>>3
            while(test<5 && !canRotate){
                testPosition = true;
                y = this->blocks[0].y + 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[0].x - 2 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[0] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[0]=' ';}

                y = this->blocks[1].y + 0 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[1].x - 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[1] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[1]=' ';}

                y = this->blocks[2].y - 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[2].x + 0 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[2] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[2]=' ';}

                y = this->blocks[3].y - 2 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[3].x + 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[3] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[3]=' ';}

                for(int i=0; i<4; i++){
                    testPosition = testPosition && (view[i] == ('[' | this->color) || view[i]==' ');
                }
                if(testPosition){canRotate = true;}else{test++;}
            }
            break;
        case 6://3>>2
            while(test<5 && !canRotate){
                testPosition = true;
                y = this->blocks[0].y - 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[0].x + 2 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[0] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[0]=' ';}

                y = this->blocks[1].y + 0 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[1].x + 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[1] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[1]=' ';}

                y = this->blocks[2].y + 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[2].x + 0 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[2] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[2]=' ';}

                y = this->blocks[3].y + 2 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[3].x - 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[3] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[3]=' ';}

                for(int i=0; i<4; i++){
                    testPosition = testPosition && (view[i] == ('[' | this->color) || view[i]==' ');
                }
                if(testPosition){canRotate = true;}else{test++;}
            }
            break;
        case 7://3>>0
            while(test<5 && !canRotate){
                testPosition = true;
                y = this->blocks[0].y - 2 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[0].x - 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[0] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[0]=' ';}

                y = this->blocks[1].y - 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[1].x + 0 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[1] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[1]=' ';}

                y = this->blocks[2].y + 0 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[2].x + 1 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[2] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[2]=' ';}

                y = this->blocks[3].y + 1 + this->whatToAdd(_clockwise, this->rotation, test, false);
                x = this->blocks[3].x + 2 + this->whatToAdd(_clockwise, this->rotation, test, true);
                view[3] = mvwinch(screen, y, x*2);
                if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view[3]=' ';}

                for(int i=0; i<4; i++){
                    testPosition = testPosition && (view[i] == ('[' | this->color) || view[i]==' ');
                }
                if(testPosition){canRotate = true;}else{test++;}
            }
            break;
    }
    if(!canRotate){return -1;}else{return test;}
}

void I_Piece::rotate(bool _clockwise, int _stage) {
    this->clear();
    int rotationCode = this->rotation * 2 + int(_clockwise);
    switch (rotationCode){
        default:
            if(_clockwise){this->rotation = (this->rotation + 3)%4;}else{this->rotation = (this->rotation + 1)%4;}
            break;
        case 0://0>>3
            this->blocks[0].y = this->blocks[0].y + 2 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[0].x = this->blocks[0].x + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[1].y = this->blocks[1].y + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[1].x = this->blocks[1].x + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[2].y = this->blocks[2].y + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[2].x = this->blocks[2].x - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[3].y = this->blocks[3].y - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[3].x = this->blocks[3].x - 2 + this->whatToAdd(_clockwise, this->rotation, _stage, true);
            break;
        case 1://0>>1
            this->blocks[0].y = this->blocks[0].y - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[0].x = this->blocks[0].x + 2 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[1].y = this->blocks[1].y + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[1].x = this->blocks[1].x + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);
            this->blocks[2].y = this->blocks[2].y + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[2].x = this->blocks[2].x + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[3].y = this->blocks[3].y + 2 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[3].x = this->blocks[3].x - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);
            break;
        case 2://1>>0

            this->blocks[0].y = this->blocks[0].y + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[0].x = this->blocks[0].x - 2 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[1].y = this->blocks[1].y + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[1].x = this->blocks[1].x - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[2].y = this->blocks[2].y - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[2].x = this->blocks[2].x + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[3].y = this->blocks[3].y - 2 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[3].x = this->blocks[3].x + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            break;
        case 3://1>>2
            this->blocks[0].y = this->blocks[0].y + 2 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[0].x = this->blocks[0].x + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[1].y = this->blocks[1].y + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[1].x = this->blocks[1].x + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[2].y = this->blocks[2].y + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[2].x = this->blocks[2].x - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[3].y = this->blocks[3].y - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[3].x = this->blocks[3].x - 2 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            break;
        case 4://2>>1

            this->blocks[0].y = this->blocks[0].y - 2 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[0].x = this->blocks[0].x - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[1].y = this->blocks[1].y - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[1].x = this->blocks[1].x + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[2].y = this->blocks[2].y + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[2].x = this->blocks[2].x + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[3].y = this->blocks[3].y + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[3].x = this->blocks[3].x + 2 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            break;
        case 5://2>>3

            this->blocks[0].y = this->blocks[0].y + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[0].x = this->blocks[0].x - 2 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[1].y = this->blocks[1].y + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[1].x = this->blocks[1].x - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[2].y = this->blocks[2].y - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[2].x = this->blocks[2].x + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[3].y = this->blocks[3].y - 2 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[3].x = this->blocks[3].x + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            break;
        case 6://3>>2

            this->blocks[0].y = this->blocks[0].y - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[0].x = this->blocks[0].x + 2 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[1].y = this->blocks[1].y + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[1].x = this->blocks[1].x + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[2].y = this->blocks[2].y + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[2].x = this->blocks[2].x + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[3].y = this->blocks[3].y + 2 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[3].x = this->blocks[3].x - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            break;
        case 7://3>>0
            this->blocks[0].y = this->blocks[0].y - 2 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[0].x = this->blocks[0].x - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[1].y = this->blocks[1].y - 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[1].x = this->blocks[1].x + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[2].y = this->blocks[2].y + 0 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[2].x = this->blocks[2].x + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, true);

            this->blocks[3].y = this->blocks[3].y + 1 + this->whatToAdd(_clockwise, this->rotation, _stage, false);
            this->blocks[3].x = this->blocks[3].x + 2 + this->whatToAdd(_clockwise, this->rotation, _stage, true);
            break;
    }
    if(_clockwise){this->rotation = (this->rotation + 1)%4;}else{this->rotation = (this->rotation + 3)%4;}
    this->show();
}