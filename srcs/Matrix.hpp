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

    
    // inverse formula : A * A^-1 = I
    Matrix<T> inverse() const {  
        if (!isSquare())
            throw std::runtime_error("Inverse is only defined for square matrices.");

        const size_t n = size_x();
        const T EPS = static_cast<T>(1e-6); //always float handling

        // Gauss-Jordan first step : create augmented matrix [A | I]
        Matrix<T> augmented(n, 2 * n);

        // fill [A | I]
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                augmented(i, j) = (*this)(i, j);              // A
                augmented(i, j + n) = (i == j) ? T(1) : T(0); // I
            }
        }

        // Gauss-Jordan second step : elimination to make A an identity matrix
        for (size_t col = 0; col < n; ++col) {

            size_t pivot = col;
            while (pivot < n && std::abs(augmented(pivot, col)) < EPS) // find pivot
                ++pivot;

            if (pivot == n) // det = 0 --> singular matrix
                throw std::runtime_error("Matrix is singular, cannot invert.");

            if (pivot != col) {
                for (size_t j = 0; j < 2 * n; ++j)
                    std::swap(augmented(pivot, j), augmented(col, j)); // swap rows if needed
            }

            // normalize pivot row
            T pivot_value = augmented(col, col);
            for (size_t j = 0; j < 2 * n; ++j) 
                augmented(col, j) /= pivot_value; //to make A an identity

            // eliminate all other rows
            for (size_t i = 0; i < n; ++i) {
                if (i == col)
                    continue;

                T factor = augmented(i, col);
                for (size_t j = 0; j < 2 * n; ++j)
                    augmented(i, j) -= factor * augmented(col, j);
            }
        }

        // Gauss-Jordan final step : extract inverse from the I because now I = A^-1
        Matrix<T> inverse(n, n);
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                inverse(i, j) = augmented(i, j + n);

        return inverse;
    }

    //minimal Gaussian elimination focused only on detecting pivots(more precise and conceptually cleaner)
    size_t rank() const {
        Matrix<T> tmp(*this);
        const T EPS = static_cast<T>(1e-6);

        size_t rank = 0;
        size_t pivot_row = 0;

        for (size_t col = 0; col < tmp.size_y() && pivot_row < tmp.size_x(); ++col) {

            // find pivot
            size_t pivot = pivot_row;
            while (pivot < tmp.size_x() && std::abs(tmp(pivot, col)) < EPS)
                ++pivot;

            if (pivot == tmp.size_x())
                continue; // no pivot in this column

            // swap rows if needed
            if (pivot != pivot_row) {
                for (size_t j = 0; j < tmp.size_y(); ++j)
                    std::swap(tmp(pivot, j), tmp(pivot_row, j));
            }

            // eliminate rows below pivot
            T pivot_value = tmp(pivot_row, col);
            for (size_t i = pivot_row + 1; i < tmp.size_x(); ++i) {
                T factor = tmp(i, col) / pivot_value;
                for (size_t j = col; j < tmp.size_y(); ++j)
                    tmp(i, j) -= factor * tmp(pivot_row, j);
            }

            ++rank;
            ++pivot_row;
        }

        return rank;
    }


    Matrix<float> projection(float fov, float ratio, float near, float far)
    {
        Matrix<float> proj(4, 4);

        float fovRad = fov * 3.1415926535f / 180.0f;
        float f = 1.0f / tan(fovRad / 2.0f);

        proj(0, 0) = f / ratio;
        proj(1, 1) = f;

        proj(2, 2) = -(far + near) / (far - near);
        proj(2, 3) = -1.0f;

        proj(3, 2) = -(2.0f * far * near) / (far - near);
        proj(3, 3) =  0.0f;

        return proj;
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
