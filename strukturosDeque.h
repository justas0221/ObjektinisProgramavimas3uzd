#include "funkcijos.h"

// Studento duomenis sauganti struktura naudojant deka
struct studentas
{
    string vardas, pavarde;
    deque<int> nd;
    int egz;
    double vidurkis, mediana, galutinis;
};