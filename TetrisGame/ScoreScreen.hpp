//
// Created by jonas on 18/03/2024.
//

#ifndef TETRIS_SCORESCREEN_HPP
#define TETRIS_SCORESCREEN_HPP
#include "../library.h"
#include <fstream>
#include <cstring>
using namespace std;
struct giocata{
    int punteggio;
    string tempo;
    string nome;
    giocata *next;
};
typedef giocata *p_giocata;
class ScoreScreen {
protected:
    WINDOW  *score_screen;
    p_giocata scores;
    int scroll_index;
    bool open;
    int line;
    int list_length;
public:
    void scambia( p_giocata , p_giocata);
    void print_list();
    p_giocata sort();
    p_giocata creaLista();
    ScoreScreen();
    void ScoreList();
};


#endif //TETRIS_SCORESCREEN_HPP
