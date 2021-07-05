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
    int line1 [] = {-1, 4, 5};
    int line2 [] = {7, 9, 2};
    int line3 [] = {2, 7, 4};

    vector<float> vectLine1(line1, line1 + 3);
    vector<float> vectLine2(line2, line2 + 3);
    vector<float> vectLine3(line3, line3 + 3);

    vector<vector<float>> matrixVect;
    matrixVect.push_back(vectLine1);
    matrixVect.push_back(vectLine2);
    matrixVect.push_back(vectLine3);

    Matrix mat (matrixVect);

    
    cout << "multiplying ..." << endl;

    Matrix::MultiplyWithThreads(mat, mat);

}

int main(int argc, char *argv[]) {

    matrixTest();

}