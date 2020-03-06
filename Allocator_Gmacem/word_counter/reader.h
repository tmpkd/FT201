#pragma once
#include <cstdio>

class Reader{
public:
    void Read(const char* filename, char* buffer);
    size_t FileSize(const char* filename);
};
