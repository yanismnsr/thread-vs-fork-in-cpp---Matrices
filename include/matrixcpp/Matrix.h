#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <condition_variable>

using namespace std;

class Matrix {

public :

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

    static void lineTimesColumnThreads(
        Matrix *solutionMatrix,
        const Matrix * mat1,
        const Matrix * mat2,
        uint line,
        uint column,
        uint threadNumber
    );

    static void naiveMultiplication (
        const Matrix & mat1, 
        const Matrix & mat2,
        Matrix* solution
    );

    virtual ~Matrix();

    static void Demo ();

private :
    unsigned int _lines;
    unsigned int _columns;

    atomic<int> _nbProcesses;
    condition_variable cv;
    mutex _mt;

    bool _shared = false;

    float ** _elementsMatrix;

};

#endif