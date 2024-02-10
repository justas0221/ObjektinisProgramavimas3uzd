#include <iostream>
#include <numeric>
#include <functional>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

bool tikRaides(string ivedimas);
string didziosios(string &tekstas);
int tarpuSkaicius(string ivedimas);

const int n = 5; // Vieno studento pazymiu skaicius
const int m = 5; // Studentu skaicius

// Studento duomenis sauganti struktura
struct studentas
{
    string vardas, pavarde;
    int nd[n];
    int egz;
    double vidurkis, mediana, galutinis;
};

int main()
{
    studentas stud[m]; // Studentu strukturu masyvas
    string skaiciavimoBudas; // Kintamasis, kuriame saugomas vartotojo pasirinkimas, kaip skaiciuoti galutini bala, naudojant vidurki ar mediana
    int tarpai;
    bool teisingasIvedimas;

    do
    {
        cout << "Ka norite naudoti galutinio balo skaiciavimui, pazymiu vidurki ar mediana? (Irasykite \'V\' arba \'M\') "; cin >> skaiciavimoBudas; // Vartotojo prasome ivesti vidurkio skaiciavimo buda tol, kol jis ives reikiama simboli

        teisingasIvedimas = true;

        skaiciavimoBudas = didziosios(skaiciavimoBudas); // Ivestos raides pakeiciamos i didziasias, kad reiktu maziau tikrinti

        if (skaiciavimoBudas != "V" && skaiciavimoBudas != "M" || cin.peek() != '\n') // Tikriname, ar vartotojas ivede viena is dvieju galimu ivesti raidziu be jokiu papildomu simboliu, jei ne, tuomet pranesame vartotojui apie klaida
        {
            teisingasIvedimas = false;
            cout << "Klaidingi duomenys. Iveskite V arba M." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!teisingasIvedimas);

    for (int i = 0; i < m; i++) // Ciklas, einantis per kiekviena studenta
        {
            do
            {
                cout << "Iveskite studento varda: "; cin >> stud[i].vardas; // Prasome vartotojo ivesti kiekvieno studento varda tol, kol tas vardas yra vienas zodis, sudarytas tik is raidziu
                teisingasIvedimas = true;

                tarpai = tarpuSkaicius(stud[i].vardas); // Randame ivesties tarpu skaiciu
                if (tarpai != 0 || !tikRaides(stud[i].vardas) || cin.peek() != '\n') // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                {
                    teisingasIvedimas = false;
                    cout << "Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju)." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruojama viskas, kas ivesta po pirmojo zodzio
                }
            } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas
            do
            {
                cout << "Iveskite studento pavarde: "; cin >> stud[i].pavarde; // Prasome vartotojo ivesti kiekvieno studento pavarde tol, kol ta pavarde yra vienas zodis, sudarytas tik is raidziu
                teisingasIvedimas = true;

                tarpai = tarpuSkaicius(stud[i].pavarde);
                if (tarpai != 0 || !tikRaides(stud[i].pavarde) || cin.peek() != '\n') // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                {
                    teisingasIvedimas = false;
                    cout << "Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruojama viskas, kas ivesta po pirmojo zodzio
                }
                
            } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas

            stud[i].vardas = didziosios(stud[i].vardas); // Kiekviena vardo raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis
                
            stud[i].pavarde = didziosios(stud[i].pavarde); // Kiekviena pavardes raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis

            for(int j = 0; j < n; j++) // Ciklas, einantis per visus kiekvieno studento pazymius
            {
                string ivedimas;
                do
                {
                    cout << "Iveskite " << i + 1 << "-o studento " << j + 1 << "-aji pazymi: ";
                    cin >> ivedimas;

                    teisingasIvedimas = true;

                    if (ivedimas.size() < 1 || (ivedimas.size() > 2 || (ivedimas.size() == 2 && (ivedimas[0] != '1' || ivedimas[1] != '0')) || cin.peek() != '\n') || !isdigit(ivedimas[0])) // Tikriname, ar vartotojo ivedima sudaro vienas arba du simboliai, jei ji sudaro du simboliai tikriname ar pirmas simbolis - vienetas, o antras - nulis, ir tikriname ar po pirmo skaiciaus iskart eina naujos eilutes simbolis
                    {
                        teisingasIvedimas = false; // Jei atsitinka taip, kad kazkuris is reikalavimu yra patenkinamas, tuomet pranesame apie klaida, isvalome klaidu flag'us ir ignoruojame likusia eilutes dali
                        cout << "Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else
                    {
                        int pazymys = stoi(ivedimas); // Paverciame ivesta string'a i int'a
                        if (pazymys < 1 || pazymys > 10) // Jei tas skaicius nera tarp 1 ir 10 imtinai, pranesame apie klaida
                        {
                            teisingasIvedimas = false;
                            cout << "Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10." << endl;
                        }
                        else
                        {
                            stud[i].nd[j] = pazymys; // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji i atitinkamo studento pazymiu masyva
                        }
                    }
                } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas yra neteisingas
            }
            do
            {
                string ivedimas;
                cout << "Iveskite studento egzamino pazymi: ";
                cin >> ivedimas;
                
                teisingasIvedimas = true;

                if (ivedimas.size() < 1 || (ivedimas.size() > 2 || (ivedimas.size() == 2 && (ivedimas[0] != '1' || ivedimas[1] != '0')) || cin.peek() != '\n') || !isdigit(ivedimas[0])) // Tikriname, ar vartotojo ivedima sudaro vienas arba du simboliai, jei ji sudaro du simboliai tikriname ar pirmas simbolis - vienetas, o antras - nulis, ir tikriname ar po pirmo skaiciaus iskart eina naujos eilutes simbolis
                    {
                        teisingasIvedimas = false; // Jei atsitinka taip, kad kazkuris is reikalavimu yra patenkinamas, tuomet pranesame apie klaida, isvalome klaidu flag'us ir ignoruojame likusia eilutes dali
                        cout << "Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else
                    {
                        int pazymys = stoi(ivedimas); // Paverciame ivesta string'a i int'a
                        if (pazymys < 1 || pazymys > 10) // Jei tas skaicius nera tarp 1 ir 10 imtinai, pranesame apie klaida
                        {
                            teisingasIvedimas = false;
                            cout << "Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10." << endl;
                        }
                        else
                        {
                            stud[i].egz = pazymys; // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji kaip atitinkamo studento egzamino pazymi
                        }
                    }
            } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas yra neteisingas
        }

    if (skaiciavimoBudas == "V") {
        for (int i = 0; i < m; i++) // Jei vartotojas galutinio balo skaiciavimui pasirinko naudoti pazymiu vidurki, tuomet skaiciuojame kiekvieno studento vidurki, o paskui ir galutini bala 
        {
            stud[i].vidurkis = accumulate(stud[i].nd, stud[i].nd + n, 0.0) / n;
            stud[i].galutinis = 0.4 * stud[i].vidurkis + 0.6 * stud[i].egz;
        }
        cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << endl; // Tvarkingai isvedame antrastine eilute
    }
    else
    {
        for (int i = 0; i < m; i++) // Jei vartotojas galutinio balo skaiciavimui pasirinko naudoti pazymiu mediana, tuomet skaiciuojame kiekvieno studento pazymiu mediana, o paskui ir galutini bala
        {
            if (n % 2 == 0)
            {
                stud[i].mediana = (stud[i].nd[n / 2] + stud[i].nd[n / 2 - 1]) / 2.0; // Jei pazymiu kiekis yra lyginis skaicius, mediana skaiciuojame rasdami dvieju viduriniu pazymiu aritmetini vidurki
            }
            else
            {
                stud[i].mediana = stud[i].nd[n / 2]; // Jei pazymiu kiekis yra nelyginis skaicius, medianai priskiriame vidurini pazymi is pazymiu aibes
            }
            stud[i].galutinis = 0.4 * stud[i].mediana + 0.6 * stud[i].egz; // Suskaiciuojame studento galutini bala, naudodami pazymiu mediana
        }
        cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Med.)" << endl; // Tvarkingai isvedame antrastine eilute
    }

    cout << left << setw(80) << setfill('-') << "-" << endl; // Antrastinei eilutei atskirti naudojame is punktyrines linijos sudaryta antraja eilute
    cout << setfill(' ');

    for(int i = 0; i < m; i++)
    {
        cout << left << setw(20) << stud[i].vardas << setw(20) << stud[i].pavarde << setw(20) << fixed << setprecision(2) << stud[i].galutinis << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
    }
    
    return 0;
}

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