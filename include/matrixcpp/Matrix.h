#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

class Matrix {

public :

    int nbProcesses;

    Matrix(uint lines, uint columns);

    Matrix(uint lines, uint columns, bool shared);

    Matrix (uint lines, uint columns, float * matrix[], bool shared);

    Matrix operator * (const Matrix & mat) const;

    uint GetNbLines() const;

    uint GetNbColumns() const;

    friend ostream & operator <<(ostream &os, const Matrix &matrix);

    void Display();

    static void MultiplyWithThreads(
        const Matrix & matrix1, 
        const Matrix & matrix2,
        Matrix * solution
    );

    static void MultiplyWithForks(
        const Matrix & matrix1,
        const Matrix & matrix2,
        Matrix * solution
    );

    static void lineTimesColumnPointers(
        Matrix *solutionMatrix,
        const Matrix * mat1,
        const Matrix * mat2,
        uint line,
        uint column
    );

    virtual ~Matrix();

    static void Demo ();

private :
    unsigned int _lines;
    unsigned int _columns;

    bool _shared = false;

    float ** _elementsMatrix;

};

#endif