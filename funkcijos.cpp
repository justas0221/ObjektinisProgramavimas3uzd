#include "funkcijos.h"
#include "strukturos.h"

// Funkcija, tikrinanti, ar vardas bei pavarde yra sudaryti tik is raidziu
bool tikRaides(string ivedimas)
{
    for(char c : ivedimas) // Keliaujame per kiekviena ivesto zodzio simboli ir tikriname ar tas simbolis yra raide
    {
        if(!isalpha(c))
            return false;
    }
    return true;
}

// Funkcija, pakeicianti visas gauto teksto raides i didziasias
string didziosios(string &tekstas)
{
    for(char &c : tekstas) // Keliaujame per kiekviena ivesto teksto raide ir paverciame ji i didziaja raide
    {
        c = toupper(c);
    }
    return tekstas;
}

// Funkcija, apskaiciuojanti tarpu skaiciu eiluteje
int tarpuSkaicius(string ivedimas)
{
    int kiekis = 0;
    for(char c : ivedimas) // Keliaujame per kiekviena ivedimo simboli ir tikriname ar jis yra tarpas
    {
        if(c == ' ')
            kiekis++;
    }
    return kiekis;
}

// Funkcija, sugeneruojanti atsitiktini skaiciu nuo 1 iki 10 imtinai
int generuotiPazymi()
{
    int skaicius = rand() % 10 + 1;

    return skaicius;
}

// Funkcija, sugeneruojanti studento varda
string generuotiVarda()
{
    ifstream vardai;
    vardai.open("names.txt");

    string vardas;
    int eiluciuSkaicius = 0;

    if (!vardai.is_open())
    {
        cout << "Nepavyko atidaryti vardu failo!" << endl;
        exit(0);
    }

    while(getline(vardai, vardas)) // Skaiciuojame eiluciu skaiciu faile
    {
        eiluciuSkaicius++;
    }

    int eilute = rand() % eiluciuSkaicius + 1; // Atsitiktinai sugeneruotas eilutes numeris

    vardai.clear();
    vardai.seekg(0);

    for (int i = 1; i < eilute; i++) // Einame per faila iki eilutes, esancios pries ta, kurios numeri sugeneravome
    {
        getline(vardai, vardas);
    }

    getline(vardai, vardas); // Nuskaitome sugeneruotu numeriu pazymetoje eiluteje esanti varda

    vardai.close();

    return vardas;
}

// Funkcija, sugeneruojanti studento pavarde
string generuotiPavarde()
{
    ifstream pavardes;
    pavardes.open("surnames.txt");

    string pavarde;
    int eiluciuSkaicius = 0;

    if (!pavardes.is_open())
    {
        cout << "Nepavyko atidaryti pavardziu failo!" << endl;
        exit(0);
    }

    while(getline(pavardes, pavarde)) // Skaiciuojame eiluciu skaiciu faile
    {
        eiluciuSkaicius++;
    }

    int eilute = rand() % eiluciuSkaicius + 1; // Atsitiktinai sugeneruotas eilutes numeris

    pavardes.clear();
    pavardes.seekg(0);

    for (int i = 1; i < eilute; i++) // Einame per faila iki eilutes, esancios pries ta, kurios numeri sugeneravome
    {
        getline(pavardes, pavarde);
    }

    getline(pavardes, pavarde); // Nuskaitome sugeneruotu numeriu pazymetoje eiluteje esanti varda

    pavardes.close();

    return pavarde;
}

bool palygintiDidejant(studentas& a, studentas& b)
{
    return a.galutinis > b.galutinis;
}


bool palygintiMazejant(studentas& a, studentas& b)
{
    return a.galutinis < b.galutinis;
}

void generuotiFaila(int studKiekis, int pazKiekis, string failoVardas)
{
    ofstream naujas(failoVardas);
    stringstream eilute;

    eilute << left << setw(20) << "Vardas" << setw(20) << "Pavarde"; // Isvedame antrastine eilute
    for (int i = 0; i < pazKiekis; i++)
    {
        string nd = "ND" + to_string(i + 1);

        eilute << setw(10) << nd;
    }
    eilute << setw(10) << "Egz." << endl;

    for (int i = 0; i < studKiekis; i++)
    {
        string vardas = "Vardas" + to_string(i + 1);
        string pavarde = "Pavarde" + to_string(i + 1);

        eilute << left << setw(20) << vardas << setw(20) << pavarde; // Isvedame kiekvieno studento varda ir pavarde
        for (int j = 0; j <= pazKiekis; j++)
        {
            eilute << setw(10) << generuotiPazymi();
        }
        eilute << endl;

        if ((i + 1) % 1000000 == 0)
        {
            naujas << eilute.str();
            eilute.str("");
        }
    }

    naujas << eilute.str();
    eilute.clear();

    naujas.close();
}