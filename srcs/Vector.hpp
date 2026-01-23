#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <initializer_list>
#include <stdexcept>

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

    // Operations on vectors
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

	float dot(const Vector& v) const {
        // same size
        if (data.size() != v.data.size()) {
            throw std::invalid_argument("Error: Vectors must have the same dimension.");
        }
        
        float result = 0.0f;
        // actual stuf
        for (size_t i = 0; i < data.size(); ++i) {
            result += data[i] * v.data[i];
        }
        return result;
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
    
    float norm_1() const { //sum of absolute
        float sum = 0.0f;
        for (size_t i = 0; i < size(); ++i) {
            sum += std::abs(data[i]);
        }
        return sum;
    }

    float norm() const { //square root of sum of square 
        float sum = 0.0f;
        for (size_t i = 0; i < size(); ++i) {
            sum += data[i] * data[i];
        }
        return std::sqrt(sum);
    }

    float norm_inf() const { //biggest abs number
        float maxVal = 0.0f;
        for (size_t i = 0; i < size(); ++i) {
            maxVal = std::max(maxVal, static_cast<float>(std::abs(data[i])));
        }
        return maxVal;
    }
};

// Stream output for vectors
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
