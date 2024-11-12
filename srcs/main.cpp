#include <iostream>
#include "Vector.hpp"
#include "Matrice.hpp"
#include "linearCombination.hpp"

// Exercise 00
void test_op_vectors() {
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
}

// Exercise 00
void test_op_matrices() {
    Matrice<double> mat1(2, 2);
    mat1(0, 0) = 1.0; mat1(0, 1) = 2.0;
    mat1(1, 0) = 3.0; mat1(1, 1) = 4.0;

    Matrice<double> mat2(2, 2);
    mat2(0, 0) = 7.0; mat2(0, 1) = 4.0;
    mat2(1, 0) = -2.0; mat2(1, 1) = 2.0;

    // Addition de matrices
    mat1.add(mat2);
    std::cout << "mat1 + mat2 = \n" << mat1;

    // Soustraction de matrices
    mat1.sub(mat2);
    std::cout << "mat1 - mat2 = \n" << mat1;

    // Multiplication par un scalaire
    mat1.scl(2.0);
    std::cout << "mat1 * 2 = \n" << mat1;
}

// Exercise 01
void test_linear_combination() {
    Vector<float> e1 = {1., 0., 0.};
    Vector<float> e2 = {0., 1., 0.};
    Vector<float> e3 = {0., 0., 1.};
    Vector<float> v1 = {1., 2., 3.};
    Vector<float> v2 = {0., 10., -100.};
    

	std::vector<Vector<float>> u1 = {e1, e2, e3};
    std::vector<Vector<float>> u2 = {v1, v2};

	std::vector<float> coefs1 = {10., -2., 0.5};
    std::vector<float> coefs2 = {10., -2.};

    std::cout << "Linear combination of e1, e2, e3 with coefs [10, -2, 0.5]:\n";
    auto result1 = linear_combination(u1, coefs1);
    std::cout << result1 << "\n"; // [10.0, -2.0, 0.5]

    std::cout << "Linear combination of v1, v2 with coefs [10, -2]:\n";
    auto result2 = linear_combination(u2, coefs2);
    std::cout << result2 << "\n"; // [10.0, 0.0, 230.0]
}

int main() {

    std::cout << "===== Test des opérations sur les vecteurs =====\n";
    test_op_vectors();

    std::cout << "\n===== Test des opérations sur les matrices =====\n";
    test_op_matrices();

    std::cout << "\n===== Test de la combinaison linéaire =====\n";
    test_linear_combination();

    return 0;
}
