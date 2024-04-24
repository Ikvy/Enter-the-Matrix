#pragma once
#include <iostream>
#include <vector>

template <typename T>
class Matrice {
private:
    std::vector<std::vector<T>> data;

public:
    Matrice(size_t x, size_t y) : data(x, std::vector<T>(y, T(0))) {}

    size_t size_x() const { return data.size(); }
    size_t size_y() const { return data.empty() ? 0 : data[0].size(); }

    T& operator()(size_t x, size_t y) { return data[x][y]; }
    const T& operator()(size_t x, size_t y) const { return data[x][y]; }

};


template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrice<T>& mat) {
    for (size_t i = 0; i < mat.size_x(); ++i) {
		os << "[ ";
    	for (size_t j = 0; j < mat.size_y(); ++j) {
    	    os << mat(i,j) << " ";
    	}
		os << " ]\n";
	}
    return os;
}