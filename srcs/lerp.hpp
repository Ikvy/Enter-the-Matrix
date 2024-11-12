#ifndef LERP_HPP
#define LERP_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

float lerp(float u, float v, float t) {
    return u + t * (v - u);
}

template <typename T>
Vector<T> lerp(const Vector<T>& u, const Vector<T>& v, float t) {
    Vector<T> diff = v;   // Crée une copie de v
    diff.sub(u);           // diff = v - u
    diff.scl(t);           // diff = t * (v - u)
    Vector<T> result = u;  // Crée une copie de u
    result.add(diff);      // result = u + t * (v - u)
    return result;
}

template <typename T>
Matrice<T> lerp(const Matrice<T>& u, const Matrice<T>& v, float t) {
    Matrice<T> diff = v;   // Crée une copie de v
    diff.sub(u);           // diff = v - u
    diff.scl(t);           // diff = t * (v - u)
    Matrice<T> result = u; // Crée une copie de u
    result.add(diff);      // result = u + t * (v - u)
    return result;
}


#endif
