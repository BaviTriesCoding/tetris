//
// Created by riccardo on 28/02/24.
//

#include "Tetramin.hpp"

Tetramin::Tetramin(WINDOW* _screen, short _rotation, short _color) {
    this->rotation = _rotation % 4;
    init_pair(_color, 0, _color);
    this->color = COLOR_PAIR(_color);
    this->screen = _screen;
}

void Tetramin::show() {
    wattron(this->screen, this->color);
    for(int i=0; i<4; i++){
        if(this->blocks[i].y >=0 && this->blocks[i].y <=19 && this->blocks[i].x >=0 && this->blocks[i].x <=9){
            mvwprintw(this->screen, this->blocks[i].y, this->blocks[i].x * 2, "[]");
        }
    }
    wattroff(this->screen, this->color);
}
void Tetramin::clear() {
    for(int i=0; i<4; i++){
        if(this->blocks[i].y >=0 && this->blocks[i].y <=19 && this->blocks[i].x >=0 && this->blocks[i].x <=9){
            mvwprintw(this->screen, this->blocks[i].y, this->blocks[i].x * 2, "  ");
        }
    }
}

bool Tetramin::evalMove(int _moveCode) {
    //_moveCode = {KEY_DOWN: goDown()} | {ARROW_LEFT: goLeft()} | {ARROW_RIGHT: goRight()} | {ARROW_UP: rotateClockwise()}
    bool madeAMove = false;
    int code;
    switch (_moveCode) {
        case KEY_DOWN:
            if(this->canGoDirection(0)) {
                this->goDirection(0);
                madeAMove = true;
            }
            break;
        case KEY_RIGHT:
            if(this->canGoDirection(1)){
                this->goDirection(1);
                madeAMove = true;
            }
            break;
        case KEY_LEFT:
            if(this->canGoDirection(-1)){
                this->goDirection(-1);
                madeAMove = true;
            }
            break;
        case KEY_UP:
            code = this->canRotate(true);
            if(code!=-1){
                this->rotate(true, code);
                madeAMove = true;
            }
            break;
        case 'q':
        case 'Q':
            code = this->canRotate(false);

            if(code!=-1){
                this->rotate(false, code);
                madeAMove = true;
            }
            break;
    }
    return madeAMove;
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
            canGoDirection =canGoDirection && (view == ('[' | this->color) || view == ' ');
        }
    }
    return canGoDirection;
}

void Tetramin::goDirection(int _direction) { // | -1 = left | 0 = down | 1 = right | //
    if(_direction < -1 || _direction > 1){return;}
    int y, x;
    this->clear();
    for(int i=0; i<4; i++){
        y = this->blocks[i].y;
        x = this->blocks[i].x;
        this->blocks[i].y = this->blocks[i].y + (_direction + 1)%2;
        this->blocks[i].x = this->blocks[i].x + _direction;
    }
    this->show();
    wrefresh(this->screen);
}

int Tetramin::whatToAdd(bool _clockwise, int _startingRotation, int _testNumber, bool _x){
    int stageAdd[8][5][2] = {
            {/* 0>>3 */{0, 0}, {0, 1},  {-1, 1},  {2,  0}, {2,  1}},
            {/* 0>>1 */{0, 0}, {0, -1}, {-1, -1}, {2,  0}, {2,  -1}},
            {/* 1>>0 */{0, 0}, {0, 1},  {1,  1},  {-2, 0}, {-2, 1}},
            {/* 1>>2 */{0, 0}, {0, 1},  {1,  1},  {-2, 0}, {-2, 1}},
            {/* 2>>1 */{0, 0}, {0, -1}, {-1, -1}, {2,  0}, {2,  -1}},
            {/* 2>>3 */{0, 0}, {0, 1},  {-1, 1},  {2,  0}, {2,  1}},
            {/* 3>>2 */{0, 0}, {0, -1}, {1,  -1}, {-2, 0}, {-2, -1}},
            {/* 3>>0 */{0, 0}, {0, -1}, {1,  -1}, {-2, 0}, {-2, -1}}
    };
    return stageAdd[_startingRotation*2 + int(_clockwise)][_testNumber][_x];
}

int Tetramin::canRotate(bool _clockwise) {
    return -1;
}

void Tetramin::rotate(bool _clockwise, int _stage) {

}