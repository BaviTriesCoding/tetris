#include "TetrisGame/TetrisGame.hpp"
#include "TetrisGame/MenuScreen.hpp"
#include "TetrisGame/NicknameScreen.hpp"

/////////////////////////////////////////////////////////////////
// in questo file vengono inizializzate tutte le funzioni     //
// di base di Ncurses tramite la funzione initializeNcurses() //
// e viene avviato il gioco creando una variabile di tipo
// menuScreen.
//
//
//
//
//
//
//
//
//////////////////////////////////////////////////////////

int main() {
    srand(time(nullptr));
    initializeNcurses();
    auto Menu = MenuScreen();
    return 0;
}
