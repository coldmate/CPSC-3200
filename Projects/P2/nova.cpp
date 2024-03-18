/*
* Alen Ovalles
* nova.cpp
* 4/14/2023
* CSPC 3200

* Implmentation History
*   4/12/2023 - Started implementation of nova.cpp
*   4/13/2023 - Implementated copy constructors, assignment operators 
*                and member functions (glow, rechange, getMinGlow, getMaxGlow)
*   4/14/2023 - Write in the pre/post conditions for constructors, destructor
*                copy constructors, assignment operators, member functions and
*                the class implementation invariants
*
* Class Implementation Invariants
*   All nova objects have valid values after its creation
*   All nova objects have valid lumen objects 
*   
*   Min/Max are initialized as -1, 
*   Calling glow(int x) will always call the lumen glow() function
*   Calling glow(int x) will always start from the first lumen object up to x lumen object
*
*   Each lumen object in nova is determined to be persistently unstable if the object
*    has been unstable for more than 2 glow calls
*
*   Deep copying is supported (Copy constructor and Copy assignement operator)
*   Move constructor and Move assignment operator is also supported
*   Default values of nova object constructor with parameters, used when handling errors
*/

#include "lumen.h"
#include "nova.h"
#include <algorithm>
using namespace std;

// Private Member Functions
// Pre: nova construtor is being initialized
// Post: populate array of objects with valid lumen objects
void nova::createLumens(int numOfLumens){
    for(int i = 0; i < numOfLumens; i++){
        lumenObj[i] = lumen(i);
        unstableCounter[i] = 0;
    }
}   

// Pre: nova glow() function is called
// Post: each lumen object in nova can recharge with 
//        with a valid state of stable
void nova::recharge(){
    inactiveLumens = 0;

    for(int i = 0; i < numOfLumens; i++){
        if(!(lumenObj[i].isActive())){
            inactiveLumens++;
        }
    }

    for(int i = 0; i < numOfLumens; i++){
        if(!(lumenObj[i].isStable())){
            unstableCounter[i] += 1;
        }
    }

    if(inactiveLumens >= numOfLumens / 2){
        for(int i = 0; i < numOfLumens; i++){
            if(unstableCounter[i] >= 2){
                replace(i);
                unstableCounter[i] = 0;
            }
            lumenObj[i].recharge();
        }
    }
}

// Pre: nova glow() then recharge() function is called
// Post: replaces a lumen object at a certain index in nova with 
//        with a new lumen object using the default constructor
void nova::replace(int index){
    lumen newLumen;
    lumenObj[index] = newLumen;
}

// Pre: copy constructor of nova is called
// Post: copy values to new nova object
void nova::copying(const nova& copy) {
    numOfLumens = copy.numOfLumens;
    lumenObj = new lumen[numOfLumens];
    unstableCounter = new int[numOfLumens];
    for(int i = 0; i < numOfLumens; i++){
        lumenObj[i] = copy.lumenObj[i];
        unstableCounter[i] = copy.unstableCounter[i];
    }

    maxGlow = copy.maxGlow;
    minGlow = copy.minGlow;
    inactiveLumens = copy.inactiveLumens;
}

// Pre: nova glow() fucntion is called
// Post: check and update min/max glow value of the 
//        whole array of lumen objects in nova object
void nova::minMaxGlowValue(int gValue){
    if(gValue > maxGlow || maxGlow == -1){
        maxGlow = gValue;
    }
    if(gValue < minGlow || minGlow == -1){
        minGlow = gValue;
    }
}

// Default Constructor 
// Pre: client doesn't enter a value for number of lumen objects
// Post: initialize a nova object with default valeus
nova::nova(){
    numOfLumens = DEFAULT_LUMENS;
    inactiveLumens = 0;
    lumenObj = new lumen[numOfLumens];
    unstableCounter = new int[numOfLumens];
    minGlow = maxGlow = -1;
    createLumens(numOfLumens);
}

// Constructor
// Pre: client enters a valid number of lumen objects
// Post: initialize a nova object with client input
nova::nova(int inputLumens){
    if(inputLumens <= 0){
        inputLumens = DEFAULT_LUMENS;
    }

    numOfLumens = inputLumens;
    inactiveLumens = 0;
    lumenObj = new lumen[numOfLumens];
    unstableCounter = new int[numOfLumens];
    minGlow = maxGlow = -1;
    createLumens(numOfLumens);
}

// Destructor
// Pre: a nova object must be intialized 
// Post: will dealocate memory of the dynamic arrays
nova::~nova(){
    if(lumenObj){
        delete lumenObj;
        delete unstableCounter;
    }
}

// Copy Construtor
// Pre: A nova object must be initialized before copy
//       constructor is called with another nova object
// Post: Successful copy of values to new nova object
nova::nova(const nova& copy){   
    copying(copy);
}

// Move Copy Constructor
// Pre: A nova object must be initialized before move copy
//       constructor is called with another nova object
// Post: Successful move values to new nova object
nova::nova(nova&& copy) noexcept {
    lumenObj = copy.lumenObj;
    unstableCounter = copy.unstableCounter;
    numOfLumens = copy.numOfLumens;
    maxGlow = copy.maxGlow;
    minGlow = copy.minGlow;
    inactiveLumens = copy.inactiveLumens;

    copy.inactiveLumens = 0;
    copy.numOfLumens = 0;
    copy.maxGlow = 0;
    copy.minGlow = 0;
    copy.lumenObj = nullptr;
    copy.unstableCounter = nullptr;
}

// Overloaded Assignment Operator
// Pre: Copy constructor is called between nova objects
// Post: Successful copy of values to new nova object
nova& nova::operator=(const nova& copy){
    if(this == &copy){
        return *this;
    }

    delete[] lumenObj;
    delete[] unstableCounter;

    copying(copy);

    return *this;
}

// Move Assignment Operator 
// Pre: Move copy constructor is called between nova objects
// Post: Successful move values to new nova object
nova& nova::operator=(nova&& copy) noexcept {
    if(this == &copy){
        return *this;
    }
    swap(lumenObj, copy.lumenObj);
    swap(unstableCounter, copy.unstableCounter);
    swap(inactiveLumens, copy.inactiveLumens);
    swap(numOfLumens, copy.numOfLumens);
    swap(maxGlow, copy.maxGlow);
    swap(minGlow, copy.minGlow);

    return *this;
}

// Public Memeber Functions
// Pre: nova object with lumen objects initialized 
// Post: lumen objects in nova array could be recharged 
//        depending on state
void nova::glow(int index){
    int gValue;

    if(index > numOfLumens){
        index = numOfLumens;    
    }
    if(index <= 0){
        index = 1; 
    }

    for(int i = 0; i < index; i++){
        gValue = lumenObj[i].glow();
        minMaxGlowValue(gValue);
    }
    recharge();
}

// Pre: nova object must be initialized to access
// Post: Returns each respected values for each condition met
int nova::getMaxGlow() const {
    return maxGlow;
}

int nova::getMinGlow() const {
    return minGlow;
}
