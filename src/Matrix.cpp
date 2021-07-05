//
// Created by manso on 04/06/2021.
//

#include "../include/matrixcpp/Matrix.h"
#include <vector>
#include <thread>

using namespace std;

Matrix::Matrix(
    const vector<vector<float>> &matrix) : _matrix(matrix) {}

Matrix::Matrix(uint lines, uint columns)
{
    for (uint i = 0; i < lines; ++i)
    {
        vector<float> line;
        for (uint j = 0; j < columns; ++j)
        {
            line.push_back(0);
        }
        this->_matrix.push_back(line);
    }
}

Matrix::~Matrix()
{
}

void Matrix::lineTimesColumn(
    Matrix *solutionMatrix,
    const Matrix mat1,
    const Matrix mat2,
    uint line,
    uint column)
{
    uint mat2Columns = mat2._matrix.size();
    uint mat1Lines = mat1._matrix.at(0).size();
    float sum = 0;
    for (uint i = 0; i < mat2Columns; ++i)
    {
        sum += mat1._matrix[line][i] * mat2._matrix[i][column];
    }
    solutionMatrix->_matrix[line][column] = sum;
    cout << "The solution of the element n° " << (line * mat2Columns + column) << " is : " << sum << endl;
}

Matrix Matrix::MultiplyWithThreads(
    const Matrix matrix1,
    const Matrix matrix2)
{
    uint mat1Lines = matrix1._matrix.size();
    uint mat1Columns = matrix1._matrix[0].size();
    uint mat2Lines = matrix2._matrix.size();
    uint mat2Columns = matrix2._matrix[0].size();
    if (mat1Columns != mat2Lines)
    {
        throw "Incompatible sizes";
    } 

    Matrix solutionMatrix(mat1Lines, mat2Columns);

    thread *threadTable[mat1Lines * mat2Columns];

    for (int i = 0; i < mat1Lines; ++i)
    {
        for (int j = 0; j < mat2Columns; ++j)
        {
            int index = mat2Columns * i + j;
            thread *t = new thread(
                &Matrix::lineTimesColumn,
                &solutionMatrix,
                matrix1, 
                matrix2, 
                i,
                j
            );
            threadTable[index] = t;
        }
    }

    for (int i = 0; i < mat1Lines * mat2Columns; ++i)
    {
        threadTable[i]->join();
    }

    cout << solutionMatrix << endl;

    return solutionMatrix;
}

ostream &operator<<(ostream &out, const Matrix &matrix)
{
    for (vector<float> line : matrix._matrix)
    {
        for (float element : line)
        {
            out << element << "\t";
        }
        out << endl;
    }
    return out;
}
