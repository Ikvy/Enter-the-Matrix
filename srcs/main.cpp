#include "Vector.hpp"
#include "Matrice.hpp"

int main() {
    Vector<double> vec1(5);
    std::cout << "Vector 1: " << vec1 << std::endl;

    Vector<int> vec2(3);
	vec2[1] = 8;
    std::cout << "Vector 2: " << vec2 << std::endl;

	Matrice<double> mat(3, 3);
	mat(0, 0) = -1; 
	mat(1, 0) = 2; 
	mat(1, 1) = 3; 
	mat(2, 2) = 1; 
	std::cout << "Matrice 1: \n" << mat << std::endl;

	Vector<double> test = mat.toVector();

	std::cout << "vector test is the matrice 1 :\n" << test << std::endl;
	test.push_back(10);
	test.push_back(10);
	test.push_back(10);
    std::cout << "Vector test after push_back: " << test << std::endl;
	mat = test.toMatrice(4, 3);

	std::cout << "vector test to matrice test :\n" << mat << std::endl;
}