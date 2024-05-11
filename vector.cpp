#include "vector.h"

// Konstruktoriai
template<typename T>
Vector<T>::Vector() : size(0), capacity(5), elem(new T[capacity]) {}

template<typename T>
Vector<T>::Vector(int s) : size(s), capacity(s * 2), elem(new T[capacity]) {}

template<typename T>
Vector<T>::Vector(int s, T value) : size(s), capacity(s * 2), elem(new T[capacity])
{
    fill_n(elem, s, value); 
}

// Destruktorius: atlaisvina vektoriaus klasės objekto resursus
template<typename T>
Vector<T>::~Vector()
{
    delete[] elem;
}