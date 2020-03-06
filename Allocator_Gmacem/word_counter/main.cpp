#include "reader.cpp"
#include "parser.cpp"
#include <iostream>
#include <iomanip>
#include <time.h>

int main() {
    const char* filename = "text.txt";
    Reader reader;
    size_t size = reader.FileSize(filename);
    std::cerr << "Size: " << size << '\n';

    char* buffer = new char[size + 1];
    reader.Read(filename, buffer);

    Parser parser;

    clock_t v_start = clock();
    auto parsed_view = parser.ParseView(buffer, size);
    auto count_view = CountFromViewBuf(parsed_view);
    double v_work = static_cast<double>((clock() - v_start))/CLOCKS_PER_SEC;

    clock_t s_start = clock();
    auto parsed_string = parser.ParseString(buffer, size);
    auto count_string = CountFromString(parsed_string);
    double s_work = static_cast<double>((clock() - s_start))/CLOCKS_PER_SEC;

    auto order = GetOrder(count_string);

    for (const auto& val : order) {
        std::cout << "Word: " << val.first << " count: " << val.second << '\n';
    }
    
    std::cerr << std::fixed << std::setprecision(6);
    std::cerr << "Time compare\n";
    std::cerr << "ViewBuf + my allocator works: " << v_work << "s\n";
    std::cerr << "String + default allocator works: " << s_work << "s\n";
    delete[] buffer;
    return 0;
}
