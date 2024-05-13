#include "vector.h"

// Konstruktoriai
template<class T>
Vector<T>::Vector() : sz(0), cap(5), elem(new T[cap]) {}

template<class T>
Vector<T>::Vector(int s) : sz(s), cap(s + 5), elem(new T[cap]) {}

template<class T>
Vector<T>::Vector(int s, T value) : sz(s), cap(s + 5), elem(new T[cap])
{
    fill_n(elem, s, value); 
}

template <class T>
Vector<T>::Vector(const initializer_list<T> &list) : sz(0), cap(list.size() + 5), elem(new T[cap])
{
    for (int i : list)
    {
        push_back(i);
    }
}

// Copy konstruktorius
template<class T>
Vector<T>::Vector(const Vector &other) : sz(other.sz), cap(other.cap), elem(new T[cap])
{
    for (int i = 0; i < other.size(); i++)
    {
        elem[i] = other.elem[i];
    }
}

// Destruktorius: atlaisvina vektoriaus klasės objekto resursus
template<class T>
Vector<T>::~Vector()
{
    delete[] elem;
}

// Elemento pridejimo i vektoriaus gala funkcija
template<class T>
void Vector<T>::push_back(T value)
{
    if (sz < cap)
    {
        elem[sz] = value;
        ++sz;
    }
    else
    {
        cap *= 2;
        T* newelem = new T[cap];
        for (int i = 0; i < sz; i++)
        {
            newelem[i] = elem[i];
        }
        newelem[sz] = value;
        ++sz;
        delete[] elem;
        elem = newelem;
    }
}

// Elemento isemimo is vektoriaus galo funkcija
template <class T>
void Vector<T>::pop_back()
{
    if (sz == 0)
    {
        throw runtime_error("Vector is empty.");
    }
    --sz;
}

// Funkcija, grazinanti true arba false, priklausomai nuo to, ar vektorius tuscias ar ne
template<class T>
bool Vector<T>::empty() const
{
    return sz == 0;
}

// Funkcija, grazinanti vektoriaus dydi
template<class T>
int Vector<T>::size() const
{
    return sz;
}

// Funkcija, grazinanti vektoriaus talpa
template<class T>
int Vector<T>::capacity() const
{
    return cap;
}

// Operatorius, lyginantis du vektorius ir grazinantis tiesa, jei tie vektoriai lygus
template<class T>
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

// Operatorius, lyginantis du vektorius ir grazinantis tiesa, jei tie vektoriai nelygus
template<class T>
bool Vector<T>::operator!=(const Vector &other) const
{
    return !(*this == other);
}

// Perkraunamas, vektoriaus isvedimo operatorius
template<class U>
ostream &operator<<(ostream &output, const Vector<U> &other)
{
    for (int i = 0; i < other.sz; i++)
    {
        output << other.elem[i] << " ";
    }

    output << "||";

    for (int i = other.sz; i < other.cap; i++)
    {
        output << other.elem[i] << " ";
    }

    output << endl;
    
    return output;
}
