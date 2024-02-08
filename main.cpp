#include <iostream>
#include <numeric>
#include <functional>
#include <iomanip>

using namespace std;

const int n = 5;
const int m = 5;

struct studentas
{
    string vardas, pavarde;
    int nd[n];
    int egz;
    double vidurkis, mediana, galutinis;
};

int main()
{
    studentas stud[m];
    char skaiciavimoBudas;

    cout << "Ka norite naudoti galutinio balo skaiciavimui, pazymiu vidurki ar mediana? (Irasykite \"V\" arba \"M\") "; cin >> skaiciavimoBudas;

    for (int i = 0; i < m; i++)
        {
            cout << "Iveskite studento varda ir pavarde: "; cin >> stud[i].vardas >> stud[i].pavarde;
            cout << "Iveskite " << n << " studento pazymiu(-ius): ";
            for(int j = 0; j < n; j++)
            {
                cin >> stud[i].nd[j];
            }
            cout << "Iveskite studento egzamino pazymi: "; cin >> stud[i].egz;
        }

    if (toupper(skaiciavimoBudas) == 'V') {
        for (int i = 0; i < m; i++)
        {
            stud[i].vidurkis = accumulate(stud[i].nd, stud[i].nd + n, 0.0) / n;
            stud[i].galutinis = 0.4 * stud[i].vidurkis + 0.6 * stud[i].egz;
        }
        cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << endl;
    }
    else
    {
        for (int i = 0; i < m; i++)
        {
            if (n % 2 == 0)
            {
                stud[i].mediana = (stud[i].nd[n / 2] + stud[i].nd[n / 2 - 1]) / 2.0;
            }
            else
            {
                stud[i].mediana = stud[i].nd[n / 2];
            }
            stud[i].galutinis = 0.4 * stud[i].mediana + 0.6 * stud[i].egz;
        }
        cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Med.)" << endl;
    }

    cout << left << setw(80) << setfill('-') << "-" << endl;
    cout << setfill(' ');

    for(int i = 0; i < m; i++)
    {
        cout << left << setw(20) << stud[i].vardas << setw(20) << stud[i].pavarde << setw(20) << fixed << setprecision(2) << stud[i].galutinis << endl;
    }
    
    return 0;
}