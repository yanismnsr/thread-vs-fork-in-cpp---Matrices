#ifndef SHAREDCALCULATOR_H
#define SHAREDCALCULATOR_H

#include <iostream>
#include <functional>
#include "Matrix.h"

using namespace std;

class SharedCalculator {

public :
    
    SharedCalculator (uint resultLines, uint resultColumns);

    // void process (void (*f)(Matrix *));
    void process (function<void (Matrix *)> & f);

    ~SharedCalculator();

private :

    Matrix * _sharedSpaceMatrix; 

};

#endif