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
    mvwprintw(this->nickNameScreen, 4, 2, "Benvenuto!");
    wrefresh(this->nickNameScreen);
    inputNickName();
}

void NicknameScreen::inputNickName() {
    int count = 0;
    while(isActive){
        char tmp[0];
        switch (tmp[0]=wgetch(this->nickNameScreen)) {
            case 10:
                this->isActive=false;
                wclear(this->nickNameScreen);
                delwin(this->nickNameScreen);
                refresh();
                showMenu();
                break;
            default:
                if((int)tmp[0]!=8){
                    this->nickName+=tmp[0];
                    mvwprintw(this->nickNameScreen, 7,2,"chiave: %d", tmp[0]);

                }
                else{
                    this->nickName = this->nickName.substr(0, this->nickName.length()-1);
                }
                wclear(this->nickNameScreen);
                mvwprintw(this->nickNameScreen, 6,2,"nome: %s",this->nickName.c_str());
                wrefresh(this->nickNameScreen);
                break;
        }
    }
    count++;
}

void NicknameScreen::showMenu() {
    auto menu = MenuScreen();
}