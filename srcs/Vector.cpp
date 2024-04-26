#include "Vector.hpp"


template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
   for (size_t i = 0; i < data.size(); ++i) {
    data[i] = other.data[i];
   }
   return *this;
}

