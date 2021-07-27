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

const int TEST_MATRIX_SIZE = 1000;
const unsigned int RUNS = 10;
const unsigned int MAX_THREADS = 50;

using namespace std;

template <class T> void printType(const T&) {
    cout << __PRETTY_FUNCTION__ << endl;
}

/**
 * Returns the current time since epoch in ms 
 * @return The current time since epoch in ms 
 */
long int getTime() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    return ms;
}

/**
 * Performs a bench mark for the following cases 
 * <p><ul>
 * <li> Multiplication in the main thread
 * <li> Multiplication using threads
 * <li> Multiplication using forks
 * </ul><p>
 */
void benchMark() {

    Matrix mat (TEST_MATRIX_SIZE, TEST_MATRIX_SIZE);
    SharedCalculator sc (TEST_MATRIX_SIZE, TEST_MATRIX_SIZE);

    Serializer singleThreadBenchmarkFile ("singleThreadBenchmark.txt");
    Serializer threadBenchmarkFile ("threadBenchmark.txt");
    Serializer forkBenchmarkFile ("forkBenchmark.txt");

    function<void (Matrix*)> singleThreadBenchmark = [&mat, &singleThreadBenchmarkFile] (Matrix* sharedSolution) -> void {
        time_t tic, tac;
        tic = getTime();
        Matrix::MultiplyInMainThread(mat, mat, sharedSolution);
        tac = getTime();
        singleThreadBenchmarkFile << (tac - tic) << endl;
    };
    
    function<void (Matrix*)> threadBenchMark = [&mat, &threadBenchmarkFile] (Matrix* sharedSolution) -> void {
        time_t tic, tac;
        unsigned int sum = 0;
        for (int i = 1; i <= MAX_THREADS; ++i) {
            sum = 0;
            for (int j = 0; j < RUNS; ++j) {
                tic = getTime();
                Matrix::MultiplyUsingThreads(i, mat, mat, sharedSolution);
                tac = getTime();
                sum += tac - tic;
            }
            threadBenchmarkFile << i << ":" << (sum / RUNS) << endl;
        }
    };

    function<void (Matrix*)> forkBenchmark = [&mat, &forkBenchmarkFile] (Matrix * sharedSolution) {
        time_t tic, tac;
        unsigned int sum = 0;
        for (int i = 1; i <= MAX_THREADS; ++i) {
            sum = 0;
            for (int j = 0; j < RUNS; ++j) {
                tic = getTime();
                Matrix::multiplyUsingForks(i, mat, mat, sharedSolution);
                tac = getTime();
                sum += tac - tic;
            }
            forkBenchmarkFile << i << ":" << (sum / RUNS) << endl;
        }
    };

    sc.process (singleThreadBenchmark);
    sc.process(threadBenchMark);
    sc.process(forkBenchmark);
    
}

/**
 * The main function
 */
int main(int argc, char *argv[]) {

    time_t tic, tac;

    benchMark();


}