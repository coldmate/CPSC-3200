/*
* Alen Ovalles
* P2.cpp
* 4/14/2023
* CSPC 3200
*
* Implmentation History
*   4/12/2023 - Started implementation of P2.cpp
*   4/13/2023 - Implement nova functions in P2.cpp
*   4/14/2023 - Fixed driver file to initialize an collection
*                of nova objects. Also, added OVERVIEW
*
* OVERVIEW OF DRIVER FILE
*   This driver file implements a nova class that is made up
*    by a collection of lumen objects. Each lumen object
*    has a brightness, power and size 
*
*   glow(int x)
*       The function call glow() for x lumen objects in the nova array,
*         returns a value based on the state of eahc lumen object. Nova's
*         glow() function doesn't return a value but lumen's does 
*
*   getMaxGlow()
*       The function return the highest glow value each lumen object admitted
*        throuhgout the whole nova array
*
*   getMinGlow()
*       The function return the lowest glow value each lumen object admitted
*        throuhgout the whole nova array
*/

#include <iostream>
#include "nova.h"
using namespace std;

const int NUMOFLUMENOBJS = 8;

int randNum(){
    return rand() % 10 + 1;
}

void runNova(){
    nova novas[8];
    for(int i = 0; i < NUMOFLUMENOBJS; i++){
        if(i % 2 == 0){
            nova copy(randNum());
            novas[i] = copy;
        }
        else{
            novas[i] = novas[i-1];
        }
    }
    for(int i = 0; i < NUMOFLUMENOBJS; i++){
        for(int j = 0; j < randNum(); j++){
            novas[i].glow(randNum());
        }
    }
    for(int i = 0; i < NUMOFLUMENOBJS; i++){
        cout << "Nova " << i+1 << " Max Glow Value: " << novas[i].getMaxGlow() << endl;
        cout << "Nova " << i+1 << " Min Glow Value: " << novas[i].getMinGlow() << endl << endl;
    }
}

int main() {
    srand(time(0));
    cout << endl;
    cout << "-------Running Nova Objects-------" << endl << endl;
    runNova();
    return 0;
}