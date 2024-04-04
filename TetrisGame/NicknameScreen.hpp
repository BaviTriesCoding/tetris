//
// Created by jonas on 04/04/2024.
//

#ifndef TETRIS_NICKNAMESCREEN_HPP
#define TETRIS_NICKNAMESCREEN_HPP

#include <ncurses/ncurses.h>
#include <fstream>
#include <cstring>
using namespace std;
class NicknameScreen {
protected:
    WINDOW *nickNameScreen;
    bool isActive;
    string nickName;
    string offNickName;
public:

    NicknameScreen();
    void inputNickName();
    void showMenu();
    void printNickName();
    string returnNickname();
};


#endif //TETRIS_NICKNAMESCREEN_HPP
