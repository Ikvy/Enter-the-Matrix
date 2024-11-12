#include <iostream>
#include "Vector.hpp"
#include "Matrice.hpp"

int main() {
    // Test des opérations sur les vecteurs
    Vector<double> u(2);
    u[0] = 2.0;
    u[1] = 3.0;

    Vector<double> v(2);
    v[0] = 5.0;
    v[1] = 7.0;

    u.add(v);
    std::cout << "u + v = " << u << "\n";

    u.sub(v);
    std::cout << "u - v = " << u << "\n";

    u.scl(2.0);
    std::cout << "u * 2 = " << u << "\n";

    // Test des opérations sur les matrices
    Matrice<double> mat1(2, 2);
    mat1(0, 0) = 1.0; mat1(0, 1) = 2.0;
    mat1(1, 0) = 3.0; mat1(1, 1) = 4.0;

    Matrice<double> mat2(2, 2);
    mat2(0, 0) = 7.0; mat2(0, 1) = 4.0;
    mat2(1, 0) = -2.0; mat2(1, 1) = 2.0;

    mat1.add(mat2);
    std::cout << "mat1 + mat2 = \n" << mat1;

    mat1.sub(mat2);
    std::cout << "mat1 - mat2 = \n" << mat1;

    mat1.scl(2.0);
    std::cout << "mat1 * 2 = \n" << mat1;

    return 0;
}
