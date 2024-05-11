#include "funkcijos.h"

// std::vector funkcionaluma atkartojanti klase
class Vector
{
    private:
        int sz;        // Vektoriaus elementu skaicius
        double* elem;  // Rodykle i vektoriaus elementus
    public:
        // Konstruktoriai
        Vector();
        Vector(int s);
        Vector(int s, double val);
        // Destruktorius: atlaisvina vektoriaus klasės objekto resursus
        ~Vector();
};