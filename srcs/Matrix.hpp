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

    Matrix<T> transpose() const { //invert rows/columns
        Matrix<T> result(size_y(), size_x());

        for (size_t i = 0; i < size_x(); ++i) {
            for (size_t j = 0; j < size_y(); ++j)
                result(j, i) = data[i][j];
        }

        return result;
    }

    //this can be used to solve system equations, to find if it's unsolvable or if there's infinite solutions faster that with classic method
    Matrix<T> row_echelon(const Matrix<T>& input) { // gaussian elimination will be used here
        Matrix<T> result(input);//copy

        size_t pivot_row = 0;
        const T EPS = static_cast<T>(1e-6);

        for (size_t col = 0; col < result.size_y() && pivot_row < result.size_x(); ++col) {

            //find pivot (first != 0)
            size_t pivot = pivot_row;
            while (pivot < result.size_x() && std::abs(result(pivot, col)) < EPS) {
                ++pivot;
            }

            if (pivot == result.size_x())
                continue;

            // swap rows (in case this column pivot is not on the current col. swapping lines do not change the system) needed to apply gaussian elimination
            if (pivot != pivot_row) {
                for (size_t j = 0; j < result.size_y(); ++j) {
                    std::swap(result(pivot, j), result(pivot_row, j));
                }
            }

            // norm pivot row. make it easier to read ( divide it until it's 1 is often better)
            T pivot_value = result(pivot_row, col);
            for (size_t j = col; j < result.size_y(); ++j) {
                result(pivot_row, j) /= pivot_value;
            }

            // put 0 under pivot (ex : L2 -x * L1 where x is the number that needs to be 0)
            for (size_t i = pivot_row + 1; i < result.size_x(); ++i) {
                T factor = result(i, col);
                for (size_t j = col; j < result.size_y(); ++j)
                    result(i, j) -= factor * result(pivot_row, j);
            }

            ++pivot_row; //same with every matrix row
        }
        return result;
    }

    T determinant() const { //gaussian elimination like above but with no normalisation (which changes the determinant)
        if (!isSquare())
            throw std::runtime_error("Determinant is only defined for square matrices.");

        size_t n = size_x();
        Matrix<T> tmp(*this);
        
        T det = static_cast<T>(1); //init to 1 bc is multiplicative
        int swap_count = 0;
        const T EPS = static_cast<T>(1e-6); // Small threshold to avoid numerical instability due to float (f32 imposed in the subject)

        for (size_t col = 0; col < n; ++col) { //gaussian loop

            size_t pivot = col;
            while (pivot < n && std::abs(tmp(pivot, col)) < EPS)
                ++pivot;

            if (pivot == n)
                return static_cast<T>(0); //if no pivot is found --> det = 0 bc det = product of all diagonal

            if (pivot != col) {
                for (size_t j = 0; j < n; ++j)
                    std::swap(tmp(pivot, j), tmp(col, j));
                swap_count++;
            }

            T pivot_value = tmp(col, col); // pivot is now on diagonal
            det *= pivot_value; //det = product of diagonal elements is case of upper triangular matrix

            
            // Eliminate values below the pivot, which does not change det (math says : adding a multiple of a row to another row preserves det) + this makes tmp a upper triangular matrix (we need this)
            for (size_t i = col + 1; i < n; ++i) {
                T factor = tmp(i, col) / pivot_value;
                for (size_t j = col; j < n; ++j)
                    tmp(i, j) -= factor * tmp(col, j);
            }
        }
        if (swap_count % 2 != 0) //Each row swap multiplies the determinant by -1
            det = -det;

        return det;
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
