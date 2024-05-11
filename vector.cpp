#include "vector.h"

// Konstruktoriai   
Vector::Vector()
{ 
    sz = 0; 
    elem = new double[sz];
}

Vector::Vector(int s)
{
    sz = s; 
    elem = new double[s]; 
}

Vector::Vector(int s, double val)
{
    sz = s; 
    elem = new double[s];
    fill_n(elem, s, val);  
}

// Destruktorius: atlaisvina vektoriaus klasės objekto resursus
Vector::~Vector()
{ 
    delete[] elem; 
    cout << "Object destroyed" << endl; 
}

