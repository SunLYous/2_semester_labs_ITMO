#include <functional>
#include <./lib/CircularBuffer.h>
#include <iostream>
#include <numeric>

int main(int argc, char** argv) {
    CircularBuffer<int> a(5);
    a.PushBack(1);
    a.PushBack(2);
    a.PushBack(3);
    a.PushBack(4);
    a.PushBack(5);
    std::sort(a.begin(), a.end(), [](int a, int b) { return a > b; });
   std::cout<< std::is_sorted(a.begin(), a.end());
    for (auto i : a) {
        std::cout << i << " ";
    }

}
