#include "Allocator.h"
#include "vector"
#include <chrono>
#include <fstream>
#include <list>
#include <map>
using namespace std::chrono;
int main(int size, char** args) {
//    std::ofstream out("list.txt", std::ios::out);
    int addArgs = std::stoi(args[1]);
    size_t a = 1;
    size_t* b = new size_t(1);
    b[0] = 1000000000;
    size_t* c = new size_t(1);
    c[0] = 24;
    std::list<int> vec1;
    auto start = std::chrono::system_clock::now();
    for (int j = 0; j < addArgs; j++) {
        vec1.emplace_back(j);
    }
    vec1.clear();
    auto stop = std::chrono::system_clock::now();
    Allocator<int> alloc(a, b, c);
    std::list<int, Allocator<int>> vec2(alloc);
    auto std = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    start = std::chrono::system_clock::now();
    for (int j = 0; j < addArgs; ++j) {
        vec2.emplace_back(j);
    }
    vec2.clear();
    stop = std::chrono::system_clock::now();
    auto pool = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    printf("%lld\n%lld", std.count(), pool.count());
    return 0;
}