/*
* Alen Ovalles
* lumen.cpp
* 5/19/2023
* CSPC 3200
*
* Class Invariants
*   All lumen objects have positive values after its creation
*   All lumen objects have to have a size between 1 - 10
*   All lumen objects start in an active and stable state
* 
*   The lumen object is considered active if its power is greater than half of the default power. 
*     It is considered stable if its power is greater than or equal to one-fourth of the default power.
*
*   The lumen object can be reset to its original values only if its power is above a certain threshold (LOW_POWER) 
*     and the number of glow requests is equal to or greater than a specific value (glowResetValue).
*
*   The size of the lumen object is determined based on user input in the parameterized constructor (lumen(int inputSize)). 
*   The size is obtained by taking the input size modulo 10 and adding 1 to the result.
*
*   The power of the lumen object decreases by one each time the glow() function is called.
*
*   The reset() function throws an invalid_argument exception when the reset request is invalid, 
*    specifically when the power is not above LOW_POWER or the number of glow requests is less than glowResetValue.
*/

#include "lumen.h"
#include <stdexcept>
using namespace std;

// Pre: If client decides not to input a size, 
//      then the default size will be used
// Post: Create an active, stable lumen object
lumen::lumen(){
    brightness = DEFAULT_BRIGHTNESS;
    power = DEFAULT_POWER;
    size = DEFAULT_SIZE;
    glowResetValue = GLOW_RESET_VALUE;
    glowRequests = 0;
    active = true;
    stable = true;
}

// Pre: Client is able to enter a vaild size
// Post: Create an active, stable lumen object
lumen::lumen(int inputSize){
    brightness = DEFAULT_BRIGHTNESS;
    power = DEFAULT_POWER;
    size = 1 + (inputSize % 10);
    glowRequests = 0;
    glowResetValue = 1 + (size % 3);
    active = true;
    stable = true;
}

// Pre: A lumen object must be initialized before copy
//       constructor is called with another lumen object
// Post: Successful copy of values to new lumen object
lumen::lumen(const lumen& copy){
    brightness = copy.brightness;
    power = copy.power;
    size = copy.size;
    glowRequests = copy.glowRequests;
    active = copy.active;
    stable = copy.stable;
}

// Pre: Copy constructor is called between lumen objects
// Post: Successful copy of values to new lumen object
lumen& lumen::operator=(const lumen& copy){
    if(this == &copy){
        return *this;
    }

    brightness = copy.brightness;
    power = copy.power; 
    size = copy.size;
    glowRequests = copy.glowRequests;
    active = copy.active;
    stable = copy.stable;

    return *this;
}

// Pre: Lumen object must be initialized to activate glow
// Post: Lumen object will return a value correspondoing to its
//       activeness and stability
int lumen::glow(){
    isActive();
    isStable();
    glowRequests++;
    power--;

    if (stable){
        return brightness * size;
    }
    if (!active){
        return brightness * -1;
    }
    return power * brightness - size;
}

// Pre: Lumen object must be initialized to activate reset
// Post: Lumen will be able to reset to its orginal values
//       if not fulfilled then a exception will be thrown
bool lumen::reset(){
    if (power > LOW_POWER && glowRequests >= glowResetValue){
        brightness = DEFAULT_BRIGHTNESS;
        power = DEFAULT_POWER;
        glowRequests = 0;
        active = true;
        stable = true;
        return true;
    }
    else{
        brightness--;
        throw invalid_argument("Reset Request Invalid");
        return false;
    }
}

// Pre: Lumen object must be initialized to access
// Post: Returns each respected values for each condition met
bool lumen::isActive(){
    if (power <= DEFAULT_POWER / 2){ 
        active = false;
    }
    return active;
}

bool lumen::isStable(){
    if (power <= DEFAULT_POWER / 4){
        stable = false;
    }
    return stable;
}

int lumen::getBrightness() const{
    return brightness;
}

int lumen::getSize() const{
    return size;
}

int lumen::getPower() const{
    return power;
}

// Pre: Lumen object must be stable
// Post: Reset power to default power
void lumen::recharge(){
    isStable();
    if(stable){
        power = DEFAULT_POWER;
    }
} 

// Overload Operators 
// Post: Adds lumen values together
lumen operator+(const lumen& l1, const lumen& l2){
    lumen L;
    L.brightness = l1.brightness + l2.brightness;
    L.power =  l1.power + l2.power;
    L.size = l1.size + l2.size;
    return L;
}

// Post: Adds current lumen values with num together
lumen operator+(const lumen& other, const unsigned int num){
    lumen L;
    L.brightness = other.brightness + num;
    L.power =  other.power + num;
    L.size = other.size + num;
    return L;
}

// Post: Adds current lumen values with num together
lumen operator+(const unsigned int num, const lumen& other){
    return other + num;
}

// Post: Adds lumen values together
lumen operator+=(const lumen& l1, const lumen& l2){
    return l1 + l2;
}

// Post: Adds current lumen values with num together
lumen operator+=(const lumen& other, const unsigned int num){
    return other + num;
}

// Post: Pre-Increment lumen values
lumen& lumen::operator++(){
    brightness++;
    size++;
    power++;

    return *this;
}

// Post: Post-Increment lumen values
lumen lumen::operator++(int){
    lumen old(*this);
    old.brightness++;
    old.size++;
    old.power++;
    return old;
}

// Post: Returns true/false for each equalivate condition
bool operator==(const lumen& l1, const lumen& l2){
    return l1.size == l2.size ? true : false;
}

bool operator!=(const lumen& l1, const lumen& l2){
    return l1.size != l2.size ? true : false;
}

bool operator<=(const lumen& l1, const lumen& l2){
    return l1.size <= l2.size ? true : false;
}

bool operator>=(const lumen& l1, const lumen& l2){
    return l1.size >= l2.size ? true : false;
}

bool operator<(const lumen& l1, const lumen& l2){
    return l1.size < l2.size ? true : false;
}

bool operator>(const lumen& l1, const lumen& l2){
    return l1.size > l2.size ? true : false;
}

/*
* Class Implementation
*   A default constructor lumen(), and a parameterized constructor lumen(int inputSize)
*   These constructors initialize the member variables of the class
*
*   The class defines a copy constructor lumen(const lumen& copy) 
*   An assignment operator operator= to perform deep copying of the lumen objects
*
*   glow(): This function simulates the glow of the lumen object and returns a value based on its state
*   reset(): This function resets the lumen object to its original values if certain conditions are met; otherwise, it throws an exception
*   isActive(): This function checks if the lumen object is considered active based on its power level
*   isStable(): This function checks if the lumen object is considered stable based on its power level
*   Getters: The class provides getter functions to retrieve the values of brightness, size, and power
*
*   The class overloads several operators, including +, +=, ++, and comparison operators, 
*    to provide additional functionality for manipulating and comparing lumen objects
*   The class doesn't support subtraction, multiplication and division overload operators 
*       due to the limits and complicating interactions between lumen objects data values
*/