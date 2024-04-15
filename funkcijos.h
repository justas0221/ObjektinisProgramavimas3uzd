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

class zmogus
{
    protected:
        string vardas_, pavarde_;
    protected:
        zmogus(string vardas = "", string pavarde = "") : vardas_(vardas), pavarde_(pavarde) {}
        ~zmogus() { cout << "zmogus destructor called" << endl; vardas_.clear(), pavarde_.clear(); }
    public:
        inline string vardas() const { return vardas_; }    // get'eriai, inline
        inline string pavarde() const { return pavarde_; }  // get'eriai, inline
        virtual void didziosiosVardas() { for(char &c : vardas_) c = toupper(c); } // Keliaujame per kiekviena ivesto teksto raide ir paverciame ja i didziaja raide
        virtual void didziosiosPavarde() { for(char &c : pavarde_) c = toupper(c); } // Keliaujame per kiekviena ivesto teksto raide ir paverciame ja i didziaja raide
        virtual void generuotiVarda(int i)
        {
            string vardas;
            vardas = "Vardas" + to_string(i + 1);
            vardas_ = vardas;
        }
        virtual void generuotiPavarde(int i)
        {
            string pavarde;
            pavarde = "Pavarde" + to_string(i + 1);
            pavarde_ = pavarde;
        }
};

// Studento duomenis sauganti struktura
class studentas : public zmogus
{
    private:
        vector<int> nd_;
        int egz_;
        double vidurkis_, mediana_, galutinis_;
    public:
        studentas() : zmogus(), egz_(0) {}  // default konstruktorius
        ~studentas() { cout << "studentas destructor called" << endl; clearNd(); } // destruktorius
        studentas(istream& is);
        studentas(const studentas& other) :
            zmogus(other.vardas_, other.pavarde_),
            nd_(other.nd_),
            egz_(other.egz_),
            vidurkis_(other.vidurkis_),
            mediana_(other.mediana_),
            galutinis_(other.galutinis_) {} // Copy konstruktorius
        studentas(studentas&& other) noexcept :
            zmogus(move(other.vardas_), move(other.pavarde_)),
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
        double galutinis() const { return galutinis_; }
        int getEgz() const { return egz_; }
        const vector<int>& getNd() const { return nd_; }
        void clearNd() { nd_.clear(); }
        int gautiPaskutiniPazymi();
        void generuotiEgzPazymi();
        void generuotiNdPazymi();
        void baloSkaiciavimas(string);
        void didziosiosVardas() override { zmogus::didziosiosVardas(); }
        void didziosiosPavarde() override { zmogus::didziosiosPavarde(); }
        void generuotiVarda(int i) override { zmogus::generuotiVarda(i); }
        void generuotiPavarde(int i) override { zmogus::generuotiPavarde(i); }
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