#include <iostream>
#include <numeric>
#include <functional>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <list>
#include <deque>
#include <utility>

using namespace std;
using namespace chrono;

extern string skaiciavimoBudas;
extern int pazymiuKiekis, parinktis, papildymas, k, i, randomPazymiuKiekis;

// Studento duomenis sauganti struktura
class studentas
{
    private:
        string vardas_, pavarde_;
        vector<int> nd_;
        int egz_;
        double vidurkis_, mediana_, galutinis_;
    public:
        studentas() : egz_(0) {}  // default konstruktorius
        ~studentas() { clearNd(); } // destruktorius
        studentas(istream& is);
        studentas(const studentas& other) :
            vardas_(other.vardas_),
            pavarde_(other.pavarde_),
            nd_(other.nd_),
            egz_(other.egz_),
            vidurkis_(other.vidurkis_),
            mediana_(other.mediana_),
            galutinis_(other.galutinis_) {} // Copy konstruktorius
        studentas(studentas&& other) noexcept :
            vardas_(move(other.vardas_)), 
            pavarde_(move(other.pavarde_)), 
            nd_(move(other.nd_)), 
            egz_(move(other.egz_)), 
            vidurkis_(move(other.vidurkis_)), 
            mediana_(move(other.mediana_)), 
            galutinis_(move(other.galutinis_)) {} // Move konstruktorius
        studentas& operator=(const studentas& other) { return *this = studentas(other); } // Copy assignment operatorius
        studentas& operator=(studentas&& other) noexcept
        {
            swap(vardas_, other.vardas_);
            swap(pavarde_, other.pavarde_);
            swap(nd_, other.nd_);
            swap(egz_, other.egz_);
            swap(vidurkis_, other.vidurkis_);
            swap(mediana_, other.mediana_);
            swap(galutinis_, other.galutinis_);
            return *this;
        } //Move assignment operatorius
        inline string vardas() const { return vardas_; }    // get'eriai, inline
        inline string pavarde() const { return pavarde_; }  // get'eriai, inline
        double galutinis() const { return galutinis_; }
        int getEgz() const { return egz_; }
        const vector<int>& getNd() const { return nd_; }
        void clearNd() { nd_.clear(); }
        void didziosiosVardas();
        void didziosiosPavarde();
        int gautiPaskutiniPazymi();
        void generuotiEgzPazymi();
        void generuotiNdPazymi();
        void generuotiVarda(int);
        void generuotiPavarde(int);
        void baloSkaiciavimas(string);
        friend bool palygintiMazejant(const studentas&, const studentas&);
        friend bool palygintiDidejant(const studentas&, const studentas&);
        friend ostream& operator<<(ostream&, const studentas&);
        friend istream& operator>>(istream&, studentas&);
};

int generuotiPazymi();
string didziosios(string&);
bool tikRaides(string);
int tarpuSkaicius(string);
void printHeader(ostream&);
void testas(studentas&);
void generuotiFaila(int, int, string);
template <typename Cont>
void failoSkaitymas(ifstream&, Cont&);
template <typename Cont>
void strategija1(Cont&, Cont&, Cont&);
template <typename Cont>
void strategija2(Cont&, Cont&);
template <typename Cont>
void strategija3(Cont&, Cont&);
template <typename Cont>
void rikiuotiDidejant(Cont&);
template <typename Cont>
void rikiuotiMazejant(Cont&);