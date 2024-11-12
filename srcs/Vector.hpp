#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include <stdexcept>  // pour std::out_of_range, std::invalid_argument

template <typename T>
class Matrice;  // Déclaration préalable pour la classe Matrice

template <typename T>
class Vector {
private:
    std::vector<T> data;

public:
    // init
    Vector(size_t size) : data(size, T(0)) {}
    Vector(const Vector<T>& other) : data(other.data) {}
    Vector(std::initializer_list<T> init) : data(init) {}

    size_t size() const { return data.size(); }
    
    T& operator[](size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    Vector<T>& operator=(const Vector<T>& other) {
        if (this != &other) { // no weird auto assign
            data = other.data;
        }
        return *this;
    }

    void add(const Vector<T>& v) {
        if (v.size() != size()) {
            throw std::invalid_argument("Vectors must be of the same size for addition.");
        }
        for (size_t i = 0; i < size(); ++i) {
            data[i] += v[i];
        }
    }

    void sub(const Vector<T>& v) {
        if (v.size() != size()) {
            throw std::invalid_argument("Vectors must be of the same size for subtraction.");
        }
        for (size_t i = 0; i < size(); ++i) {
            data[i] -= v[i];
        }
    }

    void scl(const T& scalar) {
        for (size_t i = 0; i < size(); ++i) {
            data[i] *= scalar;
        }
    }

    Matrice<T> toMatrice(size_t rows, size_t cols) const {
        if (rows * cols != data.size()) {
            throw std::invalid_argument("Rows * cols must be equal to the vector size for conversion to matrix.");
        }
        Matrice<T> ret(rows, cols);
        size_t k = 0;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                ret(i, j) = data[k++];
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

#include "Matrix.hpp"
