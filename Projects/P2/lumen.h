/*
* Alen Ovalles
* lumen.h
* 4/14/2023
* CSPC 3200
*
* Implmentation History
*   4/05/2023 - Started implementation of lumen.h
*   4/13/2023 - Added a copy constructor and assignment operator,
*                updated class invariants and pre/post conditions
*/

#ifndef LUMEN_H
#define LUMEN_H
using namespace std;

class lumen{
    private:
        // Variables
        const int LOW_POWER = 0;
        const int GLOW_RESET_VALUE = 3;
        const int DEFAULT_BRIGHTNESS = 7;
        const int DEFAULT_POWER = 8;
        const int DEFAULT_SIZE = 5;

        int brightness;
        int power;
        int size;
        int glowRequests;
        bool active;
        bool stable;
    
    public:
        // Constructors
        lumen();
        lumen(int inputSize);

        // Copy Constructor
        lumen(const lumen& copy);

        // Assignment Operator
        lumen& operator=(const lumen& copy);
        // lumen& operator=(lumen const& copy);

        // Member Functions
        int glow();
        bool reset();
        bool isActive();
        bool isStable();
        void recharge();
};

#endif
