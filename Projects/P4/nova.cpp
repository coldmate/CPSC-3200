/*
* Alen Ovalles
* nova.cpp
* 5/19/2023
* CSPC 3200
*
* Class Invariants
*   All nova objects have valid values after their creation.
*   All nova objects have valid lumen objects.
*
*   Min/Max glow values are initialized as -1.
*   Calling the glow(int x) function will always call the lumen glow() function.
*   Calling the glow(int x) function will always start from the first lumen object up to x lumen objects.
*
*   Each lumen object in nova is determined to be persistently unstable 
*        if the object has been unstable for more than 2 glow calls.
*
*   Deep copying is supported through the copy constructor and copy assignment operator.
*   Move semantics are supported through the move constructor and move assignment operator.
*
*   Default values of the nova object constructor with parameters are used when handling errors.
*   Nova objects don't support direct comparison using the equality and relational operators.
*/

#include "lumen.h"
#include "nova.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
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
// Pre: Client enters a array of lumen objects with size of array
// Post: initalize a nova object the client input lumens 
nova::nova(lumen arr[], int size){
    if(arr == nullptr || size < 0){
        throw invalid_argument("Array of lumens can't be empty");
    }

    numOfLumens = size;
    inactiveLumens = 0;
    lumenObj = new lumen[numOfLumens];
    unstableCounter = new int[numOfLumens];
    minGlow = maxGlow = -1;
    for(int i = 0; i < numOfLumens; i++){
        lumenObj[i] = arr[i];
        unstableCounter[i] = 0;
    }
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

int nova::getNumOfLumen() const{
    return numOfLumens;
}

// Overload Operators
// Post: 
bool operator==(const nova& n1, const nova& n2){
    if (n1.numOfLumens != n2.numOfLumens || n1.inactiveLumens != n2.inactiveLumens ||
        n1.maxGlow != n2.maxGlow || n1.minGlow != n2.minGlow) {
        return false;
    }

    for (int i = 0; i < n1.numOfLumens; ++i) {
        if (n1.lumenObj[i] != n2.lumenObj[i] || n1.unstableCounter[i] != n2.unstableCounter[i]) {
            return false;
        }
    }

    return true;
}

// Post: Returns true/false for each equalivate condition
bool operator!=(const nova& n1, const nova& n2){
    return !(n1 == n2);
}

bool operator<=(const nova& n1, const nova& n2){
    return n1.numOfLumens <= n2.numOfLumens ? true : false;
}

bool operator>=(const nova& n1, const nova& n2){
    return n1.numOfLumens >= n2.numOfLumens ? true : false;
}

bool operator<(const nova& n1, const nova& n2){
    return n1.numOfLumens < n2.numOfLumens ? true : false;
}

bool operator>(const nova& n1, const nova& n2){
    return n1.numOfLumens > n2.numOfLumens ? true : false;
}

// Post: Adds a new lumen to nova's lumen array
nova& nova::operator++(){
    numOfLumens++;
    lumen* newLumens = new lumen[numOfLumens];

    for (int i = 0; i < numOfLumens - 1; ++i) {
        newLumens[i] = lumenObj[i];
    }

    newLumens[numOfLumens - 1] = lumen();
    delete[] lumenObj;
    lumenObj = newLumens;

    return *this;
}

// Post: Adds a new lumen to nova's lumen array
nova nova::operator++(int){
    nova oldNova(*this);
    oldNova.numOfLumens++;
    lumen* newLumens = new lumen[numOfLumens];

    for (int i = 0; i < numOfLumens - 1; ++i) {
        newLumens[i] = lumenObj[i];
    }

    newLumens[numOfLumens - 1] = lumen();
    delete[] lumenObj;
    lumenObj = newLumens;

    return oldNova;
}

// Post: Concatenates novas together
nova operator+(const nova& n1, const nova& n2){
    nova newNova;

    newNova.numOfLumens = n1.numOfLumens + n2.numOfLumens;
    newNova.inactiveLumens = n1.inactiveLumens + n2.inactiveLumens;
    newNova.maxGlow = max(n1.maxGlow, n2.maxGlow);
    newNova.minGlow = min(n1.minGlow, n2.minGlow);

    newNova.lumenObj = new lumen[newNova.numOfLumens];
    newNova.unstableCounter = new int[newNova.numOfLumens];

    for (int i = 0; i < n1.numOfLumens; ++i) {
        newNova.lumenObj[i] = n1.lumenObj[i];
        newNova.unstableCounter[i] = n1.unstableCounter[i];
    }

    for (int i = n1.numOfLumens; i < newNova.numOfLumens; ++i) {
        int j = i - n1.numOfLumens;
        newNova.lumenObj[i] = n2.lumenObj[j];
        newNova.unstableCounter[i] = n2.unstableCounter[j];
    }

    return newNova;
}

// Post: Increase lumen array in nova
nova operator+(const nova& n1, const unsigned int num){
    nova newNova;
    lumen * defaults = new lumen[num];

    for(int i = 0; i < int(num); i++){
        defaults[i] = lumen();
    }

    nova n2(defaults, num);

    newNova.numOfLumens = n1.numOfLumens + num;
    newNova.inactiveLumens = n1.inactiveLumens + num;
    newNova.maxGlow = max(n1.maxGlow, n2.maxGlow);
    newNova.minGlow = min(n1.minGlow, n2.minGlow);

    newNova.lumenObj = new lumen[newNova.numOfLumens];
    newNova.unstableCounter = new int[newNova.numOfLumens];

    for (int i = 0; i < n1.numOfLumens; ++i) {
        newNova.lumenObj[i] = n1.lumenObj[i];
        newNova.unstableCounter[i] = n1.unstableCounter[i];
    }

    for (int i = n1.numOfLumens; i < newNova.numOfLumens; ++i) {
        int j = i - n1.numOfLumens;
        newNova.lumenObj[i] = n2.lumenObj[j];
        newNova.unstableCounter[i] = n2.unstableCounter[j];
    }

    return newNova;
}

// Post: Increase lumen array in nova by num lumens 
nova operator+(const unsigned int num, const nova& n1){
    return n1 + num;
}

// Post: Increase lumen array in nova by num lumens 
nova operator+=(const nova& n1, const unsigned int num){
    return n1 + num;
}

// Post: Concatenates novas together
nova operator+=(const nova& n1, const nova& n2){
    return n1 + n2;
}

/*
* Class Implementation
*   The nova class should have a constructor that initializes a 
*       nova object with a default number of lumen objects
*
*   It should have a constructor that accepts an integer parameter 
*       specifying the number of lumen objects in the nova object
*   It should have a constructor that accepts an array of lumen objects 
*       and its size to initialize the nova object with the provided lumen objects
*
*   The glow() function could take an optional parameter specifying the 
*       number of lumen objects to activate and recharge
*   The getMaxGlow(), getMinGlow(), and getNumOfLumen() functions could
*        return the respective values for each condition met
*
*   The class should define overloaded operators such as ==, !=, <=, >=, <, >, ++, +, += 
*       to support comparisons, concatenation, and manipulation of nova objects
*   The class doesn't support subtraction, multiplication and division overload operators 
*       due to the limits and complicating interactions between nova objects data values
*/