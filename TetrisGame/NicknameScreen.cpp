//
// Created by jonas on 04/04/2024.
//
#include <cstring>
#include "NicknameScreen.hpp"
#include "MenuScreen.hpp"
NicknameScreen::NicknameScreen() {
    this->isActive=true;
    int xMax, yMax;
    clear();
    refresh();
    getmaxyx(stdscr, yMax, xMax);
    this->nickNameScreen = newwin(yMax/2, xMax/4, yMax/2-yMax/4, xMax/2-xMax/8);

    keypad(this->nickNameScreen, TRUE);
    printNickName();
    inputNickName();
}

void NicknameScreen::inputNickName() {
    while(isActive){
        char tmp[0];
        switch (tmp[0]=wgetch(this->nickNameScreen)) {
            case 10:
                this->isActive=false;
                break;
            case 8:
                this->nickName = this->nickName.substr(0, this->nickName.length()-1);
                break;
            default:
                if(nickName.length()<16) {
                    this->nickName += tmp[0];
                }
                break;
        }
        printNickName();
    }
    delwin(this->nickNameScreen);
    clear();
    refresh();
}

void NicknameScreen::printNickName() {
    int xMax, yMax;
    getmaxyx(this->nickNameScreen, yMax, xMax);
    wclear(this->nickNameScreen);
    box(this->nickNameScreen,0,0);
    mvwprintw(this->nickNameScreen, 5,(xMax-22)/2,"inserisci il nickname:");
    mvwprintw(this->nickNameScreen, 7,(xMax-17)/2,"-----------------");
    mvwprintw(this->nickNameScreen, 8,(xMax-17)/2,"|%s",this->nickName.c_str());
    mvwprintw(this->nickNameScreen, 8,(xMax-17)/2+16,"|");
    mvwprintw(this->nickNameScreen, 9,(xMax-17)/2,"-----------------");
    mvwprintw(this->nickNameScreen, 2, (xMax-10)/2, "BENVENUTO!");
    mvwprintw(this->nickNameScreen, 12, (xMax-24)/2, "premi invio per giocare!");
    wrefresh(this->nickNameScreen);
}

string NicknameScreen::returnNickname() {
    return this->nickName;
}
