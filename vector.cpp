#include "vector.h"

// Konstruktoriai
template<typename T>
Vector<T>::Vector() : sz(0), cap(5), elem(new T[cap]) {}

template<typename T>
Vector<T>::Vector(int s) : sz(s), cap(s * 2), elem(new T[cap]) {}

template<typename T>
Vector<T>::Vector(int s, T value) : sz(s), cap(s * 2), elem(new T[cap])
{
    fill_n(elem, s, value); 
}

// Destruktorius: atlaisvina vektoriaus klasės objekto resursus
template<typename T>
Vector<T>::~Vector()
{
    delete[] elem;
}

// Elemento pridejimo i vektoriaus gala funkcija
template<typename T>
void Vector<T>::push_back(T value)
{
    elem[sz] = value;
    ++sz;
}

// Funkcija, grazinanti true arba false, priklausomai nuo to, ar vektorius tuscias ar ne
template <typename T>
bool Vector<T>::empty() const
{
    return sz == 0;
}

// Funkcija, grazinanti vektoriaus dydi
template <typename T>
int Vector<T>::size() const
{
    return sz;
}

// Funkcija, grazinanti vektoriaus talpa
template <typename T>
int Vector<T>::capacity() const
{
    return cap;
}

template <typename T>
bool Vector<T>::operator==(const Vector &other) const
{
    if (size() != other.size())
    {
        return false;
    }

    for (int i = 0; i < size(); i++)
    {
        if (elem[i] != other.elem[i])
        {
            return false;
        }
    }

    return true;
}
