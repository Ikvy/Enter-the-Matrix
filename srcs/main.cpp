#include "Vector.hpp"
#include "Matrice.hpp"

int main() {
    Vector<double> vec1(5);
    std::cout << "Vector 1: " << vec1 << std::endl;

    Vector<int> vec2(3);
	vec2[1] = 8;
    std::cout << "Vector 2: " << vec2 << std::endl;

	Matrice<double> mat(5, 5);
	mat(0, 0) = -1; 
	mat(1, 0) = 2; 
	mat(1, 4) = 3; 
	mat(2, 3) = 1; 
	std::cout << "Matrice 1: \n" << mat << std::endl;

	Vector<double> test = mat.toVector();
	std::cout << "matrice 1 to vector :\n" << test << std::endl;
}