//
// Created by jonas on 18/03/2024.
//

#ifndef TETRIS_SCORESCREEN_HPP
#define TETRIS_SCORESCREEN_HPP
#include <ncurses/ncurses.h>
#include <fstream>
struct result{
    char player[20];
    int points;
    result *next;
};
class ScoreScreen {
protected:
    WINDOW  *score_screen;
    result scores;
    bool open;
public:
    ScoreScreen();
    void ScoreList();
    void goToMenu();
};


#endif //TETRIS_SCORESCREEN_HPP
