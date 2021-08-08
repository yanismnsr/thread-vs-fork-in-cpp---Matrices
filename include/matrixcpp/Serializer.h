#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * @brief RAII based class to write data into file
 *          If the file already exists, it is overwriten 
 *          Else, it is created
 */
class Serializer {

public :

    /**
     * @brief Construct a new Serializer object
     * 
     * @param filename  The name of the file to write the data into
     */
    Serializer(const string & filename);

    /**
     * @brief Writes data into the \p _file
     * 
     * @tparam T            The type of the data 
     * @param str           The data to write
     * @return ostream&     Returns the stream, to be able to chain calls
     */
    template <typename T>
    ostream& operator << (const T & str){
        return *_file << str;
    }

    /**
     * @brief Destroy the Serializer object
     * 
     */
    ~Serializer();

private :

    /**
     * @brief The stream of the file
     * 
     */
    ofstream * _file;

};


#endif