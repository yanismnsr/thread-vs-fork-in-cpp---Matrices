//
// Created by manso on 04/06/2021.
//

/**
 * Tests the Matrix class
 */
#include "../include/matrixcpp/Matrix.h"
#include "../include/matrixcpp/SharedCalculator.h"
#include <vector>
#include <iostream>

using namespace std;

void matrixTest() {
    float line1 [] = {-1, 4, 5};
    float line2 [] = {7, 9, 2};
    float line3 [] = {2, 7, 4};

    float *matrix [3] = {line1, line2, line3};

    Matrix mat1 (3, 3, matrix, false);

    Matrix::MultiplyWithThreads(mat1, mat1, NULL);

    Matrix::MultiplyWithForks(mat1, mat1, NULL);

}

int main(int argc, char *argv[]) {

    matrixTest();
 
    SharedCalculator sc = SharedCalculator(3, 3);

    Matrix mat(3, 3);

    cout << mat;

    // sc.process([](Matrix * resultPtr) {
    //     Matrix::MultiplyWithForks(mat1, mat1, NULL);
    // })

}