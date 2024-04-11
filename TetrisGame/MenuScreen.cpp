//
// Created by jonas on 18/03/2024.
//
/////////////////////////////////////////////////////////////////
// in questo file sono presenti tutte le funzioni relative alla
// gestione del menu e dello spostamento tra i vari schermi come
// lo ScoreScreen, GameScreen, NicknameScreen.
//
//
//
//
//
//
//////////////////////////////////////////////////////////

#include "MenuScreen.hpp"
#include "ScoreScreen.hpp"
#include "NicknameScreen.hpp"
using namespace std;
//inizializzazione della classe MenuScreen
MenuScreen::MenuScreen() {

    clear();
    refresh();
    NicknameScreen nickname;//creazione dello schermo nickName visibile all'avvio del gioco
    this->nickName=nickname.returnNickname();
    this->index_choice=0;
    refresh();

    showMenu();//mostra il menu una volta inserito il nickname
}

//la funzione isActiveChoice ha come unico scopo il miglioramento dell'UI mostrando quale scelta si sta selezionando
void MenuScreen::isActiveChoice() {
    int xBox, yBox;
    getmaxyx(this->menu_window, yBox, xBox);

    if(this->index_choice==0){
        wattron(this->menu_window,A_REVERSE);
    }
    mvwprintw(this->menu_window, yBox/4, (xBox-9)/2, " New Game ");
    if(this->index_choice==0){
        wattroff(this->menu_window,A_REVERSE);
    }
    if(this->index_choice==1){
        wattron(this->menu_window,A_REVERSE);
    }
    mvwprintw(this->menu_window, yBox*2/4, (xBox-12)/2, " See results ");
    if(this->index_choice==1){
        wattroff(this->menu_window,A_REVERSE);
    }
    if(this->index_choice==2){
        wattron(this->menu_window,A_REVERSE);
    }
    mvwprintw(this->menu_window, yBox*3/4, (xBox-10)/2, " Quit game ");
    if(this->index_choice==2){
        wattroff(this->menu_window,A_REVERSE);
    }
    refresh();
}

//la funzione renderScreen si occupa di eseguire la scelta selezionata nel menu
void MenuScreen::renderScreen() {

    wclear(this->menu_window);
    wrefresh(this->menu_window);
    clear();
    refresh();
    delwin(this->menu_window);
    //nel caso 0 viene avviata una partia
    if(this->index_choice==0){
        auto game = TetrisGame(stdscr);
        this->result = game.play();//avvio del gioco
        this->gameTime = game.returnTime();//prende il tempo di gioco
        //queste funzioni in ordine scrivono il risultato nel file, mostrano il risultato all'utente, e ridisegnano il menu
        writeResults();
        resultScreen();
        showMenu();

    }
    //nel caso 1 viene mostrato lo schermo con tutti i risultati
    else if(this->index_choice==1){
        auto score = ScoreScreen();
        showMenu();
    }
    //nel caso 2 viene chiuso il gioco
    else if(this->index_choice==2){
        nodelay(stdscr, true);
        echo();
        clear();
        delwin(this->menu_window);
        endwin();
    }
}

//resultScreen è una funziona che mostra il risultato di un giocatore una volta finita una partita. viene mostrato
//solo quando si arriva al menu dopo una partita
void MenuScreen::resultScreen() {
    int xMax, yMax;
    refresh();
    this->index_choice=0;
    getmaxyx(stdscr, yMax, xMax);
    this->result_screen = newwin(yMax/6, xMax/4, yMax - yMax/4, xMax/2 - xMax/8);
    box(this->result_screen,0,0);
    mvwprintw(this->result_screen, 1,1,"complimenti %s!", this->nickName.c_str());
    mvwprintw(this->result_screen, 3,1,"hai fatto %d punti!", this->result);
    wrefresh(this->result_screen);
}

//showMenu è la funzione che si occupa di gestire gli input dell'utente nella schermata menu e chiamare le relative funzioni
void MenuScreen::showMenu() {
    this->isActive=true;
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    this->menu_window = newwin(yMax/2, xMax/4, yMax/2 - yMax/4, xMax/2 - xMax/8);
    keypad(this->menu_window, true);
    box(this->menu_window, 0, 0);
    isActiveChoice();
    //la variabile index_choice rappresenta l'indice della scelta corrente selezionata
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
            case 10://invio della scelta
                this->isActive = false;
                renderScreen();//viene chiamata la funzione che aggiorna lo schermo a seconda della scelta
            default:
                break;
        }
        isActiveChoice();//modifica la UI della scelta
    }
}

//questa funzione viene invocata una volta finita la parita e scrive i risultati nel file
void MenuScreen::writeResults() {
    ofstream outputFile; /* Dichiarazione di tipo */
    outputFile.open("score.txt",ios::app); /* Apertura del file */
    outputFile << this->nickName+","+ to_string(this->result)+"!"+ to_string((int)this->gameTime/60)+((int)this->gameTime%60<10?":0":":")+to_string((int)this->gameTime%60)<< '\n';
    outputFile.close();
}

