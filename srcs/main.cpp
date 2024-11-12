#include <iostream>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "linearCombination.hpp"
#include "lerp.hpp"

// Exercise 00
void test_op_vectors() {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error in vector operations: " << e.what() << "\n";
    }
}

// Exercise 00
void test_op_matrices() {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error in matrix operations: " << e.what() << "\n";
    }
}

// Exercise 01
void test_linear_combination() {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "Error in linear combination: " << e.what() << "\n";
    }
}

void test_lerp() {
    try {
        // Test scalars
        std::cout << "Interpolating scalars:\n";
        std::cout << "lerp(0., 1., 0.) = " << lerp(0.0f, 1.0f, 0.0f) << "\n";
        std::cout << "lerp(0., 1., 1.) = " << lerp(0.0f, 1.0f, 1.0f) << "\n";
        std::cout << "lerp(0., 1., 0.5) = " << lerp(0.0f, 1.0f, 0.5f) << "\n";
        std::cout << "lerp(21., 42., 0.3) = " << lerp(21.0f, 42.0f, 0.3f) << "\n";

        // Test vectors
        Vector<float> u = {2.0f, 1.0f};
        Vector<float> v = {4.0f, 2.0f};
        std::cout << "lerp([2., 1.], [4., 2.], 0.3) = " << lerp(u, v, 0.3f) << "\n";

        // Test matrices
        Matrice<float> uMat(2, 2);
        uMat(0, 0) = 2.0f; uMat(0, 1) = 1.0f;
        uMat(1, 0) = 3.0f; uMat(1, 1) = 4.0f;

        Matrice<float> vMat(2, 2);
        vMat(0, 0) = 20.0f; vMat(0, 1) = 10.0f;
        vMat(1, 0) = 30.0f; vMat(1, 1) = 40.0f;

        std::cout << "lerp(Matrix([[2., 1.], [3., 4.]]), Matrix([[20., 10.], [30., 40.]]), 0.5) = \n";
        std::cout << lerp(uMat, vMat, 0.5f) << "\n"; 
    } catch (const std::exception& e) {
        std::cerr << "Error in lerp operation: " << e.what() << "\n";
    }
}

void test_dot_product() {
    try {
        Vector<float> u1 = {0.0f, 0.0f};
        Vector<float> v1 = {1.0f, 1.0f};
        std::cout << "Dot product of u1 and v1: " << u1.dot(v1) << "\n"; // 0.0

        Vector<float> u2 = {1.0f, 1.0f};
        Vector<float> v2 = {1.0f, 1.0f};
        std::cout << "Dot product of u2 and v2: " << u2.dot(v2) << "\n"; // 2.0

        Vector<float> u3 = {-1.0f, 6.0f};
        Vector<float> v3 = {3.0f, 2.0f};
        std::cout << "Dot product of u3 and v3: " << u3.dot(v3) << "\n"; // 9.0

        // diff in sizes
        Vector<float> u4 = {1.0f, 2.0f};
        Vector<float> v4 = {1.0f};
        // MUST be an exeption
        std::cout << "Dot product of u4 and v4: " << u4.dot(v4) << "\n"; // Exception

    } catch (const std::invalid_argument& e) {
        std::cerr << "Exception during dot product: " << e.what() << "\n";
    }
}


int main() {
    try {
        std::cout << "===== Test of vector operations =====\n";
        test_op_vectors();

        std::cout << "\n===== Test of matrix operations =====\n";
        test_op_matrices();

        std::cout << "\n===== Test of linear combination =====\n";
        test_linear_combination();

        std::cout << "\n===== Test of linear interpolation =====\n";
        test_lerp();

		std::cout << "\n===== Test of dot product (vector) =====\n";
		test_dot_product();

	} catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
    }

    return 0;
}
