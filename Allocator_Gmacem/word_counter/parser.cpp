#include "parser.h"
#include <algorithm>
#include <map>
#include <string>
#include <vector>

ViewBuffer::ViewBuffer(int begin, int end, char* buffer)
    : begin_(begin), end_(end), buffer_(buffer) {
}

bool ViewBuffer::operator<(const ViewBuffer& other) const {
    int first = begin_, second = other.begin_;
    for (; first != end_ && second != other.end_; ++first, ++second) {
        char first_c = tolower(buffer_[first]);
        char second_c = tolower(other.buffer_[second]);
        if (first_c != second_c) {
            return first_c < second_c;
        }
    }
    return first == end_ && second != other.end_;
}

std::string ViewBuffer::ToString() const {
    std::string result;
    int pos = begin_;
    while (pos != end_) {
        result += buffer_[pos++];
    }
    return result;
}


std::vector<ViewBuffer> Parser::ParseView(char* buffer, size_t size) {
    std::vector<ViewBuffer> result;
    int begin = 0;
    for (size_t i = 0; i < size; ++i) { 
        if (!isalpha(buffer[i])) {
            if (begin < i) {
                result.emplace_back(begin, i, buffer);
            }
            begin = i + 1;
        }
    }

    return result;
}

std::vector<std::string> Parser::ParseString(char* buffer, size_t size) {
    std::vector<std::string> result;
    int begin = 0;
    for (size_t i = 0; i < size; ++i) { 
        if (!isalpha(buffer[i])) {
            if (begin < i) {
                result.emplace_back(buffer + begin, buffer + i);
                std::for_each(result.back().begin(), result.back().end(), [](char & c){
                        c = ::tolower(c);
                    });
            }
            begin = i + 1;
        }
    }

    return result;
}

std::map<ViewBuffer, size_t, Comparator, allocator_type> CountFromViewBuf(std::vector<ViewBuffer> views) {
    std::map<ViewBuffer, size_t, Comparator, allocator_type> result;
    for (const auto& view : views) {
        ++result[view];
    }
    return result;
}


std::map<std::string, size_t> CountFromString(std::vector<std::string> views) {
    std::map<std::string, size_t> result;
    for (const auto& view : views) {
        ++result[view];
    }
    return result;
}

std::vector<std::pair<std::string, size_t> > GetOrder(std::map<std::string, size_t> counts) {
    std::vector<std::pair<std::string, size_t> > result;
    for (auto it = counts.begin(); it != counts.end(); ++it ) {
        result.emplace_back(it->first, it->second);
    }
    std::sort(result.rbegin(), result.rend(), []
            (std::pair<std::string, size_t>& lhs, std::pair<std::string, size_t>& rhs) {
                return lhs.second < rhs.second;
            });
    return result;
}
