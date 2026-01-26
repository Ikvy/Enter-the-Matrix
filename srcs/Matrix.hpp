#pragma once
#include <iostream>
#include <vector>
#include "Vector.hpp"

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;

public:
    Matrix(size_t x, size_t y) : data(x, std::vector<T>(y, T(0))) {}
    Matrix(const Matrix<T>& other) : data(other.data) {}

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

    Matrix<T>& operator=(const Matrix<T>& other) {
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

    // Operations on Matrix
    void add(const Matrix<T>& mat) {
        if (size_x() != mat.size_x() || size_y() != mat.size_y()) {
            throw std::invalid_argument("Matrix must be of the same size for addition.");
        }
        for (size_t i = 0; i < size_x(); ++i) {
            for (size_t j = 0; j < size_y(); ++j) {
                data[i][j] += mat(i, j);
            }
        }
    }
    

    void sub(const Matrix<T>& mat) {
        if (size_x() != mat.size_x() || size_y() != mat.size_y()) {
            throw std::invalid_argument("Matrix must be of the same size for subtraction.");
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

    Vector<T> mul_vec(const Vector<T>& v) const {
        if (size_y() != v.size()) {
            throw std::invalid_argument("Matrix columns must match vector size.");
        }

        Vector<T> result(size_x());

        for (size_t i = 0; i < size_x(); ++i) {
            T sum = T(0);
            for (size_t j = 0; j < size_y(); ++j) {
                sum += (*this)(i, j) * v[j];
            }
            result[i] = sum;
        }

        return result;
    }
    //formula : a11 * b11 + a12 * b21 + a13 * b31 = c11
    Matrix<T> mul_mat(const Matrix<T>& m) const {
        if (size_y() != m.size_x()) {
            throw std::invalid_argument("Matrix dimensions are incompatible for multiplication.");
        }

        Matrix<T> result(size_x(), m.size_y());

        for (size_t i = 0; i < size_x(); ++i) {
            for (size_t j = 0; j < m.size_y(); ++j) {
                T sum = T(0);
                for (size_t k = 0; k < size_y(); ++k)
                    sum += (*this)(i, k) * m(k, j);
                result(i, j) = sum;
            }
        }
        return result;
    }

    T trace() const { //sum of diagonal
        if (!isSquare())
            throw std::runtime_error("Trace is only defined for square matrices.");

        T sum = T(0);
        for (size_t i = 0; i < size_x(); ++i)
            sum += data[i][i];
        return sum;
    }

};


// Stream output for Matrix
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
    for (size_t i = 0; i < mat.size_x(); ++i) {
        os << "[ ";
        for (size_t j = 0; j < mat.size_y(); ++j) {
            os << mat(i, j) << " ";
        }
        os << "]\n";
    }
    return os;
}
