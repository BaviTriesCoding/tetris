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
    scroll(this->score_screen);
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
void ScoreScreen::scambia( p_giocata tmp, p_giocata max){
    p_giocata tmp2 = new giocata;
    tmp2->punteggio=max->punteggio;
    tmp2->nome=max->nome;
    tmp2->tempo=max->tempo;
    max->tempo=tmp->tempo;
    max->nome=tmp->nome;
    max->punteggio=tmp->punteggio;
    tmp->punteggio=tmp2->punteggio;
    tmp->nome=tmp2->nome;
    tmp->tempo=tmp2->tempo;
    delete tmp2;
    tmp2 = nullptr;
}
p_giocata ScoreScreen::sort(p_giocata head){
    p_giocata tmp, tmp1;
    p_giocata max;
    tmp = head;
    max = head;
    while(tmp->next!= nullptr){
        tmp1=tmp;
        max=tmp;
        while(tmp1!= nullptr){
            if(tmp1->punteggio > max->punteggio){
                max = tmp1;
            }
            tmp1=tmp1->next;
        }
        scambia(tmp, max);
        tmp=tmp->next;
    }

    return head;
}
p_giocata ScoreScreen::creaLista() {
    p_giocata head = new giocata;
    head->next = nullptr;
    char number;
    int height, width;
    getmaxyx(stdscr, height, width);
    mvprintw(4, (width - 7) / 2, "Resluts");
    mvprintw(5, (width - 30) / 2, "------------------------------");
    int i = (width - 30) / 2;
    ifstream test("score.txt"); /* Dichiarazione di tipo */
    if (test.is_open()) {
        string line, name, time, number;
        int break1, break2, length;
        while (test) {
            while (getline(test, line)) {
                p_giocata tmp = new giocata;
                break1 = line.find(',');
                break2 = line.find('!');
                length = line.length();
                head->nome = line.substr(0, break1);
                head->punteggio = stoi(line.substr(break1 + 1, break2 - break1 - 1));
                head->tempo = line.substr(break2+1,length-break2-1);
                tmp->next = head;
                head = tmp;
            }
            p_giocata tmp = head;
            head = head->next;
            delete tmp;
            test.close();
        }
    } else {
        cout << "error";
    }
    return head;
}

void ScoreScreen::print_list(p_giocata head, int width) {
    int i = 6;

    while(head != nullptr){

        mvwprintw(this->score_screen,i, (width-30)/3,"nome: %s",head->nome.c_str());
        mvwprintw(this->score_screen,i, (width-30)/3+head->nome.length()+15,"punteggio: %d",head->punteggio);
        mvwprintw(this->score_screen,i, (width-30)/3+ to_string(head->punteggio).length()+40,"tempo: %s",head->tempo.c_str());
        head=head->next;
        i+=2;
    }
}
void ScoreScreen::ScoreList() {
    p_giocata head = new giocata;
    head = creaLista();
    head = sort(head);
    int height, width;
    char line;
    getmaxyx(stdscr, height, width);
    print_list(head, width);
    mvprintw(4,(width-7)/2, "Resluts");
    mvprintw(5,(width-64)/2, "----------------------------------------------------------------");


}