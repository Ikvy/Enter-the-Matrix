#pragma once
#include "Vector.hpp"
#include <stdexcept>
#include <cmath>

template <typename T>
float angle_cos(const Vector<T>& u, const Vector<T>& v) {
    if (u.size() != v.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }

    float norm_u = u.norm();
    float norm_v = v.norm();

    if (norm_u == 0.0f || norm_v == 0.0f) {
        throw std::invalid_argument("Angle with zero vector is undefined");
    }

    float dot = u.dot(v);
    return dot / (norm_u * norm_v);
}
