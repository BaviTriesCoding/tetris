//
// Created by jonas on 18/03/2024.
//

#include "ScoreScreen.hpp"
#include "MenuScreen.hpp"

ScoreScreen::ScoreScreen() {
    this->open = true;
    int i = 2, height, width;
    getmaxyx(stdscr, height, width);
    this->score_screen = newwin(height - 2, width - 2, 1, 1);

    ScoreList();
    scrollok(this->score_screen,TRUE);
    wrefresh(this->score_screen);
    refresh();
    while(this->open){
        switch (wgetch(this->score_screen)) {
            case 27:
                this->open=false;
                goToMenu();
                break;
            default:
                break;
        }
    }
}

void ScoreScreen::goToMenu() {
    wclear(this->score_screen);
    wrefresh(this->score_screen);
    delwin(this->score_screen);
    refresh();
    auto menu = MenuScreen();
}

void ScoreScreen::ScoreList() {
    int height, width;
    char line;
    getmaxyx(stdscr, height, width);
    mvprintw(4,(width-7)/2, "Resluts");
    mvprintw(5,(width-30)/2, "------------------------------");
    ifstream inputFile ("./score.txt"); //* Dichiarazione di tipo *//*
    int i=(width-30)/2;
    if(inputFile.is_open()){
        int j=6;
        int flag=0;
        while(inputFile){
            line = inputFile.get();
            mvwprintw(this->score_screen,j,i, "%C",line);
            if(line==':' || flag!=0){
                flag++;
            }
            if(flag==3){

                j+=2;
                flag=0;
                i=(width-30)/2-2;

            }
            i++;
        }
    }
    else{

    }
    inputFile.close();

}