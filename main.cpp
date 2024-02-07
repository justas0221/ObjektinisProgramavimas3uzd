#include <iostream>
#include <numeric>
#include <functional>

using namespace std;

struct studentas
{
    string vardas, pavarde;
    int nd[5];
    int egz;
    double vidurkis, galutinis;
};

int main()
{
    studentas stud[5];

    for (int i = 0; i < 5; i++)
    {
        cout << "Iveskite studento varda ir pavarde: "; cin >> stud[i].vardas >> stud[i].pavarde;
        cout << "Iveskite 5 studento pazymius: ";
        for(int j = 0; j < 5; j++)
        {
            cin >> stud[i].nd[j];
        }
        cout << "Iveskite studento egzamino pazymi: "; cin >> stud[i].egz;
    }

    for (int i = 0; i < 5; i++)
    {
        stud[i].vidurkis = accumulate(stud[i].nd, stud[i].nd + 5, 0.0) / 5;
        stud[i].galutinis = 0.4 * stud[i].vidurkis + 0.6 * stud[i].egz;
    }

    return 0;
}