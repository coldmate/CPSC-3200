/*
* Alen Ovalles
* nova.h
* 4/14/2023
* CSPC 3200
*
* Implmentation History
*   4/12/2023 - Started implementation of nova.h 
*                (constructors, move semantics, member functions)
*   4/13/2023 - Added minGlow() and maxGlow() functions 
*/

#ifndef NOVA_H
#define NOVA_H
#include "lumen.h"
using namespace std;

class nova{
    private:
        // Variables
        const int DEFAULT_SIZE = 5;
        const int DEFAULT_LUMENS = 5;

        int inactiveLumens;
        int numOfLumens;
        int maxGlow;
        int minGlow;
        lumen * lumenObj;
        int * unstableCounter;

        // Member Functions
        void createLumens(int numOfLumens);
        void recharge();
        void replace(int index);
        void copying(const nova& copy);
        void minMaxGlowValue(int gValue);
    public:
        // Constructors
        nova();
        nova(int inputLumens);

        // Destructor
        ~nova();

        // Copy Constructors
        nova(const nova& copy);
        nova(nova&& copy) noexcept;

        // Assignment Operators 
        nova& operator=(const nova& copy);
        nova& operator=(nova&& copy) noexcept;

        // Member Functions 
        void glow(int index);
        int getMaxGlow() const;
        int getMinGlow() const;
};

#endif