//
// Created by riccardo on 28/02/24.
//

#include "library.h"

int sign(int _n){
    //ritorna il segno del numero in input e ritorna 0 se _n = 0
    if(_n > 0){return 1;}else if(_n < 0){return -1;}else{return 0;}
}