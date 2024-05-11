#ifndef VECTOR_H
#define VECTOR_H

#include "funkcijos.h"

// std::vector funkcionaluma atkartojanti klase
template<typename T>
class Vector
{
    private:
        int size;      // Vektoriaus elementu skaicius
        int capacity;  // Vektoriaus talpa  
        T* elem;       // Rodykle i vektoriaus elementus
    public:
        // Konstruktoriai
        Vector();
        Vector(int s);
        Vector(int s, T value);
        // Destruktorius: atlaisvina vektoriaus klasės objekto resursus
        ~Vector();
};

#endif