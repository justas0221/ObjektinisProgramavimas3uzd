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

using namespace std;
using namespace chrono;

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
        ~studentas() {}
        studentas(istream& is);
        inline string vardas() const { return vardas_; }    // get'eriai, inline
        inline string pavarde() const { return pavarde_; }  // get'eriai, inline
        double getGalutinis() const { return galutinis_; }
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
        void vardoSkaitymas();
        void pazymiuSkaitymas(int, int, int, int);
        void baloSkaiciavimas(studentas&,string);
        friend bool palygintiMazejant(const studentas&, const studentas&);
        friend bool palygintiDidejant(const studentas&, const studentas&);
};

int generuotiPazymi();
string didziosios(string);
bool tikRaides(string);
int tarpuSkaicius(string);
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