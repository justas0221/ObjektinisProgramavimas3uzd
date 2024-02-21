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

using namespace std;

// Studento duomenis sauganti struktura
struct studentas
{
    string vardas, pavarde;
    vector<int> nd;
    int egz;
    double vidurkis, mediana, galutinis;
};

bool tikRaides(string ivedimas);
string didziosios(string &tekstas);
int tarpuSkaicius(string ivedimas);
int generuotiPazymi();
string generuotiVarda();
string generuotiPavarde();
bool palygintiMazejant(studentas a, studentas b);
bool palygintiDidejant(studentas a, studentas b);

int main()
{
    vector<studentas> stud; // Studentu strukturu vektorius
    string skaiciavimoBudas, eilute; // Kintamasis, kuriame saugomas vartotojo pasirinkimas, kaip skaiciuoti galutini bala, naudojant vidurki ar mediana
    int tarpai;
    bool teisingasIvedimas, isvedimasFaile, rikiavimas;
    int i = 0, j, parinktis, studentuKiekis, k, l, papildymas;
    char testiPrograma;
    ifstream input;

    srand(time(0));

    do // Prasome studento ivesti skaiciu, nuo kurio priklausys, kaip bus vykdoma programa
    {
        cout << "Pasirinkite, kaip norite vykdyti programa\n1 - Viska vesti ranka\n2 - Generuoti pazymius atsitiktinai\n3 - Generuoti pazymius ir studentu vardus, pavardes atsitiktinai\n4 - Baigti darba\n5 - Skaityti duomenis is failo\n"; cin >> parinktis;

        teisingasIvedimas = true;

        if (parinktis != 1 && parinktis != 2 && parinktis != 3 && parinktis != 4 && parinktis != 5 || cin.peek() != '\n')
        {
            teisingasIvedimas = false;
            cout << "Klaidingi duomenys. Iveskite kazkuri is skaiciu nuo 1 iki 5 imtinai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!teisingasIvedimas);

    if (parinktis == 4)
    {
        exit(0);
    }

    if (parinktis != 5) // Prasome ivesti pradini studentu kieki
    {
        do
        {
            cout << "Iveskite studentu kieki (nuo 1 iki 10 imtinai): "; cin >> studentuKiekis;

            teisingasIvedimas = true;

            if (studentuKiekis > 10 || studentuKiekis < 1 || cin.peek() != '\n')
            {
                teisingasIvedimas = false;
                cout << "Klaidingi duomenys. Iveskite sveikaji skaiciu nuo 1 iki 10 imtinai." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!teisingasIvedimas);
    
    }

    if (parinktis == 5) // Jei vartotojas nori nuskaityti duomenis is failo, atidarome duomenu faila ir praleidziame pirmaja eilute, kuri yra antrastine
    {
        input.open("studentai1000000.txt");
        getline(input, eilute);
    }

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

    do // Klausiame vartotojo, kokia tvarka jis nori isrikiuoti studentus rezultatuose
    {
        cout << "Jei norite studentus isrikiuoti pagal galutini bala mazejimo tvarka, iveskite \"1\", jei didejimo, iveskite \"0\": "; cin >> rikiavimas;

        teisingasIvedimas = true;

        if (rikiavimas != 1 && rikiavimas != 0 || cin.peek() != '\n')
        {
            teisingasIvedimas = false;
            cout << "Klaidingi duomenys. Iveskite \"1\" arba \"0\"." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!teisingasIvedimas);

    do // Klausiame vartotojo, ar jis nori rezultatus irasyti i faila, ar isvesti i ekrana
    {
        cout << "Jei norite rezultatus irasyti i faila, iveskite \"1\", jei norite isvesti juos i ekrana, iveskite \"0\": "; cin >> isvedimasFaile;

        teisingasIvedimas = true;

        if (isvedimasFaile != 1 && isvedimasFaile != 0 || cin.peek() != '\n')
        {
            cout << "Klaidingi duomenys. Iveskite \"1\" arba \"0\"." << endl;
            teisingasIvedimas = false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!teisingasIvedimas);

    auto start = chrono::high_resolution_clock::now(); // Pradedame programos veikimo laikmati

    l = 0;
    papildymas = 0;

    while (true)
    {
        studentuKiekis += papildymas;
        studentas naujasStudentas;

        if (parinktis != 5)
        {
            for (int i = l; i < studentuKiekis; i++)
            {
                int randomPazymiuKiekis = rand() % 10 + 1;
                int pazymiuKiekis = 0;
                
                if (parinktis == 1 || parinktis == 2)
                {
                    do
                    {
                        cout << "Iveskite studento varda: "; cin >> naujasStudentas.vardas; // Prasome vartotojo ivesti kiekvieno studento varda tol, kol tas vardas yra vienas zodis, sudarytas tik is raidziu
                        teisingasIvedimas = true;

                        tarpai = tarpuSkaicius(naujasStudentas.vardas); // Randame ivesties tarpu skaiciu
                        if (tarpai != 0 || !tikRaides(naujasStudentas.vardas) || cin.peek() != '\n') // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                        {
                            teisingasIvedimas = false;
                            cout << "Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju)." << endl;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruojama viskas, kas ivesta po pirmojo zodzio
                        }
                    } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas
                    do
                    {
                        cout << "Iveskite studento pavarde: "; cin >> naujasStudentas.pavarde; // Prasome vartotojo ivesti kiekvieno studento pavarde tol, kol ta pavarde yra vienas zodis, sudarytas tik is raidziu
                        teisingasIvedimas = true;

                        tarpai = tarpuSkaicius(naujasStudentas.pavarde);
                        if (tarpai != 0 || !tikRaides(naujasStudentas.pavarde) || cin.peek() != '\n') // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                        {
                            teisingasIvedimas = false;
                            cout << "Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu." << endl;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruojama viskas, kas ivesta po pirmojo zodzio
                        }
                        
                    } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas

                    naujasStudentas.vardas = didziosios(naujasStudentas.vardas); // Kiekviena vardo raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis
                            
                    naujasStudentas.pavarde = didziosios(naujasStudentas.pavarde); // Kiekviena pavardes raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis
                }

                if (parinktis == 1)
                {
                    do
                    {
                        cout << "Kiek pazymiu norite ivesti siam studentui? (Irasykite skaiciu nuo 1 iki 10 imtinai): "; cin >> pazymiuKiekis;

                        teisingasIvedimas = true;

                        if (pazymiuKiekis > 10 || pazymiuKiekis < 1 || cin.peek() != '\n')
                        {
                            teisingasIvedimas = false;
                            cout << "Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 10 imtinai." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    } while (!teisingasIvedimas);

                    k = 0;
                    papildymas = 0;
                    
                    while (true)
                    {
                        pazymiuKiekis += papildymas;

                        for (int j = k; j < pazymiuKiekis; j++)
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
                                        naujasStudentas.nd.push_back(pazymys); // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji i atitinkamo studento pazymiu masyva
                                    }
                                }
                            } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas yra neteisingas
                            
                            k = j + 1;
                        }

                        do
                        {
                            cout << "Jei norite daugiau pazymiu, iveskite papildomu pazymiu kieki (Irasykite skaiciu nuo 1 iki 10 imtinai), jei ne, iveskite bet koki simboli ir spauskite \"Enter\": "; // Klausiame, ar vartotojas nori prideti daugiau pazymiu i vektoriu
                            cin >> papildymas;

                            teisingasIvedimas = true;

                            if (papildymas == 0)
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            }
                            else if (papildymas > 10 || papildymas < 1)
                            {
                                teisingasIvedimas = false;
                                cout << "Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 10 imtinai." << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        } while (!teisingasIvedimas);

                        if (papildymas == 0)
                        {
                            break;
                        }
                    }

                    do
                    {
                        string ivedimas;

                        cout << "Iveskite " << i + 1 << "-o studento egzamino pazymi: ";
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
                                    naujasStudentas.egz = pazymys; // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji kaip atitinkamo studento egzamino pazymi
                                }
                            }
                    } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas yra neteisingas
                }

                if (parinktis == 2)
                {
                        for (int j = 0; j < randomPazymiuKiekis; j++)
                        {
                            int pazymys = generuotiPazymi();
                            
                            naujasStudentas.nd.push_back(pazymys); // Sugeneruota pazymi pridedame i vektoriu
                                
                            cout << "Sugeneruotas " << i + 1 << "-o studento " << j + 1 << "-aji pazymys: " << pazymys << endl;
                        }
                        
                        int pazymys = generuotiPazymi();

                        naujasStudentas.egz = pazymys;

                        cout << "Sugeneruotas " << i + 1 << "-o studento egzamino pazymys: " << pazymys << endl;
                }

                if (parinktis == 3)
                {
                        naujasStudentas.vardas = generuotiVarda(); // Sugeneruota varda priskiriame naujam studentui
                        naujasStudentas.pavarde = generuotiPavarde(); // Sugeneruota pavarde priskiriame naujam studentui

                        cout << "Sugeneruoti " << i + 1 << "-o studento vardas ir pavarde: " << naujasStudentas.vardas << " " << naujasStudentas.pavarde << endl;
                        for (int j = 0; j < randomPazymiuKiekis; j++)
                        {
                            int pazymys = generuotiPazymi();
                            
                            naujasStudentas.nd.push_back(pazymys); // Sugeneruota pazymi pridedame i vektoriu

                            cout << "Sugeneruotas " << i + 1 << "-o studento " << j + 1 << "-asis pazymys: " << pazymys << endl;
                        }
                        
                        int pazymys = generuotiPazymi();

                        naujasStudentas.egz = pazymys;

                        cout << "Sugeneruotas " << i + 1 << "-o studento egzamino pazymys: " << pazymys << endl;
                }

                stud.push_back(naujasStudentas);
                naujasStudentas.nd.clear();
                l = i + 1;
            }
    
            do
            {
                cout << "Jei norite daugiau studentu, iveskite papildomu studentu kieki (Irasykite skaiciu nuo 1 iki 10 imtinai), jei ne, iveskite bet koki simboli ir spauskite \"Enter\": "; // Klausiame, ar vartotojas nori prideti daugiau studentu i vektoriu
                cin >> papildymas;

                teisingasIvedimas = true;

                if (papildymas == 0)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                else if (papildymas > 10 || papildymas < 1)
                {
                    teisingasIvedimas = false;
                    cout << "Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 10 imtinai." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (!teisingasIvedimas);

            if (papildymas == 0)
            {
                break;
            }
        }
        else
        {
            getline(input, eilute); // Praleidziame pirmaja failo eilute

            while (getline(input, eilute)) // Skaitome duomenis is failo kol ju yra
            {
                istringstream iss(eilute); // Padaliname juos i atskirus string'us, atskirtus tarpais
                string dalis;

                iss >> naujasStudentas.vardas >> naujasStudentas.pavarde;

                while (iss >> dalis)
                {
                    int pazymys = stoi(dalis); // Pazymi paverciame is string'o i int'a ir pridedame i naujo studento pazymiu vektoriu
                    naujasStudentas.nd.push_back(pazymys);
                }

                naujasStudentas.egz = naujasStudentas.nd.back();

                naujasStudentas.nd.pop_back();

                stud.push_back(naujasStudentas); // Nauja studenta pridedame i studentu vektoriaus gala
                naujasStudentas.nd.clear();
            }

        }
        if (parinktis == 5) // Jei vartotojas rinkosi nuskaityti duomenis is failo, cia nuskaitymas ir baigiasi, nes prideti studentu neimanoma
        {
            break;
        }
    }

    input.close(); // uzdarome duomenu faila

    for (int i = 0; i < stud.size(); i++) // Skaiciuojame kiekvieno studento vidurki, mediana, o paskui ir galutinius balus 
    {
        stud[i].vidurkis = accumulate(stud[i].nd.begin(), stud[i].nd.end(), 0.0) / stud[i].nd.size();
        if (stud[i].nd.size() % 2 == 0)
        {
            stud[i].mediana = (stud[i].nd[stud[i].nd.size() / 2] + stud[i].nd[stud[i].nd.size() / 2 - 1]) / 2.0; // Jei pazymiu kiekis yra lyginis skaicius, mediana skaiciuojame rasdami dvieju viduriniu pazymiu aritmetini vidurki
        }
        else
        {
            stud[i].mediana = stud[i].nd[floor(stud[i].nd.size() / 2)]; // Jei pazymiu kiekis yra nelyginis skaicius, medianai priskiriame vidurini pazymi is pazymiu aibes
        }
        if (skaiciavimoBudas == "V")
        {
            stud[i].galutinis = 0.4 * stud[i].vidurkis + 0.6 * stud[i].egz; // Suskaiciuojame studento galutini bala, naudodami pazymiu vidurki
        }
        else
        {
            stud[i].galutinis = 0.4 * stud[i].mediana + 0.6 * stud[i].egz; // Suskaiciuojame studento galutini bala, naudodami pazymiu mediana
        }
    }

    if (rikiavimas) // Priklausomai nuo to, kaip studentus isrikiuoti norejo vartotojas, iskvieciame tam skirtas funkcijas
    {
        sort(stud.begin(), stud.end(), palygintiDidejant);
    }
    else
    {
        sort(stud.begin(), stud.end(), palygintiMazejant);
    }
    
    if (isvedimasFaile)
    {
        ofstream output;
        output.open("output.txt");

        output << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl; // Tvarkingai isvedame antrastine eilute
        output << left << setw(80) << setfill('-') << "-" << endl; // Antrastinei eilutei atskirti naudojame is punktyrines linijos sudaryta antraja eilute
        output << setfill(' ');
        
        if (skaiciavimoBudas == "V")
        {    
            for(int i = 0; i < stud.size(); i++)
            {
                output << left << setw(20) << stud[i].vardas << setw(20) << stud[i].pavarde << setw(20) << fixed << setprecision(2) << stud[i].galutinis << setw(20) << "-.--" << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
            }
        }
        else
        {
            for(int i = 0; i < stud.size(); i++)
            {
                output << left << setw(20) << stud[i].vardas << setw(20) << stud[i].pavarde << setw(20) << "-.--" << setw(20) << fixed << setprecision(2) << stud[i].galutinis << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
            }
        }

        output.close();
    }
    else
    {
        cout << endl;
        cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl; // Tvarkingai isvedame antrastine eilute
        cout << left << setw(80) << setfill('-') << "-" << endl; // Antrastinei eilutei atskirti naudojame is punktyrines linijos sudaryta antraja eilute
        cout << setfill(' ');

        if (skaiciavimoBudas == "V")
        {    
            for(int i = 0; i < stud.size(); i++)
            {
                cout << left << setw(20) << stud[i].vardas << setw(20) << stud[i].pavarde << setw(20) << fixed << setprecision(2) << stud[i].galutinis << setw(20) << "-.--" << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
            }
        }
        else
        {
            for(int i = 0; i < stud.size(); i++)
            {
                cout << left << setw(20) << stud[i].vardas << setw(20) << stud[i].pavarde << setw(20) << "-.--" << setw(20) << fixed << setprecision(2) << stud[i].galutinis << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
            }
        }
    }

    auto end = chrono::high_resolution_clock::now(); // Sustabdome laikmati

    chrono::duration<double> duration = end - start; // Apskaiciuojame programos veikimo laika ir ji atspausdiname i ekrana

    cout << "Programos veikimo laikas sekundemis: " << duration.count() << endl;

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

bool palygintiDidejant(studentas a, studentas b)
{
    return a.galutinis > b.galutinis;
}


bool palygintiMazejant(studentas a, studentas b)
{
    return a.galutinis < b.galutinis;
}