#include "reader.h"
#include <fstream>
#include <iostream>

void Reader::Read(const char* filename, char* buffer) {
    std::ifstream is(filename);
    int i = 0;
    char c;
    while (is.get(c)) {
        buffer[i++] = c;
    }
    buffer[i] = 0;
    is.close();
}

size_t Reader::FileSize(const char* filename) {
    std::ifstream is(filename, std::ifstream::ate | std::ifstream::binary);
    size_t size = is.tellg();
    is.close();
    return size;
}
