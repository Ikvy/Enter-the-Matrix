#pragma once
#include <iostream>
#include <vector>
#include "Vector.hpp"  // Déplace cette inclusion avant pour éviter les dépendances circulaires

template <typename T>
class Matrice {
private:
    std::vector<std::vector<T>> data;

public:
    Matrice(size_t x, size_t y) : data(x, std::vector<T>(y, T(0))) {}
    Matrice(const Matrice<T>& other) : data(other.data) {}

    size_t size_x() const { return data.size(); }
    size_t size_y() const { return data.empty() ? 0 : data[0].size(); }

    T& operator()(size_t x, size_t y) {
        if (x >= size_x() || y >= size_y()) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y];
    }

    const T& operator()(size_t x, size_t y) const {
        if (x >= size_x() || y >= size_y()) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[x][y];
    }

    Matrice<T>& operator=(const Matrice<T>& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    bool isSquare() const { return size_x() == size_y(); }

    Vector<T> toVector() const {
        Vector<T> ret(size_x() * size_y());
        size_t k = 0;
        for (size_t i = 0; i < size_x(); ++i) {
            for (size_t j = 0; j < size_y(); ++j) {
                ret[k] = data[i][j];
                ++k;
            }
        }
        return ret;
    }

    // Operations on matrices
    void add(const Matrice<T>& mat) {
        if (size_x() != mat.size_x() || size_y() != mat.size_y()) {
            throw std::invalid_argument("Matrices must be of the same size for addition.");
        }
        for (size_t i = 0; i < size_x(); ++i) {
            for (size_t j = 0; j < size_y(); ++j) {
                data[i][j] += mat(i, j);
            }
        }
    }

    void sub(const Matrice<T>& mat) {
        if (size_x() != mat.size_x() || size_y() != mat.size_y()) {
            throw std::invalid_argument("Matrices must be of the same size for subtraction.");
        }
        for (size_t i = 0; i < size_x(); ++i) {
            for (size_t j = 0; j < size_y(); ++j) {
                data[i][j] -= mat(i, j);
            }
        }
    }

    void scl(const T& scalar) {
        for (size_t i = 0; i < size_x(); ++i) {
            for (size_t j = 0; j < size_y(); ++j) {
                data[i][j] *= scalar;
            }
        }
    }
    
};

// Stream output for matrices
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrice<T>& mat) {
    for (size_t i = 0; i < mat.size_x(); ++i) {
        os << "[ ";
        for (size_t j = 0; j < mat.size_y(); ++j) {
            os << mat(i, j) << " ";
        }
        os << "]\n";
    }
    return os;
}
