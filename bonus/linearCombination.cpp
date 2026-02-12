#include "linearCombination.hpp"
#include <stdexcept>
#include "Vector.hpp"

template <typename T>
Vector<T> linear_combination(const std::vector<Vector<T>>& u, const std::vector<T>& coefs) {
    if (u.size() != coefs.size()) {
        throw std::invalid_argument("Vectors and coefficients must have the same size");
    }

    size_t vec_size = u[0].size();
    for (const auto& vec : u) {
        if (vec.size() != vec_size) {
            throw std::invalid_argument("All vectors must have the same size");
        }
    }

    Vector<T> result(vec_size);

    for (size_t i = 0; i < u.size(); ++i) {
        for (size_t j = 0; j < vec_size; ++j) {
            result[j] += u[i][j] * coefs[i];
        }
    }
    
    return result;
}

template Vector<float> linear_combination(const std::vector<Vector<float>>&, const std::vector<float>&);
template Vector<double> linear_combination(const std::vector<Vector<double>>&, const std::vector<double>&);
