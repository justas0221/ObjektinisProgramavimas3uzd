#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

// std::vector funkcionaluma atkartojanti klase
template<class T>
class Vector
{
    private:
        int sz;                         // Vektoriaus elementu skaicius
        int cap;                        // Vektoriaus talpa  
        T* elem;                        // Rodykle i vektoriaus elementus
    public:
        // Konstruktoriai
        Vector();
        Vector(int s);
        Vector(int s, T value);
        Vector(const initializer_list<T>& list);
        Vector(const Vector& other);          // Copy kontruktorius
        ~Vector();                            // Destruktorius: atlaisvina vektoriaus klasės objekto resursus

        void push_back(T value);              // Elemento pridejimo i vektoriaus gala funkcija
        bool empty() const;                   // Funkcija, grazinanti true arba false, priklausomai nuo to, ar vektorius tuscias ar ne
        int size() const;                     // Funkcija, grazinanti vektoriaus dydi
        int capacity() const;                 // Funkcija, grazinanti vektoriaus talpa

        bool operator==(const Vector& other) const; // Operatorius, lyginantis du vektorius ir grazinantis tiesa, jei tie vektoriai lygus
        bool operator!=(const Vector& other) const; // Operatorius, lyginantis du vektorius ir grazinantis tiesa, jei tie vektoriai nelygus
        
        template<typename U>
        friend ostream& operator<<(ostream& output, const Vector<U>& other); // Perkraunamas, vektoriaus isvedimo operatorius
};

#include "vector.cpp"

#endif