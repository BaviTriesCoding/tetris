//
// Created by riccardo on 08/03/24.
//
#include "TetrisGame.hpp"
TetrisGame::TetrisGame(WINDOW* _mainScreen) {
    //input accettabili
    int acIn[17] = {
            KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN,
            'a','A','w','W','d','D', 's', 'S',
            ' ', 'q', 'Q', 'e', 'E'
    };
    //inizializzazione degli input accettabili, e degli schermi di gioco
    for(int i=0; i<17; i++){
        this->acceptedInput[i] = acIn[i];
    }
    int rows = getmaxy(_mainScreen), cols = getmaxx(_mainScreen);
    this->points = 0;

    this->main = new GameScreen( 20, 20, rows/2 - 10, cols/2 - 10, -2, 5);
    this->hold = new GameScreen(6, 12, rows/2 - 10, cols/2 - 24, 1, 2);

    for(int i=0; i<3; i++){
        this->next[i] = new GameScreen(6, 12, rows/2 - 10 + 6*i, cols/2 + 12, 1, 3);
        this->next[i]->pairTetramin(rand()%28);
    }

    this->hold = new GameScreen(6, 12, rows/2 - 10, cols/2 - 24, 1, 3);
    this->main = new GameScreen( 20, 20, rows/2 - 10, cols/2 - 10, -2, 5);

    //setta che si puo tenere un pezzo, che il gioco e partito
    this->canHold = true;
    this->gameIsOver = false;
    this->milliseconds = 200;
}

void TetrisGame::checkLines() {
    int checkLine = 19, checkRow, clearedLines = 0;
    chtype moveChars;
    //check line? line e row non coincidono?
    while (checkLine >= 0 && clearedLines < 4) {
        checkRow = 0;
        //controllo la singola riga
        while (checkRow <= 9 && mvwinch(this->main->current_screen, checkLine, checkRow * 2) != ' ') {
            checkRow++;
        }
        //nel caso check row fosse 10 vuol dire che la linea e completa
        if (checkRow == 10) {
            clearedLines++;
            //trasla tutte le linee di una sotto
            for (int i = checkLine; i > 0; i--) {
                for (int j = 0; j < 20; j++) {
                    moveChars = mvwinch(this->main->current_screen, i-1, j);
                    mvwaddch(this->main->current_screen, i, j,moveChars);
                }
            }
        }else {
            checkLine--;
        }
    }
    this->points = this->points + 50*clearedLines*(clearedLines + 1);
    mvprintw(0,0, "%11d", this->points);
    if(this->milliseconds>=50){ this->milliseconds = 100 - (this->points / 1000); }
}
//aggiorna lo schermo dei prossimi tetramini
void TetrisGame::nextTetramin() {
    int semiRandom = rand()%28;
    while(semiRandom/4 == this->next[1]->current_tetramin_code/4 || semiRandom/4 == this->next[2]->current_tetramin_code/4){
        semiRandom = rand()%28;
    }
    this->main->pairTetramin(this->next[0]->current_tetramin_code);
    this->main->current_tetramin->shadowsAllowed = true;
    this->next[0]->clear();
    this->next[0]->pairTetramin(this->next[1]->current_tetramin_code);
    this->next[1]->clear();
    this->next[1]->pairTetramin(this->next[2]->current_tetramin_code);
    this->next[2]->clear();
    this->next[2]->pairTetramin(semiRandom);
}

void TetrisGame::holdTetramin() {
    if(this->canHold){
        //nel caso ci fosse un pezzo lo scambia
        if (this->hold->current_tetramin_code != -1) {
            this->hold->clear();
            this->main->current_tetramin->clear();
            int _main = this->main->current_tetramin_code;
            int _hold = this->hold->current_tetramin_code;
            this->main->pairTetramin(_hold);
            this->main->current_tetramin->shadowsAllowed = true;
            this->hold->pairTetramin(_main);
        } else { //nel caso fosse vuoto il campo del tetramino
            this->main->current_tetramin->clear();
            this->hold->pairTetramin(this->main->current_tetramin_code);
            this->nextTetramin();
        }
        this->canHold = false;
    }
}

