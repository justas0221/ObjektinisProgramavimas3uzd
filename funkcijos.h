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

struct studentas;
bool tikRaides(string);
string didziosios(string &);
int tarpuSkaicius(string);
int generuotiPazymi();
string generuotiVarda(int);
string generuotiPavarde(int);
bool palygintiMazejant(const studentas&, const studentas&);
bool palygintiDidejant(const studentas&, const studentas&);
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