#include "vector.h"

// Konstruktoriai
template<class T>
Vector<T>::Vector() : sz(0), cap(5), elem(new value_type[cap]) {}

template<class T>
Vector<T>::Vector(int s) : sz(s), cap(s + 5), elem(new value_type[cap]) {}

template<class T>
Vector<T>::Vector(int s, value_type value) : sz(s), cap(s + 5), elem(new value_type[cap])
{
    fill_n(elem, s, value); 
}

template <class T>
Vector<T>::Vector(const initializer_list<value_type> &list) : sz(0), cap(list.size() + 5), elem(new value_type[cap])
{
    for (int i : list)
    {
        push_back(i);
    }
}

// Copy konstruktorius
template<class T>
Vector<T>::Vector(const Vector &other) : sz(other.sz), cap(other.cap), elem(new value_type[cap])
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
void Vector<T>::push_back(value_type value)
{
    if (sz < cap)
    {
        elem[sz] = value;
        ++sz;
    }
    else
    {
        cap *= 2;
        T* newelem = new value_type[cap];
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

// Funkcija, pasalinanti elementa, esanti nurodyto indekso vietoje
template <class T>
void Vector<T>::erase(int index)
{
    if (index < 0 || index >= sz)
    {
        throw runtime_error("Index out of range.");
    }

    for (int i = index; i < sz - 1; i++)
    {
        elem[i] = elem[i + 1];
    }

    sz--;
}

template <class T>
void Vector<T>::insert(int index, value_type value)
{
    if (index < 0 || index >= sz)
    {
        throw runtime_error("Index out of range.");
    }

    if (sz != cap)
    {
        for (int i = sz - 1; i >= index; i--)
        {
            elem[i + 1] = elem[i];
        }
        
        elem[index] = value;
        sz++;
    }
    else
    {
        cap *= 2;
        int* newelem = new value_type[cap];

        for (int i = 0; i < sz; i++)
        {
            newelem[i] = elem[i];
        }

        delete[] elem;
        elem = newelem;
        insert(index, value);
    }
}

// Funkcija, isvalanti vektoriu
template <class T>
void Vector<T>::clear()
{
    sz = 0;
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

// Operatorius, priskiriantis desineje lygybes puseje esancio vektoriaus reiksmes kaireje puseje esanciam vektoriui
template <class T>
Vector<T> &Vector<T>::operator=(const Vector &other)
{
    if (other.sz > sz)
    {
        delete[] elem;
        cap = other.sz + 5;
        elem = new value_type[cap];
    }

    for (int i = 0; i < other.size(); i++)
    {
        elem[i] = other.elem[i];
    }

    sz = other.sz;

    return *this;
}

// Operatorius, leidziantis pasiekti konkretu vektoriaus elementa
template <class T>
T &Vector<T>::operator[](int index)
{
    if (index < 0 || index >= sz)
    {
        throw runtime_error("Index out of range.");
    }
    return elem[index];
}

// Funkcija, grazinanti vektoriaus elementa, esanti i funkcija perduoto indekso vietoje
template <class T>
T &Vector<T>::at(int index)
{
    if (index < 0 || index >= sz)
    {
        throw runtime_error("Index out of range.");
    }
    
    return elem[index];
}

// Funkcija, grazinanti pirmaji vektoriaus elementa
template <class T>
T &Vector<T>::front()
{
    return elem[0];
}

// Funkcija, grazinanti paskutini vektoriaus elementa
template <class T>
T &Vector<T>::back()
{
    return elem[sz - 1];
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
