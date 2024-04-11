//
// Created by jonas on 18/03/2024.
//

#include "ScoreScreen.hpp"


/////////////////////////////////////////////////////////////////
// in questo file sono presenti tutte le funzioni relative alla
// stampa dei risultati e dei tempi dei vari giocatori
//
//
//
//
//
////////////////////////////////////////////////////////////////


//inizializzazione della classe ScoreScreen
ScoreScreen::ScoreScreen() {
    this->open = true;
    this->line=0;
    this->list_length=0;
    this->scroll_index = 7;
    int height, width;
    getmaxyx(stdscr, height, width);
    this->score_screen = newwin(height - 2, width - 2, 1, 1);
    keypad(this->score_screen, true);
    ScoreList();//funzione che gestisce la creazione della lista e della prima stampa
    wrefresh(this->score_screen);
    refresh();
    manageInput();
}

//la funzione manageInput si occupa di gestire lo scroll dei dati e l'uscita dalla schermata.
//la variabile scroll_index rappresenta la posizione della barra di scorrimento laterale della schermata
void ScoreScreen::manageInput() {
    int height, width;
    getmaxyx(stdscr, height, width);
    while(this->open){
        switch (wgetch(this->score_screen)) {
            case KEY_DOWN:
                if(this->line+(height-9)/2<this->list_length){
                    this->line+=1;//rappresenta l'indice del primo elemento della lista da stampare
                    this->scroll_index+=((float)((height-9)*2)/(float)((this->list_length*2)-(height-9)));//fa scendere la barra. vedere relazione per dettagli formula
                    print_list();
                }
                break;
            case KEY_UP:
                if(this->line>0){
                    this->line-=1;//rappresenta l'indice del primo elemento della lista da stampare
                    this->scroll_index-=((float)((height-9)*2)/(float)((this->list_length*2)-(height-9)));//fa salire la barra. vedere relazione per dettagli formula
                    print_list();
                }
                break;
            case 27://esce dalla schermata e torna al menu principale
                this->open=false;
                wclear(this->score_screen);
                wrefresh(this->score_screen);
                clear();
                refresh();
                delwin(this->score_screen);
                break;
            default:
                break;
        }
    }
}


//questa funzione si occupa di scambiare i valore tra due nodi della lista
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

//ordinamento decrescente lista
p_giocata ScoreScreen::selectionSort(){
    p_giocata tmp, tmp1;
    p_giocata max;
    tmp = this->scores;
    max = this->scores;
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

    return this->scores;
}



//questa funzione si occupa di leggere il file e crearne la relativa lista dinamica
//la creazione della lista avvine tramite la tecnica di inserimento in testa
p_giocata ScoreScreen::creaLista() {
    p_giocata head = new giocata;
    head->next = nullptr;
    ifstream test("score.txt");

    //controllo corretta apertura del file
    if (test.is_open()) {
        string line, name, time, number;
        int break1, break2, length;
        while (test) {
            while (getline(test, line)) {
                this->list_length+=1;
                //trovo gli indici in cui tagliare la stringa
                break1 = line.find(',');//carattere separatore del file di testo: nome,punteggio
                break2 = line.find('!');//carattere separatore del file di testo: punteggio!tempo
                length = line.length();

                //riempo i capi del nodo
                head->nome = line.substr(0, break1);
                head->punteggio = stoi(line.substr(break1 + 1, break2 - break1 - 1));
                head->tempo = line.substr(break2+1,length-break2-1);

                //creo il nodo sucessivo
                p_giocata tmp = new giocata;
                tmp->next = head;
                head = tmp;
            }

            //elimino il nodo iniziale date che è vuoto
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


//stampo la lista dei risultati
void ScoreScreen::print_list() {
    p_giocata head = this->scores;
    wclear(this->score_screen);
    int i = 6;//indice grafico da cui partire a scrivere
    int count_line=0;//rappresenta a quale nodo siamo
    int height, width;
    getmaxyx(stdscr, height, width);

    mvprintw(2, (width - 63) / 2, "[esc] quit     [arrow_up] scroll up    [arrow_down] scroll down");
    mvprintw(4, (width - 7) / 2, "Results");
    mvprintw(5,(width-64)/2, "----------------------------------------------------------------");
    mvprintw((int)this->scroll_index,width/2+32,"|");
    //ciclo per stampare la lista
    while(head != nullptr){
        //controllo che siamo al primo nodo da stampare
        if(count_line >= this->line){
            mvwprintw(this->score_screen,i, (width-30)/3,"nome: %s",head->nome.c_str());
            mvwprintw(this->score_screen,i, (width-30)/3+23,"punteggio: %d",head->punteggio);
            mvwprintw(this->score_screen,i, (width-30)/3+48,"tempo: %s",head->tempo.c_str());
            i+=2;
        }
        head=head->next;
        count_line+=1;
    }
    mvprintw(height-1,(width-64)/2, "----------------------------------------------------------------");
    wrefresh(this->score_screen);
    refresh();
}


//questa funzione gestisce la creazione della lista e della prima stampa della lista
void ScoreScreen::ScoreList() {
    this->scores = new giocata;
    this->scores = creaLista();
    this->scores = selectionSort();
    print_list();
}