void TetrisGame::placeTetramin() {
    //nel caso il giooc fosse appena iniziato e non ci sono tetramini in discesa
    if(this->main->current_tetramin_code!=-1){
        //piazza i singoli 4 pezzi del tetramino in posizione
        for (int i = 0; i < 4; i++) {
            if (this->main->current_tetramin->blocks[i].y >= 0) {
                mvwaddch(this->main->current_screen, this->main->current_tetramin->blocks[i].y,
                         this->main->current_tetramin->blocks[i].x * 2,
                         '(' | this->main->current_tetramin->color | A_REVERSE);
                mvwaddch(this->main->current_screen, this->main->current_tetramin->blocks[i].y,
                         this->main->current_tetramin->blocks[i].x * 2 + 1,
                         ')' | this->main->current_tetramin->color | A_REVERSE);
            }
            this->gameIsOver = this->gameIsOver || this->main->current_tetramin->blocks[i].y < 0;
        }
    }
    this->canHold = true;
    this->checkLines();
    this->nextTetramin();
}
//questa funzione controlla se ogni input inserito in un raggio di n millisecondi è valdio e restituisce l'ultimo valido
int TetrisGame::getSafeInput(){
    clock_t start, end;
    int input, i, output = ERR;
    bool found;
    start = clock();
    do{
        input = getch();
        i = 0;
        found = false;
        // controlla se l'input rientra nella categoria dei tasti
        while(i<17 && !found){
            found = (input == this->acceptedInput[i]);
            i++;
        }
        if(found){
            output=input;
        }
        end = clock();
    }while(double(end - start) <= this->milliseconds * (CLOCKS_PER_SEC/1000));
    return output;
}


//questa funzione si occupa dello spostamento del tetramino
bool TetrisGame::evalInput(int _input) {
    //_moveCode = {KEY_DOWN: goDown()} | {ARROW_LEFT: goLeft()} | {ARROW_RIGHT: goRight()} | {ARROW_UP: rotateClockwise()}
    bool madeAMove = false;
    int code;
    switch (_input) {
        default:
            break;
        case KEY_DOWN:
        case int('s'):
        case int('S'):
            if(this->main->current_tetramin->canGoDirection(0)) {
                this->main->current_tetramin->goDirection(0);
            }
            madeAMove = true;
            break;
        case KEY_RIGHT:
        case int('d'):
        case int('D'):
            if(this->main->current_tetramin->canGoDirection(1)){
                this->main->current_tetramin->goDirection(1);
                madeAMove = true;
            }
            madeAMove = true;
            break;
        case KEY_LEFT:
        case int('a'):
        case int('A'):
            if(this->main->current_tetramin->canGoDirection(-1)){
                this->main->current_tetramin->goDirection(-1);
                madeAMove = true;
            }
            madeAMove = true;
            break;
        case KEY_UP:
        case int('w'):
        case int('W'):
            code = this->main->current_tetramin->canRotate(true);
            if(code!=-1){
                this->main->current_tetramin->rotate(true, code);
                madeAMove = true;
            }
            madeAMove = true;
            break;
        case int('q'):
        case int('Q'):
            code = this->main->current_tetramin->canRotate(false);
            if(code!=-1){
                this->main->current_tetramin->rotate(false, code);
                madeAMove = true;
            }
            madeAMove = true;
            break;
        case int(' '):
            this->main->current_tetramin->hardDrop();
            this->placeTetramin();
            madeAMove = false;
            break;
        case int('e'):
        case int('E'):
            this->holdTetramin();
            break;
    }
    return madeAMove;
}

int TetrisGame::play() {
    int ticks = 0;
    bool wentDown;
    this->nextTetramin();

    while(!this->gameIsOver){
        this->evalInput(this->getSafeInput());
        ticks++;
        // fa una discesa forzata se ci si mette a spammare le rotazioni
        if(ticks==5){
            if(this->main->current_tetramin->canGoDirection(0)){
                this->main->current_tetramin->goDirection(0);
                wentDown = true;
            }else{
                if(wentDown){
                    wentDown = false;
                }else{
                    this->placeTetramin();
                }
            }
            ticks=0;
        }
    }
    delwin(this->main->current_screen);
    delwin(this->next[0]->current_screen);
    delwin(this->next[1]->current_screen);
    delwin(this->next[2]->current_screen);
    delwin(this->hold->current_screen);
    clear();
    refresh();
    return this->points;
}