#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

class Matrix {

public :

    Matrix(
            const vector<vector<float>> &matrix
            );

    Matrix(uint lines, uint columns);

    Matrix operator * (const Matrix & mat) const;

    friend ostream & operator <<(ostream &os, const Matrix &matrix);

    static Matrix MultiplyWithThreads(
        const Matrix matrix1, 
        const Matrix matrix2
    );

    virtual ~Matrix();

    static void Demo ();

private :
    vector <vector<float>> _matrix;
    unsigned int lines;
    unsigned int columns;

    static void lineTimesColumn(
        Matrix *solutionMatrix,
        const Matrix mat1, 
        const Matrix mat2, 
        uint line, 
        uint column
    );

};

#endif