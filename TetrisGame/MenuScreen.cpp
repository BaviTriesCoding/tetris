//
// Created by jonas on 18/03/2024.
//

#include "MenuScreen.hpp"
#include "ScoreScreen.hpp"
#include "NicknameScreen.hpp"
using namespace std;

MenuScreen::MenuScreen() {

    clear();
    refresh();
    NicknameScreen nickname;
    this->nickName=nickname.returnNickname();
    this->isActive = true;
    this->index_choice=0;
    refresh();

    showMenu();
}

void MenuScreen::isActiveChoice() {
    int xBox, yBox;
    getmaxyx(this->menu_window, yBox, xBox);

    if(this->index_choice==0){
        wattron(this->menu_window,A_REVERSE);
    }
    mvwprintw(this->menu_window, yBox/4, (xBox-7)/2, "New Game");
    if(this->index_choice==0){
        wattroff(this->menu_window,A_REVERSE);
    }


    if(this->index_choice==1){
        wattron(this->menu_window,A_REVERSE);
    }
    mvwprintw(this->menu_window, yBox*2/4, (xBox-10)/2, "See results");
    if(this->index_choice==1){
        wattroff(this->menu_window,A_REVERSE);
    }
    if(this->index_choice==2){
        wattron(this->menu_window,A_REVERSE);
    }
    mvwprintw(this->menu_window, yBox*3/4, (xBox-8)/2, "quit game");
    if(this->index_choice==2){
        wattroff(this->menu_window,A_REVERSE);
    }
}
void MenuScreen::renderScreen() {

    wclear(this->menu_window);
    wrefresh(this->menu_window);
    clear();
    refresh();
    delwin(this->menu_window);
    if(this->index_choice==0){
        auto game = TetrisGame(stdscr);

        this->result = game.play();
        writeResults();
        resultScreen();
        showMenu();
        refresh();
    }
    else if(this->index_choice==1){
        auto score = ScoreScreen();
        showMenu();
    }
    else if(this->index_choice==2){
        delwin(this->menu_window);
        endwin();
    }
}


void MenuScreen::resultScreen() {
    int xMax, yMax;
    refresh();
    this->index_choice=0;
    getmaxyx(stdscr, yMax, xMax);
    this->result_screen = newwin(yMax/6, xMax/4, (yMax*6)/8, xMax/3);
    box(this->result_screen,0,0);
    mvwprintw(this->result_screen, 1,1,"complimenti %s!", this->nickName.c_str());
    mvwprintw(this->result_screen, 3,1,"hai fatto %d punti!", this->result);
    wrefresh(this->result_screen);
}

void MenuScreen::showMenu() {
    this->isActive=true;
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    this->menu_window = newwin(yMax/2, xMax/4, yMax/4, xMax/3);
    keypad(this->menu_window, true);
    box(this->menu_window, 0, 0);
    isActiveChoice();
    while(isActive){
        switch (wgetch(this->menu_window)) {
            case KEY_DOWN:
                this->index_choice++;
                this->index_choice=this->index_choice%3;
                break;
            case KEY_UP:
                this->index_choice+=2;
                this->index_choice=this->index_choice%3;
                break;
            case 10:
                this->isActive = false;
                renderScreen();
            default:
                break;
        }
        isActiveChoice();
    }
}

void MenuScreen::writeResults() {
    ofstream outputFile; /* Dichiarazione di tipo */
    outputFile.open("score.txt",ios::app); /* Apertura del file */
    outputFile << this->nickName+","+ to_string(this->result)+"!"+"2:45"<< '\n';
    outputFile.close();
}

