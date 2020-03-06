#pragma once
#include <memory>
#include <list>

template<typename T>
class Allocator : public std::allocator<T> {
public:
    using pointer = typename std::allocator<T>::pointer;
    using size_type = typename std::allocator<T>::size_type;
    using byte = unsigned char;
    const size_t BLOCK_SIZE = 1024 * 1024;

    Allocator() : position_(0) {
        blocks_.emplace_back(new byte[BLOCK_SIZE]);
    }

    template<class Other>
    Allocator(const Allocator<Other>& _Right) {
    }
    
    inline pointer allocate(size_type n, typename std::allocator<void>::const_pointer = 0) {
        size_type size = n * sizeof(T);
        if (size + position_ >= BLOCK_SIZE) {
            blocks_.emplace_back(new byte[BLOCK_SIZE]);
            position_ = 0;
        }
        position_ += size;
        return reinterpret_cast<pointer>(blocks_.back() + position_ - size);
    }

    inline void deallocate(pointer p, typename std::allocator<T>::size_type n) {
    }

    ~Allocator() {
        for (auto a : blocks_) {
            delete[] a;
        }
    }

private:
    std::list<byte*> blocks_;
    size_type position_ = 0;
};

