/*
* Alen Ovalles
* lumen.cpp
* 4/14/2023
* CSPC 3200
*
* Implmentation History
*   4/05/2023 - Started implementation of lumen.cpp, added previous
*                class invariants from P1
*   4/13/2023 - Added a copy constructor and assignment operator,
*                updated class invariants and pre/post conditions
*
* Class Implementation Invariants
*   All lumen objects have positive values after its creation
*   All lumen objects have to have a size between 1 - 10
*   All lumen objects start in an active and stable state
*   All lumen object sizes, once set, can't be altered
*   
*   Calling glow() will always increase the total number of glow requests by 1
*   After calling glow(), the power will decrease
* 
*   Lumen objects can either be in an active/inactive state after each glow call
*   Lumen objects can either be in a stable/unstable state after each glow call
*   Lumen objects turn from active to inactive when power is 1/2 the defaulted power
*   Lumen objects turn from stable to unstable when power is 1/4 the defaulted power
*
*   Stable lumen objects that call recharge() will always recharge
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
    if (power > LOW_POWER && glowRequests >= GLOW_RESET_VALUE){
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

// Pre: Lumen object must be stable
// Post: Reset power to default power
void lumen::recharge(){
    isStable();
    if(stable){
        power = DEFAULT_POWER;
    }
}

/*
* Invariants: The client can create a lumen object by entering a valid size 
* or if client doesn't want to pick a size, then the DEFAULT_SIZE will be picked.
* After lumen object is initialized, size becomes readonly and cannot change afterwards.
* actualBrightness and actualPower are the values that will change when glow or reset is 
* called. On reset, acutalBrighness and actualPower get set back to their default values,
* DEFALUT_BRIGHENSS and DEFAULT_POWER are set equal to actualBrightness and actualPower.
* A lumen object's activiness and stability can alter with conditions met by
* the client calling glow and reset several times. Each lumen object is able to recharge,
* which would set their current power back to its original power but only if the lumen
* object is in a stable state
*/
