#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <condition_variable>

using namespace std;

struct limits{
    int lower;
    int upper;
};


/**
 * @brief Represents a matrix, with the multiply operation performed in 
 *          two parallel approaches (threads + forks)
 */
class Matrix {

public :


    /**
     * Builds a "lines x columns" matrix initialized with random numbers 
     * <p> 
     */
    Matrix(uint lines, uint columns);



    /**
     * Creates a "lines x columns" matrice. 
     * <p>
     * If shared is set to true, the matrice is put in an inter-process shared space 
     * and initialized with 0's
     * Else, the matrix is initialized normally
     */
    Matrix(uint lines, uint columns, bool shared);



    /**
     * Creates a "lines x columns" matrix, initialized with the give data 
     * in the matrix parameter 
     */
    Matrix (uint lines, uint columns, float * matrix[], bool shared);



    /**
     * @brief Get the number of lines of the current matrix
     * 
     * @return uint - Number of lines
     */
    uint GetNbLines() const;



    /**
     * @brief Get the number of columns of the current matrix 
     * 
     * @return uint - Number of columns
     */
    uint GetNbColumns() const;



    /**
     * @brief Displays the matrix in the terminal
     * 
     * @param[in] os        Ostream object
     * @param[in] matrix    The matrix to display
     * @return ostream& A reference to the given \p os object in parameter
     */
    friend ostream & operator <<(ostream &os, const Matrix &matrix);



    /**
     * @brief Multiplies \p matrix1 and \p matrix2, using \p nbThreads threads
     *        and puts the result in \p solution
     * 
     * @pre \p matrix1 and \p matrix2 must be initialized, and be compatible
     *      in multiplication
     * 
     * @pre The dimensions of the \p solution matrix must much the dimensions 
     *      of the result
     * 
     * @note If \p nbThreads > the number of total elements of solution matrix,
     *       then the operation will be performed using one thread
     * 
     * @param[in] nbThreads     The number of threads used in the 
     *                          multiplication process
     * @param[in] matrix1       The first operand 
     * @param[in] matrix2       The second operand
     * @param[out] solution     The solution matrix 
     */
    static void MultiplyUsingThreads(
        const unsigned int & nbThreads, 
        const Matrix & matrix1,
        const Matrix & matrix2, 
        Matrix * solution
    );

    /**
     * @brief Multiplies \p mat1 and \p mat2 without creating any threads
     *        nor performing any fork().
     * 
     * @pre mat1 and mat2 must be initialized, and be comparible in 
     *      multiplication
     * 
     * @pre The dimensions of the \p solution matrix must much the dimensions 
     *      of the result
     * 
     * @post \p solution contains the result of the multiplication
     * 
     * @param mat1      The first operand
     * @param mat2      The second operand
     * @param solution  The solution
     */
    static void MultiplyInMainThread (
        const Matrix & mat1, 
        const Matrix & mat2,
        Matrix* solution
    );



    /**
     * @brief   Performs a matrix multiplication and notifies the main thread
     *          when the work is done. The caller thread must use a unique_lock
     *          in the _mt mutex of the \p resultMatrix, and wait for 
     *          nbProcesses to become equal to 0 using the cv condition 
     *          variable of the \p resultMatrix object
     * 
     * @pre \p mat1 and \p mat2 must be initialized 
     * 
     * @pre The dimensions of \p resultMatrix must much the dimensions of the 
     *      result
     * 
     * @post \p resultMatrix contains the result of the multiplication
     * 
     * @post    If there is a thread that is waiting for the cv condition 
     *          variable, it is notified that the work is done.
     * 
     * @param mat1          The first operand
     * @param mat2          The second operand
     * @param resultMatrix  The matrix that will contain the result
     * @param thresholds    Describes the first element and the last element
     *                      of the \p resultMatrix the worker will multiply
     */
    static void threadMultiplicationWorker  (
        const Matrix & mat1,
        const Matrix & mat2, 
        Matrix * resultMatrix,
        const limits & thresholds
    );




    /**
     * @brief   Performs a matrix multiplication of the elements 
     *          described by the \p thresholds parameter
     * 
     * @pre \p mat1 and \p mat2 must be initialized
     * 
     * @pre The dimensions of \p resultMatrix must much the dimensions of the 
     *      result
     * 
     * @post \p resultMatrix contains the result of the multiplication
     * 
     * @note This method does not notify any process that the work is done
     * 
     * @note    If this method is used by forked processes, the resultMatrix 
     *          must be located in an inter-processes shared space 
     * 
     * @param mat1          The first operand
     * @param mat2          The second operand
     * @param resultMatrix  The matrix that will contain the result
     * @param thresholds    Describes the first element and the last element 
     *                      of the \p resultMatrix the method will multiply
     */
    static void multiplyElements(
        const Matrix & mat1,
        const Matrix & mat2, 
        Matrix * resultMatrix,
        const limits & thresholds
    );



    /**
     * @brief   Multiply \p matrix1 and \p matrix2 using \p nbProcesses
     *          processes
     * 
     * @pre \p matrix1 and \p matrix2 must be initialized
     * 
     * @pre     The dimensions of \p matrix1 and \p matrix2 must be compatible 
     *          in multiplication
     * 
     * @pre \p solution must be allocated in an inter-processes shared space
     * 
     * @param nbProcesses   The number of processes to create
     * @param matrix1       The first operand of multiplication
     * @param matrix2       The second operand of multiplication
     * @param solution      The matrix that will contain the result
     */
    static void multiplyUsingForks(
        const int & nbProcesses, 
        const Matrix & matrix1,
        const Matrix & matrix2, 
        Matrix * solution
    );

    /**
     * @brief Destroy the Matrix object
     */
    virtual ~Matrix();

private :

    /**
     * @brief The number of lines of the matrix
     */
    unsigned int _lines;
    /**
     * @brief The number of columns of the matrix
     */
    unsigned int _columns;

    /**
     * @brief Number of active processes that are accessing the matrix
     * 
     * @note It is used to synchronize processes
     * 
     */
    atomic<int> _nbProcesses;

    /**
     * @brief Used to synchronize processes
     */
    condition_variable cv;

    /**
     * @brief synchronize access to \p _nbProcesses attribute 
     *        and synchronize processes when used with \p cv
     */
    mutex _mt;

    /**
     * @brief   Specifies if the current object is in an inter-processes shared 
     *          space
     */
    bool _shared = false;

    /**
     * @brief Contains the data of the matrix
     * 
     */
    float ** _elementsMatrix;

};

#endif