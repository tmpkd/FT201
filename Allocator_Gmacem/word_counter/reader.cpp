#include <fstream>
#include <iostream>

class Reader{
public:
    void Read(char* filename, char* buffer) {
        std::ifstream is(filename);
        int i = 0;
        char c;
        while (is.get(c)) {
            buffer[i++] = c;
        }
        buffer[i] = 0;
        is.close();
    }

    size_t FileSize(char* filename) {
        std::ifstream is(filename, std::ifstream::ate | std::ifstream::binary);
        size_t size = is.tellg();
        is.close();
        return size;
    }
};
