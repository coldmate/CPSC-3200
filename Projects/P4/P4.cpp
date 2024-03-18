/*
* Alen Ovalles
* P4.cpp
* 5/19/2023
* CSPC 3200
*
* OVERVIEW OF DRIVER FILE
*   This driver file implements a nova class that is made up
*    by a collection of lumen Novas. Each lumen object
*    has a brightness, power and size 
*
*   glow(int x)
*       The function call glow() for x lumen Novas in the nova array,
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
*
*   getBrightness()
*       The function returns the brightness each lumen object 
*
*   getSize()
*       The function returns the size each lumen object 
*
*   getPower()
*       The function returns the power each lumen object 
*
*   getNumOfLumen()
*       The function returns the number of lumens in each nova object
*/

#include <iostream>
#include <memory>
#include <vector>
#include "lumen.h"
#include "nova.h"
using namespace std;

const int NUMOFNOVAS = 5;

int randNum(){
    return rand() % 10 + 1;
}

vector<shared_ptr<nova>> makeNovas(){
    vector<shared_ptr<nova>> Novas;

    for (int i = 0; i < NUMOFNOVAS; i++) {
    int lumenSize = randNum();
    unique_ptr<lumen[]> lumens(new lumen[lumenSize]);

    for (int j = 0; j < lumenSize; j++) {
        lumens[j] = lumen(randNum());
    }

    shared_ptr<nova> n(new nova(lumens.get(), lumenSize));
    Novas.push_back(n);
}

    return Novas;
}

void glowCalls(vector<shared_ptr<nova>> Novas){
    for(int i = 0; i < NUMOFNOVAS; i++) {
        cout << "---------" << endl;
        cout << "Object " << i + 1 << ":" << endl;
        cout << "---------" << endl;
        for(int j = 0; j < NUMOFNOVAS; j++) {
            cout << endl;
            cout << " Lumen " << j + 1 << ":" << endl;
            cout << "  Before glow:" << endl;
            cout << "   Minimum Glow Count: " << Novas[i]->getMinGlow() << endl;
            cout << "   Maximum Glow Count: " << Novas[i]->getMaxGlow() << endl << endl;

            Novas[i]->glow(randNum());

            cout << "  After glow:" << endl; 
            cout << "   Minimum Glow Count: " << Novas[i]->getMinGlow() << endl;
            cout << "   Maximum Glow Count: " << Novas[i]->getMaxGlow() << endl;
        }
        cout << endl;
    }
}

void novaCopying(vector<shared_ptr<nova>> Novas){
    cout << "-----------------------" << endl;
    cout << "Copying by constructor:" << endl;
    cout << "-----------------------" << endl << endl;
    cout << " Before: "<< endl;
    cout << "  First Object -  Minimum Glow Count: " << Novas[0]->getMinGlow() << endl;
    cout << "                  Maximum Glow Count: " << Novas[0]->getMaxGlow() << endl;
    cout << "  Second Object - Does not exist yet" << endl << endl;

    shared_ptr<nova> event = Novas[0];

    cout << "-----------------------" << endl;
    cout << "Copying by constructor:" << endl;
    cout << "-----------------------" << endl << endl;
    cout << " After: " << endl;
    cout << "  First Object -  Minimum Glow Count: " << Novas[0]->getMinGlow() << endl;
    cout << "                  Maximum Glow Count: " << Novas[0]->getMaxGlow() << endl;
    cout << "  Second Object - Minimum Glow Count: " << event->getMinGlow() << endl;
    cout << "                  Maximum Glow Count: " << event->getMaxGlow() << endl << endl;

    cout << "-----------" << endl;
    cout << "Assignment:" << endl;  
    cout << "-----------" << endl << endl;
    cout << " Before:" << endl;
    cout << "  First Object -  Minimum Glow Count: " << Novas[1]->getMinGlow() << endl;
    cout << "                  Maximum Glow Count: " << Novas[1]->getMaxGlow() << endl;
    cout << "  Second Object - Minimum Glow Count: " << Novas[2]->getMinGlow() << endl;
    cout << "                  Maximum Glow Count: " << Novas[2]->getMaxGlow() << endl << endl;

    Novas[2] = Novas[1];

    cout << "-----------" << endl;
    cout << "Assignment:" << endl;  
    cout << "-----------" << endl << endl;
    cout << " After:" << endl;
    cout << "  First Object -  Minimum Glow Count: " << Novas[1]->getMinGlow() << endl;
    cout << "                  Maximum Glow Count: " << Novas[1]->getMaxGlow() << endl;
    cout << "  Second Object - Minimum Glow Count: " << Novas[2]->getMinGlow() << endl;
    cout << "                  Maximum Glow Count: " << Novas[2]->getMaxGlow() << endl;
    cout << endl;
}

