//
// Created by riccardo on 08/03/24.
//
#include "TetrisGame.hpp"
TetrisGame::TetrisGame(WINDOW* _mainScreen) {
    int rows = getmaxy(_mainScreen), cols = getmaxx(_mainScreen);
    this->points = 0;
    this->main = new GameScreen(_mainScreen, 20, 20, rows/2 - 10, cols/2 - 10);
    this->hold = new GameScreen(_mainScreen, 6, 12, rows/2 - 10, cols/2 - 22);
    for(int i=0; i<3; i++){
        this->next[i] = new GameScreen(_mainScreen, 6, 12, rows/2 - 10 + 6*i, cols/2 +10);
        this->next[i]->pairTetramin(rand()%28);
    }
    this->canHold = true;
    this->gameIsOver = false;
}

void TetrisGame::checkLines() {
    int checkLine = 20, checkRow, clearedLines = 0;
    while (checkLine >= 0 && clearedLines < 4) {
        checkRow = 0;
        while (checkRow < 10 && mvwinch(this->main->current_screen, checkLine, checkRow * 2) != ' ') {
            checkRow++;
        }
        if (checkRow == 10) {
            clearedLines++;
            for (int i = checkLine; i > 0; i--) {
                for (int j = 0; j < 20; j++) {
                    mvwaddch(this->main->current_screen, checkLine, checkRow, ' ');
                    mvwaddch(this->main->current_screen, checkLine, checkRow,
                             mvwinch(this->main->current_screen, checkLine - 1, checkRow));
                    mvwaddch(this->main->current_screen, checkLine - 1, checkRow, ' ');
                }
            }
        }
        checkLine++;
    }
    this->points = this->points + 50*clearedLines*(clearedLines + 1);
}

void TetrisGame::nextTetramin() {
    this->main->pairTetramin(this->next[0]->current_tetramin_code);
    this->next[0]->pairTetramin(this->next[1]->current_tetramin_code);
    this->next[1]->pairTetramin(this->next[2]->current_tetramin_code);
    this->next[2]->pairTetramin(rand()%28);
}

void TetrisGame::holdTetramin() {
    if(this->canHold){
        if (this->hold->current_tetramin_code != -1) {
            int _main = this->main->current_tetramin_code, _hold = this->hold->current_tetramin_code;
            this->main->pairTetramin(_hold);
            this->hold->pairTetramin(_main);
        } else {
            this->nextTetramin();
        }
    }
}

void TetrisGame::placeTetramin() {
    for(int i=0; i<4; i++){
        this->gameIsOver = this->gameIsOver || this->main->current_tetramin->blocks[i].y < 0;
    }
    this->checkLines();
    this->nextTetramin();
}

int TetrisGame::play() {
    return this->points;
}