#include "Vector.hpp"
#include "Matrice.hpp"

int main() {
    Vector<double> vec1(5);
    std::cout << "Vector 1: " << vec1 << std::endl;

    Vector<int> vec2(3);
	vec2[1] = 8;
    std::cout << "Vector 2: " << vec2 << std::endl;

	Matrice<int> mat(5, 5);
	mat(2, 2) = 1; 
	std::cout << "Matrice 1: \n" << mat << std::endl;

}