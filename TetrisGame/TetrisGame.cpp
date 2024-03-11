//
// Created by riccardo on 08/03/24.
//
#include "TetrisGame.hpp"
TetrisGame::TetrisGame(WINDOW* _mainScreen) {
    int rows = getmaxy(_mainScreen), cols = getmaxx(_mainScreen);
    this->points = 0;
    this->blocks = nullptr;
    this->main.current_screen = derwin(_mainScreen, 20, 20, rows/2 - 10, cols/2 - 10);
    this->main.current_tetramin = nullptr;
    this->hold.current_screen = derwin(_mainScreen, 6, 12, rows/2 - 10, cols/2 - 22);
    this->main.current_tetramin = nullptr;
    for(int i=0; i<3; i++){
        this->next[i].current_screen = derwin(_mainScreen, 6, 12, rows/2 - 10 + 6*i, cols/2 + 10);
        this->next[i].current_tetramin = pairTetramin(rand()%28, 1, 3);
    }
}

void TetrisGame::show() {
    placedBlockPtr pointer = this->blocks;
    while(pointer != nullptr){
        mvwaddch(this->main.current_screen, pointer->y, pointer->x * 2, '[' | pointer->color | A_REVERSE);
        mvwaddch(this->main.current_screen, pointer->y, pointer->x * 2 + 1, ']' | pointer->color | A_REVERSE);
        pointer = pointer -> next;
    }
    this->main.current_tetramin->show();
    this->hold.current_tetramin->show();
    for(int i=0; i<3; i++){this->next[i].current_tetramin->show();}
}

void TetrisGame::clear() {
    placedBlockPtr pointer = this->blocks;
    while(pointer != nullptr){
        mvwprintw(this->main.current_screen, pointer->y, pointer->x * 2, "  ");
        pointer = pointer -> next;
    }
    this->main.current_tetramin->clear();
    this->hold.current_tetramin->clear();
    for(int i=0; i<3; i++){this->next[i].current_tetramin->clear();}
}

void TetrisGame::checkLines() {
    int checkLine = 20, checkRow, clearedLines = 0;
    placedBlockPtr pointer = this->blocks;
    while(clearedLines < 4 && checkLine>=0){
        checkRow = 0;
        while(checkRow < 10 && mvwinch(this->main.current_screen, checkLine, checkRow)!=' '){
            checkRow++;
        }
        if(checkRow == 9){
            clearedLines++;
            this->clear();
            while(pointer!=nullptr){
                if(pointer->y < checkLine) { pointer->y = pointer->y + 1; }
            }
            this->show();


        }else{
            checkLine--;
        }
    }
}