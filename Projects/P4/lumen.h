/*
* Alen Ovalles
* lumen.h
* 5/19/2023
* CSPC 3200
*
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
        int glowResetValue;
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
        
        // Overload Operators
        lumen& operator++();
        lumen operator++(int);

        friend lumen operator+(const lumen& l1, const lumen& l2);
        friend lumen operator+(const lumen& other, const unsigned int num);
        friend lumen operator+(const unsigned int num, const lumen& other);
        friend lumen operator+=(const lumen& l1, const lumen& l2);
        friend lumen operator+=(const lumen& other, const unsigned int num);

        friend bool operator==(const lumen& l1, const lumen& l2);
        friend bool operator!=(const lumen& l1, const lumen& l2);
        friend bool operator<=(const lumen& l1, const lumen& l2);
        friend bool operator>=(const lumen& l1, const lumen& l2);
        friend bool operator<(const lumen& l1, const lumen& l2);
        friend bool operator>(const lumen& l1, const lumen& l2);
        
        // Member Functions
        int glow();
        bool reset();
        bool isActive();
        bool isStable();
        int getBrightness() const;
        int getSize() const;
        int getPower() const;
        void recharge();
};

#endif
