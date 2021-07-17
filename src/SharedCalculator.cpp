//
// Created by manso on 04/06/2021.
//

#include "../include/matrixcpp/SharedCalculator.h"
#include <iostream>
#include <sys/mman.h>
#include <new>

using namespace std;

SharedCalculator::SharedCalculator (uint solutionLines, uint solutionColumns) {

    _sharedSpaceMatrix = (Matrix *)mmap(
        NULL,
        sizeof(Matrix),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1,
        0
    );

    _sharedSpaceMatrix = new (_sharedSpaceMatrix) Matrix(solutionLines, solutionColumns, true);

}

void SharedCalculator::process(function<void (Matrix*)> & f) {
    f(_sharedSpaceMatrix);
}


SharedCalculator::~SharedCalculator() {
    _sharedSpaceMatrix->~Matrix();
    munmap(_sharedSpaceMatrix, sizeof(Matrix));
}