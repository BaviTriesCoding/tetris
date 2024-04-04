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
    this->nickNameScreen = newwin(yMax/2, xMax/4, yMax/4, xMax/3);

    keypad(this->nickNameScreen, TRUE);
    printNickName();
    inputNickName();
}

void NicknameScreen::inputNickName() {
    while(isActive){
        char tmp[0];
        switch (tmp[0]=wgetch(this->nickNameScreen)) {
            case 10:
                if(this->nickName.length()>0){
                    this->isActive=false;
                    wclear(this->nickNameScreen);
                    delwin(this->nickNameScreen);
                    refresh();
                    showMenu();
                }
                break;
            case 8:
                this->nickName = this->nickName.substr(0, this->nickName.length()-1);
                break;
            default:
                if(nickName.length()<25) {
                    this->nickName += tmp[0];
                }
                break;
        }
        printNickName();
    }

}

void NicknameScreen::showMenu() {
    auto menu = MenuScreen();
}
void NicknameScreen::printNickName() {
    wclear(this->nickNameScreen);
    box(this->nickNameScreen,0,0);
    mvwprintw(this->nickNameScreen, 5,2,"inserisci il nickname:");
    mvwprintw(this->nickNameScreen, 7,2,"--------------------------");
    mvwprintw(this->nickNameScreen, 8,2,"|%s",this->nickName.c_str());
    mvwprintw(this->nickNameScreen, 8,27,"|");
    mvwprintw(this->nickNameScreen, 9,2,"--------------------------");
    mvwprintw(this->nickNameScreen, 2, 2, "Benvenuto!");
    mvwprintw(this->nickNameScreen, 12, 2, "premi invio giocare!");
    wrefresh(this->nickNameScreen);
}