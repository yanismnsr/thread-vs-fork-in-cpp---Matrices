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
#include <algorithm>
#include <functional>

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


void Matrix::MultiplyInMainThread (
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


void Matrix::MultiplyUsingThreads(
    const unsigned int & nbThreads, 
    const Matrix & matrix1,
    const Matrix & matrix2, 
    Matrix * solution
) {
    // Get the number of elements for each thread
    unsigned int matrix1Lines = matrix1._lines;
    unsigned int matrix1Columns = matrix1._columns;
    unsigned int matrix2Lines = matrix2._lines;
    unsigned int matrix2Columns = matrix1._lines;

    unsigned int nbElements = matrix1Lines * matrix2Columns;

    // security
    int _nbThreads = nbThreads;
    if (nbThreads > nbElements) {
        _nbThreads = 1;
    } 

    limits thresholds [_nbThreads];

    int elementsPerThread = nbElements / _nbThreads;
    for (int i = 0; i < _nbThreads; ++i) {
        thresholds[i].lower = i * elementsPerThread;
        thresholds[i].upper = (i + 1) * elementsPerThread - 1;
    }
    thresholds[_nbThreads - 1].upper = nbElements - 1;

    thread *threadTable[_nbThreads];
    solution->_nbProcesses = _nbThreads;

    for (int i = 0; i < _nbThreads; ++i) {
        threadTable[i] = new thread (
            &Matrix::threadMultiplicationWorker,
            ref(matrix1),
            ref(matrix2),
            solution,
            ref(thresholds[i])
        );
        threadTable[i]->detach();
    }

    // Barrier synchronization
    {
        unique_lock <mutex> lock (solution->_mt);
        solution->cv.wait(lock, [&solution] {return solution->_nbProcesses == 0;});
    }

    // No need to join, just free the ressources 
    for (int i = 0; i < _nbThreads; ++i) {
        delete threadTable[i];
    }

}

void Matrix::threadMultiplicationWorker(
    const Matrix & mat1,
    const Matrix & mat2, 
    Matrix * resultMatrix,
    const limits & thresholds
) {

    Matrix::multiplyElements(
        mat1,
        mat2,
        resultMatrix,
        thresholds
    );

    // Notify the main thread to check if all the threads have finished the job
    {
        lock_guard<mutex> lock(resultMatrix->_mt);
        --resultMatrix->_nbProcesses;
        resultMatrix->cv.notify_one();
    }

}

void Matrix::multiplyElements(
    const Matrix & mat1,
    const Matrix & mat2, 
    Matrix * resultMatrix,
    const limits & thresholds
) {
    int lower = thresholds.lower;
    int upper = thresholds.upper;

    int nbLines = resultMatrix->_lines;
    int nbColumns = resultMatrix->_columns;


    for (int i = lower; i <= upper; ++i) {
        int line = i / nbColumns;
        int column = i % nbColumns;
        resultMatrix->_elementsMatrix[line][column] = 0;
        for (int j = 0; j < mat1._columns; ++j) {
            resultMatrix->_elementsMatrix[line][column] += 
                mat1._elementsMatrix[line][j]*mat2._elementsMatrix[j][column];
        }
    }
}

void Matrix::multiplyUsingForks(
    const int & nbThreads, 
    const Matrix & matrix1,
    const Matrix & matrix2, 
    Matrix * solution
) {

    // Get the number of elements for each thread
    unsigned int matrix1Lines = matrix1._lines;
    unsigned int matrix1Columns = matrix1._columns;
    unsigned int matrix2Lines = matrix2._lines;
    unsigned int matrix2Columns = matrix1._lines;

    unsigned int nbElements = matrix1Lines * matrix2Columns;

    pid_t pid;

    // security
    int _nbThreads = nbThreads;
    if (nbThreads > nbElements) {
        _nbThreads = 1;
    } 

    limits thresholds [_nbThreads];

    int elementsPerThread = nbElements / _nbThreads;
    for (int i = 0; i < _nbThreads; ++i) {
        thresholds[i].lower = i * elementsPerThread;
        thresholds[i].upper = (i + 1) * elementsPerThread - 1;
    }
    thresholds[_nbThreads - 1].upper = nbElements - 1;

    for (int i = 0; i < _nbThreads; ++i) {
        pid = fork();
        if (pid == 0) {
            multiplyElements(
                matrix1,
                matrix2, 
                solution,
                thresholds[i]
            );
            exit(0);
        }
    }

    // Synchronization 
    if (pid != 0) {
        while (wait(NULL) > 0);
    }

}