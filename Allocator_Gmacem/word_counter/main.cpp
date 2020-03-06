#include "reader.cpp"
#include "parser.cpp"
#include <iostream>
#include <iomanip>
#include <time.h>

int main() {
    char* filename = "text.txt";
    Reader reader;
    size_t size = reader.FileSize(filename);
    std::cout << "Size: " << size << '\n';

    char* buffer = new char[size];
    reader.Read(filename, buffer);

    Parser parser;

    clock_t v_start = clock();
    auto parsed_view = parser.ParseView(buffer, size);
    auto count_view = CountFromViewBuf(parsed_view);
    double v_work = static_cast<double>((clock() - v_start))/CLOCKS_PER_SEC;
    std::cout << parsed_view.size() << '\n';

    clock_t s_start = clock();
    auto parsed_string = parser.ParseString(buffer, size);
    auto count_string = CountFromString(parsed_string);
    double s_work = static_cast<double>((clock() - s_start))/CLOCKS_PER_SEC;

    auto order = GetOrder(count_string);

    for (const auto& val : order) {
        std::cout << "Word: " << val.first << " count: " << val.second << '\n';
    }
    
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Time compare\n";
    std::cout << "ViewBuf works: " << v_work << '\n';
    std::cout << "String works: " << s_work << '\n';
    
    /*
    auto parsed_second = parser.PareseSecond(buffer);

    Stat statistic(parsed_first, parsed_second);
    statistic.Print();
*/
    delete[] buffer;
    return 0;
}
