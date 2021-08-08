#ifndef SHAREDCALCULATOR_H
#define SHAREDCALCULATOR_H

#include <iostream>
#include <functional>
#include "Matrix.h"

using namespace std;

/**
 * @brief Container of a matrix in a shared space.
 *          The matrix can be used to perform any type of operation using 
 *          the \p process method 
 * 
 */
class SharedCalculator {

public :
    
    /**
     * @brief Construct a new Shared Calculator object
     * 
     * @param nbLines       The number of lines of the matrix 
     * @param nbColumns     The number of columns of the matrix
     */
    SharedCalculator (uint nbLines, uint nbColumns);

    /**
     * @brief   Performs a call to the given callback function 
     *          that takes the read only shared matrix as a parameter
     * 
     * @param f A callback function that takes a pointer to matrix as a
     *          parameter
     */
    void process (function<void (Matrix *)> & f);

    /**
     * @brief Destroy the Shared Calculator object
     * 
     */
    ~SharedCalculator();

private :

    /**
     * @brief A matrix that is in an inter-processes shared space 
     * 
     */
    Matrix * _sharedSpaceMatrix; 

};

#endif