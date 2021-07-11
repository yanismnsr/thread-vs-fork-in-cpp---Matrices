//
// Created by manso on 04/06/2021.
//

#include "../include/matrixcpp/Matrix.h"
#include <vector>
#include <thread>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

using namespace std;

Matrix::Matrix(
    const vector<vector<float>> &matrix) : _matrix(matrix) {}

Matrix::Matrix(uint lines, uint columns) : nbProcesses(0)
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

Matrix::Matrix(uint lines, uint columns, bool shared) {
    _shared = shared;
    if (shared) {
        // Creating the shared memory space for the container of lines (table of tables)
        _elementsMatrix = (float**)mmap(
            NULL, 
            sizeof(float*) * lines,
            PROT_READ | PROT_WRITE,
            MAP_SHARED | MAP_ANONYMOUS, 
            -1,
            0
        );

        // Creating shared memory space for lines
        for (int i = 0; i < lines; ++i) {
            _elementsMatrix[i] = (float*)mmap(
                NULL,
                sizeof(float) * columns,
                PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS,
                -1, 
                0
            );
            // Initializing the line with 0's
            float elements[columns] = {0};
            memcpy(_elementsMatrix[i], &elements, columns * sizeof(float));
        }

    } else {
        _elementsMatrix = new float*[lines];
        for (int i = 0; i < lines; ++i) {
            _elementsMatrix[i] = {new float[columns]{}};
        }
    }

    // Initializing lines and columns
    _lines = lines;
    _columns = columns;

}

Matrix::Matrix (uint lines, uint columns, float ** matrix, bool shared) {
    _shared = shared;
    if (shared) {
        // Creating the shared memory space for the container of lines (table of tables)
        _elementsMatrix = (float**)mmap(
            NULL, 
            sizeof(float*) * lines,
            PROT_READ | PROT_WRITE,
            MAP_SHARED | MAP_ANONYMOUS, 
            -1,
            0
        );

        // Creating shared memory space for lines
        for (int i = 0; i < lines; ++i) {
            _elementsMatrix[i] = (float*)mmap(
                NULL,
                sizeof(float) * columns,
                PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS,
                -1, 
                0
            );
            // Initializing the line
            memcpy (_elementsMatrix[i], matrix[i], sizeof(float) * columns);
        }

    } else {
        _elementsMatrix = new float*[lines];
        for (int i = 0; i < lines; ++i) {
            _elementsMatrix[i] = new float[columns]();
            memcpy(_elementsMatrix[i], matrix[i], sizeof(float) * columns);
        }
    }

    // Initializing lines and columns
    _lines = lines;
    _columns = columns;
}

Matrix::~Matrix()
{
    if (_shared) {
        // We will start by unmapping the lines 
        for (int i = 0; i < _columns; ++i) {
            munmap(
                _elementsMatrix[i],
                sizeof(float) * _columns
            );
        }

        // We will now unmap the outer table 
        munmap(
            _elementsMatrix,
            sizeof(float*) * _lines
        );
    } else {
        for (int i = 0; i < _lines; ++i) {
            delete _elementsMatrix[i];
        }
        delete _elementsMatrix;
    }

}

uint Matrix::GetNbLines() const {
    return this->_lines;
}

uint Matrix::GetNbColumns() const {
    return this->_columns;
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
}

void Matrix::lineTimesColumnPointers(
    Matrix *solutionMatrix,
    const Matrix * mat1,
    const Matrix * mat2,
    uint line,
    uint column)
{
    uint mat2Columns = mat2->GetNbColumns();
    uint mat1Lines = mat1->GetNbLines();
    float sum = 0;
    for (uint i = 0; i < mat2Columns; ++i)
    {
        sum += mat1->_elementsMatrix[line][i] * mat2->_elementsMatrix[i][column];
    }
    solutionMatrix->nbProcesses ++;
    solutionMatrix->_elementsMatrix[line][column] = sum;
}

Matrix Matrix::MultiplyWithThreads(
    const Matrix & matrix1,
    const Matrix & matrix2)
{
    uint mat1Lines = matrix1.GetNbLines();
    uint mat1Columns = matrix1.GetNbColumns();
    uint mat2Lines = matrix2.GetNbLines();
    uint mat2Columns = matrix2.GetNbColumns();
    if (mat1Columns != mat2Lines)
    {
        throw "Incompatible sizes";
    } 

    Matrix solutionMatrix(mat1Lines, mat2Columns, false);

    thread *threadTable[mat1Lines * mat2Columns];

    for (int i = 0; i < mat1Lines; ++i)
    {
        for (int j = 0; j < mat2Columns; ++j)
        {
            int index = mat2Columns * i + j;
            thread *t = new thread(
                &Matrix::lineTimesColumnPointers,
                &solutionMatrix,
                &matrix1, 
                &matrix2, 
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
    for (int i = 0; i < matrix._lines; ++i)
    {
        for (int j = 0; j < matrix._columns; ++j)
        {
            out << matrix._elementsMatrix[i][j] << "\t";
        }
        out << endl;
    }
    return out;
}

void Matrix::MultiplyWithForks(
    const Matrix &matrix1,
    const Matrix &matrix2
) {
    uint mat1Lines = matrix1._lines;
    uint mat1Columns = matrix1._columns;
    uint mat2Lines = matrix2._lines;
    uint mat2Columns = matrix2._columns;
    pid_t pid;

    if (mat1Columns != mat2Lines)
    {
        throw "Incompatible sizes";
    }

    Matrix * sharedSolutionMatrix = (Matrix *)mmap(
        NULL,
        sizeof(Matrix),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );

    
    Matrix temp (
        mat2Lines,
        mat1Columns,
        true
    );
    memcpy(sharedSolutionMatrix, &temp, sizeof(Matrix));

    sharedSolutionMatrix->nbProcesses = 0;

    for (int i = 0; i < mat1Lines; ++i) {
        for (int j = 0; j < mat2Columns; ++j) {
            pid = fork();
            if (pid == 0) {
                lineTimesColumnPointers(
                    sharedSolutionMatrix,
                    &matrix1,
                    &matrix2,
                    i,
                    j
                );
                break;
            }
        }
        if (pid == 0) {
            break;
        }
    }

    if (pid != 0) {
        while (wait(NULL) > 0); 
        cout << *sharedSolutionMatrix;
        cout << "number of processed : " << sharedSolutionMatrix->nbProcesses << endl;
    }

}

void Matrix::Display() {
    for (int i = 0; i < this->_lines; ++i) {
        for (int j = 0; j < this->_columns; ++j) {
            cout << this->_elementsMatrix[i][j] << "\t";
        } 
        cout << endl;
    }
}