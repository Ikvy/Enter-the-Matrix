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
	std::cout << "matrice 1 to vector X :\n" << test << std::endl;
	//test.push_back(0);
   // std::cout << "Vector X after push_back: " << test << std::endl;
	mat = test.toMatrice(3, 3);

	std::cout << "vector X to matrice 1 :\n" << mat << std::endl;
}