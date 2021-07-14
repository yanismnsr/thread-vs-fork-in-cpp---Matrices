//
// Created by manso on 04/06/2021.
//

/**
 * Tests the Matrix class
 */
#include "../include/matrixcpp/Matrix.h"
#include <vector>
#include <iostream>

using namespace std;

void matrixTest() {
    float line1 [] = {-1, 4, 5};
    float line2 [] = {7, 9, 2};
    float line3 [] = {2, 7, 4};

    float *matrix [3] = {line1, line2, line3};

    vector<float> vectLine1(line1, line1 + 3);
    vector<float> vectLine2(line2, line2 + 3);
    vector<float> vectLine3(line3, line3 + 3);

    vector<vector<float>> matrixVect;
    matrixVect.push_back(vectLine1);
    matrixVect.push_back(vectLine2);
    matrixVect.push_back(vectLine3);

    Matrix mat1 (3, 3, matrix, false);

    Matrix::MultiplyWithThreads(mat1, mat1);

    Matrix::MultiplyWithForks(mat1, mat1);

}

int main(int argc, char *argv[]) {

    matrixTest();

}