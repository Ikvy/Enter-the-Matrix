#pragma once

#include "Vector.hpp"
#include <vector>

template <typename T>
Vector<T> linear_combination(const std::vector<Vector<T>>& u, const std::vector<T>& coefs);
