#pragma once
#include <iostream>
#include <vector>

template <typename T>

class Matrice;
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

	Matrice<T> toMatrice(size_t rows, size_t cols) const
	{
		if (rows * cols != data.size()){
			std::cerr << "Error : to shape a vector into a matrice, rows * cols must be equal to the vector size\n";
			exit(EXIT_FAILURE); } ////////to be treated
		
		Matrice<T> ret(rows, cols);
		size_t k = 0;
		for (size_t i = 0; i < rows; ++i){
			for (size_t j = 0; j < cols; ++j){
			ret(i, j) = data[k];
			++k;
			}
		}
		return ret;
	}
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


#include "Matrice.hpp"