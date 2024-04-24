#pragma once
#include <iostream>
#include <vector>

template <typename T>
class Vector {
private:
    std::vector<T> data;

public:
    Vector(size_t size) : data(size, T(0)) {}
	Vector(const Vector<T>& other) : data(other.data) {}

    size_t size() const { return data.size(); }

    Vector<T>& operator=(const Vector<T>& other);
	T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }
	
	void push_back(const T& value) {data.push_back(value);}
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
