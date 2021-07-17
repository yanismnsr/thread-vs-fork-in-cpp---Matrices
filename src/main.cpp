//
// Created by manso on 04/06/2021.
//

/**
 * Tests the Matrix class
 */
#include "../include/matrixcpp/Matrix.h"
#include "../include/matrixcpp/SharedCalculator.h"
#include "../include/matrixcpp/Serializer.h"
#include <vector>
#include <iostream>
#include <functional>
#include <ctime>
#include <sys/time.h>

using namespace std;

void matrixTest() {
    float line1 [] = {-1, 4, 5};
    float line2 [] = {7, 9, 2};
    float line3 [] = {2, 7, 4};

    float *matrix [3] = {line1, line2, line3};

    Matrix mat1 (3, 3, matrix, false);

    //Matrix::MultiplyWithThreads(mat1, mat1, NULL);

    Matrix::MultiplyWithForks(mat1, mat1, NULL);

}

template <class T> void printType(const T&) {
    cout << __PRETTY_FUNCTION__ << endl;
}

long int getTime() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    return ms;
}

int main(int argc, char *argv[]) {

    time_t tic, tac;

    Serializer threadFile("thread.txt");

    for (int i = 1; i <= 100; ++i) {

        SharedCalculator sc (i, i);

        Matrix mat(i, i);

        function <void (Matrix*)> funcThreads = [i, &mat, &threadFile] (Matrix* resultPtr) {
            long int tic = getTime();
            Matrix::MultiplyWithThreads(mat, mat, resultPtr);
            long int tac = getTime();
            threadFile << i << ":" << tac - tic << endl;
        };

        sc.process(funcThreads);

    }

    Serializer forkFile ("fork.txt");

    for (int i = 1; i <= 100; ++i) {

        SharedCalculator sc (i, i);

        Matrix mat(i, i);

        function <void (Matrix*)> funcForks = [i, &mat, &forkFile] (Matrix* resultPtr) {
            long int tic = getTime();
            Matrix::MultiplyWithForks(mat, mat, resultPtr);
            long int tac = getTime();
            forkFile << i << ":" << tac - tic << endl;
        };

        sc.process(funcForks);

    }


    // Matrix mat (150, 150);
    // SharedCalculator sc(150, 150);
    
    // function <void (Matrix*)> funcThreads = [&mat] (Matrix* resultPtr) {
    //     Matrix::MultiplyWithThreads(mat, mat, resultPtr);
    // };

    // sc.process(funcThreads);

}