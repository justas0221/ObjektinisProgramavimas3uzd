#ifndef VECTOR_H
#define VECTOR_H

#include "funkcijos.h"

// std::vector funkcionaluma atkartojanti klase
template<typename T>
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
        ~Vector();                      // Destruktorius: atlaisvina vektoriaus klasės objekto resursus
        void push_back(T value);        // Elemento pridejimo i vektoriaus gala funkcija
        bool empty();                   // Funkcija, grazinanti true arba false, priklausomai nuo to, ar vektorius tuscias ar ne
        int size();                     // Funkcija, grazinanti vektoriaus dydi
        int capacity();                 // Funkcija, grazinanti vektoriaus talpa
};

#endif