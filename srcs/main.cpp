#include "Vector.hpp"
#include <iostream>

int main() {
    Vector<double> vec1(5);
    std::cout << "Vector 1: " << vec1 << std::endl;

    Vector<int> vec2(3);
    std::cout << "Vector 2: " << vec2 << std::endl;

    return 0;
}