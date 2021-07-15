#ifndef SHAREDCALCULATOR_H
#define SHAREDCALCULATOR_H

#include <iostream>
#include <functional>
#include "Matrix.h"

using namespace std;

enum SharingType {
    THREAD,
    FORK
};

class SharedCalculator {

public :
    
    SharedCalculator (uint resultLines, uint resultColumns);

    // void process (void (*f)(Matrix *));
    template <typename F, typename P>
    void process (function<F(P)> f);

    ~SharedCalculator();

private :

    Matrix * _sharedSpaceMatrix; 

};

#endif