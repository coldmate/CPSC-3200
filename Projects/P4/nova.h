/*
* Alen Ovalles
* nova.h
* 5/19/2023
* CSPC 3200
*
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
        nova increment();
    public:
        // Constructors
        nova();
        nova(lumen arr[], int size); 

        // Destructor
        ~nova();

        // Copy Constructors
        nova(const nova& copy);
        nova(nova&& copy) noexcept;

        // Assignment Operators 
        nova& operator=(const nova& copy);
        nova& operator=(nova&& copy) noexcept;

        // Overload Operators
        nova& operator++();
        nova operator++(int);

        friend nova operator+(const nova& n1, const nova& n2);
        friend nova operator+(const nova& other, const unsigned int num);
        friend nova operator+(const unsigned int num, const nova& other); 
        friend nova operator+=(const nova& n1, const nova& n2); 
        friend nova operator+=(const nova& other, const unsigned int num);

        friend bool operator==(const nova& n1, const nova& n2);
        friend bool operator!=(const nova& n1, const nova& n2);
        friend bool operator<=(const nova& n1, const nova& n2);
        friend bool operator>=(const nova& n1, const nova& n2);
        friend bool operator<(const nova& n1, const nova& n2);
        friend bool operator>(const nova& n1, const nova& n2);

        // Member Functions 
        void glow(int index);
        int getMaxGlow() const;
        int getMinGlow() const;
        int getNumOfLumen () const;
};

#endif