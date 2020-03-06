#include <fstream>
#include <iostream>
#include <string>

class Buffer {
public:
    // rule of 5
    Buffer(const Buffer& buffer) = delete;
    Buffer(Buffer&& buffer) = delete;
    Buffer& operator=(const Buffer& buffer) = delete;
    Buffer& operator=(Buffer&& buffer) = delete;
    ~Buffer() {
        delete[] buf_;
    }

    Buffer(): size_(0), buf_(nullptr) {
    }

    void ReadData() {
        std::ifstream is("some_file", std::ifstream::ate | std::ifstream::binary);
        std::cout << is.tellg();
        return;
        char c;

        while (is.get(c)) {
            std::cout << c << '\n';
            Push(c);
        }
        is.close();
        Reserve(size_ + 1);
        buf_[size_] = 0;
    }

    size_t Size() {
        return size_;
    }

private:
    void Push(char c) {
        if (reserve_ == size_) {
            Reserve(2 * reserve_);
        }
        buf_[size_++] = c;
    }

    void Reserve(size_t size) {
        char* new_buf_ = new char[size];
        for (size_t i = 0; i < size_ && i < size; ++i) {
            new_buf_[i] = buf_[i];
        }
        reserve_ = size;
        delete[] buf_;
    }

private:
    char* buf_;
    size_t reserve_ = 0;
    size_t size_ = 0;
};
