#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

// std::vector funkcionaluma atkartojanti klase
template<class T>
class Vector
{
    private:
        int sz;                                     // Vektoriaus elementu skaicius
        int cap;                                    // Vektoriaus talpa  
        T* elem;                                    // Rodykle i vektoriaus elementus
    public:
        using value_type             = T;
        using allocator_type         = Allocator;
        using pointer                = typename allocator_traits<Allocator>::pointer;
        using const_pointer          = typename allocator_traits<Allocator>::const_pointer;
        using reference              = value_type&;
        using const_reference        = const value_type&;
        using size_type              = size_t;;
        using difference_type        = ptrdiff_t;
        using iterator               = T*;
        using const_iterator         = const T*;
        using reverse_iterator       = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        // Konstruktoriai
        Vector();
        Vector(int s);
        Vector(int s, T value);
        Vector(const initializer_list<T>& list);
        Vector(const Vector& other);                // Copy kontruktorius
        ~Vector();                                  // Destruktorius: atlaisvina vektoriaus klasės objekto resursus

        void push_back(T value);                    // Elemento pridejimo i vektoriaus gala funkcija
        void pop_back();                            // Elemento isemimo is vektoriaus galo funkcija
        void erase(int index);                      // Funkcija, pasalinanti elementa, esanti nurodyto indekso vietoje
        void insert(int index, T value);                      // Funkcija, pridedanti nurodyta elementa (2), i nurodyta indekso vieta (1)
        void clear();                               // Funkcija, isvalanti vektoriu
        bool empty() const;                         // Funkcija, grazinanti true arba false, priklausomai nuo to, ar vektorius tuscias ar ne
        int size() const;                           // Funkcija, grazinanti vektoriaus dydi
        int capacity() const;                       // Funkcija, grazinanti vektoriaus talpa

        bool operator==(const Vector& other) const; // Operatorius, lyginantis du vektorius ir grazinantis tiesa, jei tie vektoriai lygus
        bool operator!=(const Vector& other) const; // Operatorius, lyginantis du vektorius ir grazinantis tiesa, jei tie vektoriai nelygus
        Vector& operator=(const Vector& other);     // Operatorius, priskiriantis desineje lygybes puseje esancio vektoriaus reiksmes kaireje puseje esanciam vektoriui
        T& operator[](int index);                   // Operatorius, leidziantis pasiekti konkretu vektoriaus elementa
        T& at(int index);                           // Funkcija, grazinanti vektoriaus elementa, esanti i funkcija perduoto indekso vietoje
        T& front();                                 // Funkcija, grazinanti pirmaji vektoriaus elementa
        T& back();                                  // Funkcija, grazinanti paskutini vektoriaus elementa
    
        template<typename U>
        friend ostream& operator<<(ostream& output, const Vector<U>& other); // Perkraunamas, vektoriaus isvedimo operatorius
};

#include "vector.cpp"

#endif