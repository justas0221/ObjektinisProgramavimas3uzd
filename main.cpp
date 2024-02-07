#include <iostream>
#include <numeric>
#include <functional>
#include <iomanip>

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

    cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << endl;
    cout << left << setw(80) << setfill('-') << "-" << endl;
    cout << setfill(' ');

    for(int i = 0; i < 5; i++)
    {
        cout << left << setw(20) << stud[i].vardas << setw(20) << stud[i].pavarde << setw(20) << fixed << setprecision(2) << stud[i].galutinis << endl;
    }
    
    return 0;
}