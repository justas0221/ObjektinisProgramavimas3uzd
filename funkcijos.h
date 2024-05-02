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

// Zmogaus duomenis sauganti klase
class zmogus
{
    protected:
        string vardas_, pavarde_; // Klases kintamieji: zmogaus vardas ir pavarde
    protected:
        zmogus(string vardas = "", string pavarde = "") : vardas_(vardas), pavarde_(pavarde) {} // Default konstruktorius
        ~zmogus() { vardas_.clear(), pavarde_.clear(); } // Destruktorius
    public:
        inline string vardas() const { return vardas_; }    // get'eriai, inline
        inline string pavarde() const { return pavarde_; }  // get'eriai, inline
        virtual void didziosiosVardas() = 0; // Visiskai virtuali funkcija
        virtual void generuotiVarda(int i) // Funkcija, skirta generuoti zmogaus vardui
        {
            string vardas;
            vardas = "Vardas" + to_string(i + 1);
            vardas_ = vardas;
        }
        virtual void generuotiPavarde(int i) // Funkcija, skirta generuoti zmogaus pavardei
        {
            string pavarde;
            pavarde = "Pavarde" + to_string(i + 1);
            pavarde_ = pavarde;
        }
};

// Studento duomenis sauganti klase
class studentas : public zmogus
{
    private:
        vector<int> nd_; // Studento namu darbu pazymiu vektorius
        int egz_; // Studento egzamino pazymys
        double vidurkis_, mediana_, galutinis_; // Studento pazymiu vidurkis, mediana ir galutinis balas
    public:
        studentas() : zmogus(), egz_(0) {}  // default konstruktorius
        ~studentas() { clearNd(); } // destruktorius
        studentas(istream& is); // Konstruktorius su nuoroda i istream objekta, kaip parametru
        studentas(const studentas& other) : // Copy konstruktorius
            zmogus(other.vardas_, other.pavarde_),
            nd_(other.nd_),
            egz_(other.egz_),
            vidurkis_(other.vidurkis_),
            mediana_(other.mediana_),
            galutinis_(other.galutinis_) {}
        studentas(studentas&& other) noexcept : // Move konstruktorius
            zmogus(move(other.vardas_), move(other.pavarde_)),
            nd_(move(other.nd_)), 
            egz_(move(other.egz_)), 
            vidurkis_(move(other.vidurkis_)), 
            mediana_(move(other.mediana_)), 
            galutinis_(move(other.galutinis_)) {}
        studentas& operator=(const studentas& other) { return *this = studentas(other); } // Copy assignment operatorius
        studentas& operator=(studentas&& other) noexcept // Move assignment operatorius
        {
            swap(vardas_, other.vardas_);
            swap(pavarde_, other.pavarde_);
            swap(nd_, other.nd_);
            swap(egz_, other.egz_);
            swap(vidurkis_, other.vidurkis_);
            swap(mediana_, other.mediana_);
            swap(galutinis_, other.galutinis_);
            return *this;
        }
        double galutinis() const { return galutinis_; } // Galutinio balo get'eris
        int getEgz() const { return egz_; } // Egzamino pazymio get'eris
        const vector<int>& getNd() const { return nd_; } // Namu darbu pazymiu vektoriaus get'eris
        void clearNd() { nd_.clear(); } // Funkcija, isvalanti namu darbu pazymiu vektoriu
        int gautiPaskutiniPazymi();
        void generuotiEgzPazymi();
        void generuotiNdPazymi();
        void baloSkaiciavimas(string);
        void didziosiosVardas() { for(char &c : vardas_) c = toupper(c); } // Funkcija, skirta visas vardo raides paversti i didziasias
        void didziosiosPavarde() { for(char &c : pavarde_) c = toupper(c); } // Funkcija, skirta visas pavardes raides paversti i didziasias
        void generuotiVarda(int i) override { zmogus::generuotiVarda(i); } // Funkcija, skirta generuoti varda
        void generuotiPavarde(int i) override { zmogus::generuotiPavarde(i); } // Funkcija, skirta generuoti pavarde
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
void strategija3(Cont&, Cont&);
template <typename Cont>
void rikiuotiDidejant(Cont&);
template <typename Cont>
void rikiuotiMazejant(Cont&);