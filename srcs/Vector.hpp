#pragma once
#include <iostream>
#include <vector>

template <typename T>
class Vector {
private:
    std::vector<T> data;

public:
    Vector(size_t size) : data(size, T(0)) {}

    size_t size() const { return data.size(); }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

};


template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    os << "[ ";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i] << " ";
    }
    os << "]";
    return os;
}
