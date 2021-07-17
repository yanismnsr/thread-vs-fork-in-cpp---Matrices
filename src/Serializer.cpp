#include "../include/matrixcpp/Serializer.h"

#include <string>
#include <iostream>
#include <fstream>

Serializer::Serializer(const string & filename) {
    _file = new ofstream(filename);
}

Serializer::~Serializer() {
    _file->close();
    delete _file;
}

