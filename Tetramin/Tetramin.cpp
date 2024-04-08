//
// Created by riccardo on 28/02/24.
//

#include "Tetramin.hpp"

Tetramin::Tetramin(WINDOW* _screen, short _rotation, short _color) {
    this->rotation = _rotation % 4;
    init_pair(_color, _color, _color);
    this->color = COLOR_PAIR(_color);
    init_pair(_color + 100, _color, 0);
    this->shadowColor = COLOR_PAIR(_color + 100);
    this->shadowsAllowed = false;
    this->screen = _screen;
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

                int stageAdd[5][2] = {{0, 0}, {0, 1},  {-1, 1},  {2,  0}, {2,  1}};
                int segnoY = 2 * abs(int(ceil(float(n * (-0.5)) + 1)) % 2) - 1;
                int segnoX = 2 * abs(int(ceil(float((n - 2) * (-0.75)) + 1)) % 2) - 1;
                int a = stageAdd[_testNumber][x];

                this->stageRotation[n][_testNumber][x] =  (x==1 ? a * segnoX : a * segnoY);
            }
        }
    }
    for(int i=0; i<4; i++){
        this->blocks[i].y = -2;
        this->blocks[i].x = -2;
    }

}

void Tetramin::show() {
    if(this->shadowsAllowed){ this->updateShadow(); }
    for(int i=0; i<4; i++){
        if(this->shadowsAllowed && this->shadowBlocks[i].y >=0 && this->shadowBlocks[i].y <=19 && this->shadowBlocks[i].x >=0 && this->shadowBlocks[i].x <=9){
            mvwaddch(this->screen, this->shadowBlocks[i].y, this->shadowBlocks[i].x * 2, ('[' | this->shadowColor));
            mvwaddch(this->screen, this->shadowBlocks[i].y, this->shadowBlocks[i].x * 2 + 1, (']' | this->shadowColor));
        }
        if(this->blocks[i].y >=0 && this->blocks[i].y <=19 && this->blocks[i].x >=0 && this->blocks[i].x <=9){
            mvwaddch(this->screen, this->blocks[i].y, this->blocks[i].x * 2, ('[' | this->color | A_REVERSE));
            mvwaddch(this->screen, this->blocks[i].y, this->blocks[i].x * 2 + 1, (']' | this->color | A_REVERSE));
        }
    }
    wrefresh(this->screen);
    refresh();
}
void Tetramin::clear() {
    if(this->shadowsAllowed){ this->updateShadow(); }
    for(int i=0; i<4; i++){
        if(this->blocks[i].y >=0 && this->blocks[i].y <=19 && this->blocks[i].x >=0 && this->blocks[i].x <=9){
            mvwprintw(this->screen, this->blocks[i].y, this->blocks[i].x * 2, "  ");
        }
        if(this->shadowsAllowed && this->shadowBlocks[i].y >=0 && this->shadowBlocks[i].y <=19 && this->shadowBlocks[i].x >=0 && this->shadowBlocks[i].x <=9){
            mvwprintw(this->screen, this->shadowBlocks[i].y, this->shadowBlocks[i].x * 2, "  ");
        }
    }
    wrefresh(this->screen);
    refresh();
}

bool Tetramin::canGoDirection(int _direction) { // | -1 = left | 0 = down | 1 = right | //
    if(_direction !=-1 && _direction!=0 && _direction!=1){return false;}
    bool canGoDirection = true;
    int y, x;
    chtype view;
    for(int i=0; i<4; i++){
        y = this->blocks[i].y + (_direction + 1)%2;
        x = (this->blocks[i].x + _direction);
        if(y>=0){
            view = mvwinch(this->screen, y, x * 2);
            canGoDirection =canGoDirection && (view == ('[' | this->color | A_REVERSE ) || view == ('[' | this->shadowColor ) || view == ' ');
        }else{
            canGoDirection = canGoDirection && x<=9 && x>=0;
        }
    }
    return canGoDirection;
}

void Tetramin::goDirection(int _direction) { // | -1 = left | 0 = down | 1 = right | //
    if(_direction < -1 || _direction > 1){return;}
    this->clear();
    for(int i=0; i<4; i++){
        this->blocks[i].y = this->blocks[i].y + (_direction + 1)%2;
        this->blocks[i].x = this->blocks[i].x + _direction;
    }
    this->show();
}

int Tetramin::canRotate(bool _clockwise) {
    int rotationCode = this->rotation * 2 + int(_clockwise);
    bool testPosition, canRotate = false;
    int y, addY, x, addX, test = 0;
    chtype view;
    while(test<5 && !canRotate){
        testPosition = true;
        addY = this->stageRotation[rotationCode][test][0];
        addX = this->stageRotation[rotationCode][test][1];
        for(int i=0; i<4; i++){
            y = this->blocks[i].y + this->defaultRotation[rotationCode][i][0] + addY;
            x = this->blocks[i].x + this->defaultRotation[rotationCode][i][1] + addX;
            view = mvwinch(this->screen, y, x*2);
            if(y > 19 || x < 0 || x > 9){testPosition = false;}else if(y < 0){view=' ';}
            testPosition = testPosition && (view == ('[' | this->color | A_REVERSE) || view == ('[' | this->shadowColor) || view==' ');
        }
        if(testPosition){canRotate = true;}else{test++;}
    }
    if(!canRotate){return -1;}else{return test;}
}

void Tetramin::rotate(bool _clockwise, int _stage) {
    this->clear();
    int rotationCode = this->rotation * 2 + int(_clockwise);
    int addY = this->stageRotation[rotationCode][_stage][0];
    int addX = this->stageRotation[rotationCode][_stage][1];

    for(int i=0; i<4; i++){
        this->blocks[i].y = this->blocks[i].y + this->defaultRotation[rotationCode][i][0] + addY;
        this->blocks[i].x = this->blocks[i].x + this->defaultRotation[rotationCode][i][1] + addX;
    }
    if(_clockwise){this->rotation = (this->rotation + 1)%4;}else{this->rotation = (this->rotation + 3)%4;}
    this->show();
}

void Tetramin::hardDrop(){
    bool canGoDown;
    this->clear();
    do{
        canGoDown = canGoDirection(0);
        if(canGoDown){
            for(int i=0; i<4; i++){
                this->blocks[i].y = this->blocks[i].y + 1;
            }
        }
    }while(canGoDown);
    this->show();
}

void Tetramin::updateShadow() {
    for(int i=0; i<4; i++){
        this->shadowBlocks[i].y = this->blocks[i].y;
        this->shadowBlocks[i].x = this->blocks[i].x;
    }
    bool canGoDown = true;
    chtype view;
    while(canGoDown){
        for(int i=0; i<4; i++){
            view = mvwinch(this->screen, this->shadowBlocks[i].y + 1, this->shadowBlocks[i].x * 2);
            if(this->shadowBlocks[i].y + 1>=0){
                canGoDown = canGoDown && (view == ('[' | this->color | A_REVERSE) || view == ('[' | this->shadowColor) || view == ' ');
            }
        }
        if(canGoDown){
            for(int i=0; i<4; i++){ this->shadowBlocks[i].y = this->shadowBlocks[i].y + 1; }
        }
    }
}
