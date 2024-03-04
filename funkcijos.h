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

using namespace std;

struct studentas;
bool tikRaides(string);
string didziosios(string &);
int tarpuSkaicius(string);
int generuotiPazymi();
string generuotiVarda();
string generuotiPavarde();
bool palygintiMazejant(studentas, studentas);
bool palygintiDidejant(studentas, studentas);
void generuotiFaila(int, int);