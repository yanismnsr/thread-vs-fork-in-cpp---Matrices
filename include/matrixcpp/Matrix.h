#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

class Matrix {

public :

    int nbProcesses;

    Matrix(
            const vector<vector<float>> &matrix
            );

    Matrix(uint lines, uint columns);

    Matrix(uint lines, uint columns, bool shared);

    Matrix (uint lines, uint columns, float * matrix[], bool shared);

    Matrix operator * (const Matrix & mat) const;

    uint GetNbLines() const;

    uint GetNbColumns() const;

    friend ostream & operator <<(ostream &os, const Matrix &matrix);

    void Display();

    // TODO transform the parameters into pointers
    static Matrix MultiplyWithThreads(
        const Matrix & matrix1, 
        const Matrix & matrix2
    );

    static void MultiplyWithForks(
        const Matrix & matrix1,
        const Matrix & matrix2
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
    vector <vector<float>> _matrix;
    unsigned int _lines;
    unsigned int _columns;

    bool _shared = false;

    float ** _elementsMatrix;

    static void lineTimesColumn(
        Matrix *solutionMatrix,
        const Matrix mat1, 
        const Matrix mat2, 
        uint line, 
        uint column
    );

};

#endif