void novaOperators(){
    cout << "----------------------------" << endl;
    cout << "Nova Overloaded Operators..." << endl;
    cout << "----------------------------" << endl << endl;

    nova nova1;
    nova nova2;
    nova nova3 = nova1 + nova2;

    cout << "Standard Addition" << endl;
    cout << "   Number of lumen objects: " << nova3.getNumOfLumen() << endl << endl;
    
    cout << "Mixed Addition: nova + int" << endl;
    nova nova4 = nova3 + NUMOFNOVAS;
    cout << "   Number of lumen objects: " << nova4.getNumOfLumen() << endl << endl;
    
    cout << "Mixed Addition: int + nova" << endl;
    nova nova5 = NUMOFNOVAS + nova3;
    cout << "   Number of lumen objects: " << nova5.getNumOfLumen() << endl << endl;

    cout << "Pre-Increment" << endl;
    nova4++;
    cout << "   Number of lumen objects: " << nova4.getNumOfLumen() << endl << endl;

    cout << "Post-Increment" << endl;
    ++nova4;
    cout << "   Number of lumen objects: " << nova4.getNumOfLumen() << endl << endl;

    cout << "Short-Cut Assignment with nova" << endl;
    nova4 += nova3;
    cout << "   Number of lumen objects: " << nova4.getNumOfLumen() << endl << endl;

    cout << "Short-Cut Assignment with int" << endl;
    nova4 += 10;
    cout << "   Number of lumen objects: " << nova4.getNumOfLumen() << endl << endl;

    cout << "Operator: ==" << endl;
    if(nova1 == nova2) {
        cout << "   nova 1 and nova 2 are equal" << endl << endl;
    }

    cout << "Operator: !=" << endl;
    if(nova1 != nova3) {
        cout << "   nova 1 and nova 3 are not equal" << endl << endl;
    }

    cout << "Operators: > and >=" << endl;
    if(nova3 >= nova2) {
        cout << "   nova 3 is greater than or equal to nova 2" << endl << endl;
    }

    cout << "Operators: < and <=" << endl;
    if(nova3 <= nova4) {
        cout << "   nova 3 is less than or equal to nova 4" << endl << endl;
    }
}

void lumenOperators(){
    cout << "-----------------------------" << endl;
    cout << "Lumen Overloaded Operators..." << endl;
    cout << "-----------------------------" << endl << endl;

    lumen lumen1;
    lumen lumen2;
    lumen lumen3 = lumen1 + lumen2;

    cout << "Standard Addition" << endl;
    cout << "   Brightness: " << lumen3.getBrightness() << endl; 
    cout << "   Size: " << lumen3.getSize() << endl;
    cout << "   Power: " << lumen3.getPower() << endl << endl;
    
    cout << "Mixed Addition: lumen + int" << endl;
    lumen lumen4 = lumen3 + 1000;
    cout << "   Brightness: " << lumen4.getBrightness() << endl; 
    cout << "   Size: " << lumen4.getSize() << endl;
    cout << "   Power: " << lumen4.getPower() << endl << endl;

    cout << "Mixed Addition: int + lumen" << endl;
    lumen lumen5 = 1000 + lumen3;
    cout << "   Brightness: " << lumen5.getBrightness() << endl; 
    cout << "   Size: " << lumen5.getSize() << endl;
    cout << "   Power: " << lumen5.getPower() << endl << endl;

    cout << "Pre-Increment" << endl;
    lumen4++;
    cout << "   Brightness: " << lumen4.getBrightness() << endl; 
    cout << "   Size: " << lumen4.getSize() << endl;
    cout << "   Power: " << lumen4.getPower() << endl << endl;

    cout << "Post-Increment" << endl;
    ++lumen4;
    cout << "   Brightness: " << lumen4.getBrightness() << endl; 
    cout << "   Size: " << lumen4.getSize() << endl;
    cout << "   Power: " << lumen4.getPower() << endl << endl;

    cout << "Short-Cut Assignment with lumen" << endl;
    lumen4 += lumen3;
    cout << "   Brightness: " << lumen4.getBrightness() << endl; 
    cout << "   Size: " << lumen4.getSize() << endl;
    cout << "   Power: " << lumen4.getPower() << endl << endl;

    cout << "Short-Cut Assignment with int" << endl;
    lumen4 += 1000;
    cout << "   Brightness: " << lumen4.getBrightness() << endl; 
    cout << "   Size: " << lumen4.getSize() << endl;
    cout << "   Power: " << lumen4.getPower() << endl << endl;

    cout << "Operator: ==" << endl;
    if(lumen1 == lumen2) {
        cout << "  lumen 1 and lumen 2 are equal" << endl << endl;
    }

    cout << "Operator: !=" << endl;
    if(lumen1 != lumen3) {
        cout << "   lumen 1 and lumen 3 are not equal" << endl << endl;
    }

    cout << "Operators: > and >=" << endl;
    if(lumen3 >= lumen2) {
        cout << "   lumen 3 is greater than or equal to lumen 2" << endl << endl;
    }

    cout << "Operators: < and <=" << endl;
    if(lumen3 <= lumen4) {
        cout << "   lumen 3 is less than or equal to lumen 4" << endl;
    }
}

void runProgram(vector<shared_ptr<nova>> Novas){
    glowCalls(Novas);
    novaCopying(Novas);     
    novaOperators();
    lumenOperators();
}

int main() {
    srand(time(0));
    cout << endl;
    cout << "-------Running Program for Nova and Lumen Objects-------" << endl << endl;
    runProgram(makeNovas());
    cout << endl;
    return 0;
}