#pragma once
#include <string>
#include <vector>
#include <map>
#include "allocator.h"

class ViewBuffer {
public:
    ViewBuffer(int begin, int end, char* buffer);

    bool operator<(const ViewBuffer& other) const;

    std::string ToString() const;

private:
    int begin_, end_;
    char* buffer_;
};

class Parser {
public:
    std::vector<ViewBuffer> ParseView(char* buffer, size_t size);

    std::vector<std::string> ParseString(char* buffer, size_t size);

private:
};

using allocator_type = Allocator<std::pair<const ViewBuffer, size_t>>;

class Comparator {
public:
    bool operator()(const ViewBuffer& lhs, const ViewBuffer& rhs) const {
        return lhs < rhs;
    }
};

std::map<ViewBuffer, size_t, Comparator, allocator_type> CountFromViewBuf(
        std::vector<ViewBuffer> views);

std::map<std::string, size_t> CountFromString(std::vector<std::string> views);

std::vector<std::pair<std::string, size_t> > GetOrder(std::map<std::string, size_t> counts);
