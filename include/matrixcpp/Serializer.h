#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;


class Serializer {

public :
    Serializer(const string & filename);

    template <typename T>
    ostream& operator << (const T & str){
        return *_file << str;
    }

    ~Serializer();

private :

    ofstream * _file;

};


#endif