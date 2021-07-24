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
#include <cstdlib>
#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;

Matrix::Matrix(uint lines, uint columns)
{
    _shared = false;
    _elementsMatrix = new float* [lines];
    for (int i = 0; i < lines; ++i) {
        _elementsMatrix[i] = new float [columns];
        for (int j = 0; j < columns; ++j) {
            _elementsMatrix[i][j] = (rand() % 20) - 10;
        }
    }

    _lines = lines;
    _columns = columns;
}

Matrix::Matrix(uint lines, uint columns, bool shared) {
    _shared = shared;
    if (shared) {
        // Creating the shared memory space for the container of 
        // lines (table of tables)
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
            _elementsMatrix[i] = new float[columns];
        }
    }

    // Initializing lines and columns
    _lines = lines;
    _columns = columns;

}

Matrix::Matrix (uint lines, uint columns, float ** matrix, bool shared) {
    _shared = shared;
    if (shared) {
        // Creating the shared memory space for the container of 
        // lines (table of tables)
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
            _elementsMatrix[i] = new float[columns];
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
            delete[] _elementsMatrix[i];
        }
        delete [] _elementsMatrix;
    }

}

uint Matrix::GetNbLines() const {
    return this->_lines;
}

uint Matrix::GetNbColumns() const {
    return this->_columns;
}

void Matrix::lineTimesColumnPointers(
    Matrix *solutionMatrix,
    const Matrix * mat1,
    const Matrix * mat2,
    const uint line,
    const uint column
){
    uint mat2Columns = mat2->GetNbColumns();
    uint mat1Lines = mat1->GetNbLines();
    float sum = 0;
    for (uint i = 0; i < mat2Columns; ++i)
    {
        sum += mat1->_elementsMatrix[line][i]*mat2->_elementsMatrix[i][column];
    }
    solutionMatrix->_elementsMatrix[line][column] = sum;
}

void Matrix::lineTimesColumnThreads(
    Matrix *solutionMatrix,
    const Matrix * mat1,
    const Matrix * mat2,
    uint line,
    uint column,
    int threadNumber
){

    /* {
        lock_guard<mutex> lk(solutionMatrix->_mt);
        solutionMatrix->_nbProcesses ++;
    } */

    uint mat2Columns = mat2->GetNbColumns();
    uint mat1Lines = mat1->GetNbLines();
    float sum = 0;
    for (uint i = 0; i < mat2Columns; ++i)
    {
        sum += mat1->_elementsMatrix[line][i]*mat2->_elementsMatrix[i][column];
    }
    solutionMatrix->_elementsMatrix[line][column] = sum;

    {
        lock_guard<mutex> lk(solutionMatrix->_mt);
        solutionMatrix->_nbProcesses --;
        solutionMatrix->cv.notify_all();
    }
}

void Matrix::MultiplyWithThreads(
    const Matrix & matrix1,
    const Matrix & matrix2,
    Matrix * solution
){
    uint mat1Lines = matrix1.GetNbLines();
    uint mat1Columns = matrix1.GetNbColumns();
    uint mat2Lines = matrix2.GetNbLines();
    uint mat2Columns = matrix2.GetNbColumns();
    if (mat1Columns != mat2Lines)
    {
        throw "Incompatible sizes";
    }

    thread *threadTable[mat1Lines * mat2Columns];

    solution->_nbProcesses = mat1Lines * mat2Columns;

    for (int i = 0; i < mat1Lines; ++i)
    {
        for (int j = 0; j < mat2Columns; ++j)
        {
            int index = mat2Columns * i + j;
            thread *t = new thread(
                &Matrix::lineTimesColumnThreads,
                solution,
                &matrix1, 
                &matrix2, 
                i,
                j,
                mat2Columns * i + j
            );
            threadTable[index] = t;
        }
    }

    // Synchronization 
    {
        unique_lock<mutex> lk(solution->_mt);
        solution->cv.wait(lk, [&solution]{ return solution->_nbProcesses == 0; });
    }

    // Detaching
    for (int i = 0; i < mat1Lines * mat2Columns; ++i)
    {
        threadTable[i]->detach();
    }

    // Deleting the allocated memory for threads
    for (int i = 0; i < mat1Lines * mat2Columns; ++i)
    {
        delete threadTable[i];
    }

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
    const Matrix &matrix2,
    Matrix * solution
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

    for (int i = 0; i < mat1Lines; ++i) {
        for (int j = 0; j < mat2Columns; ++j) {
            pid = fork();
            if (pid == 0) {
                lineTimesColumnPointers(
                    solution,
                    &matrix1,
                    &matrix2,
                    i,
                    j
                );
                exit(0);
            }
        }
    }

    if (pid != 0) {
        while (wait(NULL) > 0); 
    }

}

void Matrix::naiveMultiplication (
    const Matrix & mat1, 
    const Matrix & mat2,
    Matrix* solution
) {
    uint mat1Lines = mat1.GetNbLines();
    uint mat1Columns = mat1.GetNbColumns();
    uint mat2Lines = mat2.GetNbLines();
    uint mat2Columns = mat2.GetNbColumns();

    int operations = 0;

    for (int i = 0; i < mat1Lines; ++i) {
        for (int j = 0; j < mat2Columns; ++j) {
            ++ operations;
            solution->_elementsMatrix[i][j] = 0;
            for (int k = 0; k < mat1Columns; ++k) {
                solution->_elementsMatrix[i][j] += mat1._elementsMatrix[i][k] * mat1._elementsMatrix[k][j];
            }
        }
    }

    cout << "operations : " << operations << endl;
}