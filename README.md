# App Tetris
<p style='display:flex; align-items:center; justify-content:center; flex-direction:row;'>
      <img src="./docs/media/1.jpg" style='widht:50%'align="left">
      <img src="./docs/media/2.jpg" style='width:50%'>
</p>
![Gioco del testris sviluppato in C++](./docs/media/1.jpg) ![Gioco del testris sviluppato in C++](./docs/media/2.jpg)
## Descrizione
Progetto svolto come parte della prova finale del corso di programmazione al primo anno di scienze informatiche 
presso l'UNIBO.

## Licenza
Proprietà intellettuale di Jonas Micocci, Riccardo Baviera e Andrea Astolfi , licenza del codice AGPL come riportato in [LICENCE.TXT](./LICENSE).

## Autori
Lista degli autori e cv riportati nel file [AUTORI.TXT](AUTORI)

## Framework e linguaggi
Per lo sviluppo dell'app sono è stato utilizzato il compilatore C++ e le seguenti librerie:

```c++
#include <ncurses.h>
#include <ctime>
#include <cstring>
```
## Installazione ed esecuzione
Di seguito la procedura per compilare ed installare l'app:

1. configurazione variabili di ambiente:
seguire le istruzione al file [istruzioni_installazione](./docs/files/documentazione.pdf)

## Comandi per giocare

I comandi del gioco sono:
```
move left: left-arrow or a-key
move rigth: right-arrow or d-key
move down: down-arrow or s-key
hard drop: space
hold piece: e-key
rotatate clockwise: arrow-up or w-key
rotate anti-clockwise: q-key
```