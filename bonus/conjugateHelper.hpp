#pragma once
#include <complex>

//for conjugate complex and float in dot bc for complex : u · v = Σ u[i] * conj(v_i) | for reels: u · v = Σ u[i] * v[i]
template<typename U> 
inline U conjugate(const U& value) {
    return value;
}

template<>
inline std::complex<float> conjugate(const std::complex<float>& value) {
    return std::conj(value);
}

template<>
inline std::complex<double> conjugate(const std::complex<double>& value) {
    return std::conj(value);
}