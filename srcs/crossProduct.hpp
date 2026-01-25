#pragma once
#include "Vector.hpp"
#include <stdexcept>

template <typename T>
Vector<T> cross_product(const Vector<T>& u, const Vector<T>& v) {
    if (u.size() != 3 || v.size() != 3) {
        throw std::invalid_argument("Cross product is only defined for 3D vectors");
    }

    Vector<T> result(3);
    //formula from my old math classes. u * v =
    // (u2v3 - u3v2)
    // (u3v1 - u1v3)
    // (u1v2 - u2v1)
    result[0] = u[1] * v[2] - u[2] * v[1];
    result[1] = u[2] * v[0] - u[0] * v[2];
    result[2] = u[0] * v[1] - u[1] * v[0];

    return result;
}
