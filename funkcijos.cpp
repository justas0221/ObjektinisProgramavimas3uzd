#include "funkcijos.h"

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

// Funkcija, pakeicianti visas gauto vardo raides i didziasias
void studentas::didziosiosVardas()
{
    for(char &c : vardas_) // Keliaujame per kiekviena ivesto teksto raide ir paverciame ji i didziaja raide
    {
        c = toupper(c);
    }
}

// Funkcija, pakeicianti visas gautos pavardes raides i didziasias
void studentas::didziosiosPavarde()
{
    for(char &c : pavarde_) // Keliaujame per kiekviena ivesto teksto raide ir paverciame ji i didziaja raide
    {
        c = toupper(c);
    }
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

studentas::studentas(istream& is)
{
    is >> vardas_ >> pavarde_;
    int x;
    while(is >> x)
    {
        nd_.push_back(x);
    }
    egz_ = nd_.back();
    nd_.pop_back();
}

// Funkcija, sugeneruojanti atsitiktini skaiciu nuo 1 iki 10 imtinai
studentas::generuotiPazymi()
{
    int skaicius = rand() % 10 + 1;

    return skaicius;
}

// Funkcija, sugeneruojanti studento varda
void studentas::generuotiVarda(int i)
{
    string vardas;
    
    vardas = "Vardas" + to_string(i + 1);

    vardas_ = vardas;
}

// Funkcija, sugeneruojanti studento pavarde
void studentas::generuotiPavarde(int i)
{
    string pavarde;
    
    pavarde = "Pavarde" + to_string(i + 1);

    pavarde_ = pavarde;
}

bool palygintiMazejant(const studentas& a, const studentas& b)
{
    return a.galutinis_ > b.galutinis_;
}


bool palygintiDidejant(const studentas& a, const studentas& b)
{
    return a.galutinis_ < b.galutinis_;
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
            eilute << setw(10) << rand() % 10;
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

void studentas::vardoSkaitymas()
{
    bool teisingasIvedimas;
    int tarpai;

    do
    {
        try
        {
            cout << "Iveskite studento varda: "; // Prasome vartotojo ivesti kiekvieno studento varda tol, kol tas vardas yra vienas zodis, sudarytas tik is raidziu

            if (!(cin >> vardas_))
            {
                throw runtime_error("Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju).");
            }

            tarpai = tarpuSkaicius(vardas_); // Randame ivesties tarpu skaiciu

            teisingasIvedimas = (tarpai == 0 && tikRaides(vardas_) && cin.peek() == '\n');

            if (!teisingasIvedimas) // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
            {
                throw runtime_error("Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju).");
            }
        }
        catch(const exception& e)
        {
            cerr << "Klaida: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas
    do
    {
        try
        {
            cout << "Iveskite studento pavarde: "; // Prasome vartotojo ivesti kiekvieno studento pavarde tol, kol ta pavarde yra vienas zodis, sudarytas tik is raidziu

            if (!(cin >> pavarde_))
            {
                throw runtime_error("Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu.");
            }

            tarpai = tarpuSkaicius(pavarde_); // Randame ivesties tarpu skaiciu

            teisingasIvedimas = (tarpai == 0 && tikRaides(pavarde_) && cin.peek() == '\n');

            if (!teisingasIvedimas) // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
            {
                throw runtime_error("Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu.");
            }
        }
        catch(const exception& e)
        {
            cerr << "Klaida: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas
    return;
}

void studentas::pazymiuSkaitymas(int pazymiuKiekis, int papildymas, int k, int it)
{
    bool teisingasIvedimas;

    while (true)
    {
        pazymiuKiekis += papildymas; // Prie esamo pazymiu kiekio pridedame vartotojo parinkta papildymo kieki

        for (int j = k; j < pazymiuKiekis; j++)
        {
            string ivedimas;
            
            do
            {
                try
                {
                    cout << "Iveskite " << it + 1 << "-o studento " << j + 1 << "-aji pazymi: ";
                    teisingasIvedimas = false;

                    if (!(cin >> ivedimas))
                    {
                        throw runtime_error("Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10.");
                    }

                    teisingasIvedimas = ((ivedimas.size() == 1 || (ivedimas.size() == 2 && (ivedimas[0] == '1' && ivedimas[1] == '0'))) && cin.peek() == '\n' && isdigit(ivedimas[0]));

                    if (!teisingasIvedimas) // Tikriname, ar vartotojo ivedima sudaro vienas arba du simboliai, jei ji sudaro du simboliai tikriname ar pirmas simbolis - vienetas, o antras - nulis, ir tikriname ar po pirmo skaiciaus iskart eina naujos eilutes simbolis
                    {
                        throw runtime_error("Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10.");
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
                            nd_.push_back(pazymys); // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji i atitinkamo studento pazymiu masyva
                        }
                    }
                }
                catch(const exception& e)
                {
                    cerr << "Klaida: " << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
            } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas yra neteisingas
            
            k = j + 1;
        }

        do
        {
            try
            {
                cout << "Jei norite daugiau pazymiu, iveskite papildomu pazymiu kieki (Irasykite skaiciu nuo 1 iki 10 imtinai), jei ne, iveskite \"0\" (nuli) ir spauskite \"Enter\": "; // Klausiame, ar vartotojas nori prideti daugiau pazymiu i vektoriu
                teisingasIvedimas = false;

                if (!(cin >> papildymas))
                {
                    throw runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 10 imtinai.");
                }

                teisingasIvedimas = (papildymas >= 0 && papildymas <= 10 && cin.peek() == '\n');

                if (papildymas == 0)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                else if (!teisingasIvedimas)
                {
                    throw runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 10 imtinai.");
                }
            }
            catch(const exception& e)
            {
                cerr << "Klaida: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
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

        try // Prasome vartotojo ivesti studento pazymius viena po kito
        {
            cout << "Iveskite " << it + 1 << "-o studento egzamino pazymi: ";
            teisingasIvedimas = false;

            if (!(cin >> ivedimas))
            {
                throw runtime_error("Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10.");
            }
                    
            teisingasIvedimas = ((ivedimas.size() == 1 || (ivedimas.size() == 2 && (ivedimas[0] == '1' && ivedimas[1] == '0'))) && cin.peek() == '\n' && isdigit(ivedimas[0]));

            if (!teisingasIvedimas) // Tikriname, ar vartotojo ivedima sudaro vienas arba du simboliai, jei ji sudaro du simboliai tikriname ar pirmas simbolis - vienetas, o antras - nulis, ir tikriname ar po pirmo skaiciaus iskart eina naujos eilutes simbolis
            {
                throw runtime_error("Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10.");
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
                    egz_ = pazymys; // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji kaip atitinkamo studento egzamino pazymi
                }
            }
        }
        catch(const exception& e)
        {
            cerr << "Klaida: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas yra neteisingas
}

void studentas::baloSkaiciavimas(studentas &i, string skaiciavimoBudas)
{
    if (skaiciavimoBudas == "V")
    {
        i.vidurkis_ = accumulate(i.nd_.begin(), i.nd_.end(), 0.0) / i.nd_.size();
        i.galutinis_ = 0.4 * i.vidurkis_ + 0.6 * i.egz_; // Suskaiciuojame studento galutini bala, naudodami pazymiu vidurki
    }
    else
    {
        auto it = i.nd_.begin();
        advance(it, i.nd_.size() / 2); // advance the iterator to the middle of the list

        if (i.nd_.size() % 2 == 0)
        {
            int a = *it;
            --it;
            int b = *it;
            i.mediana_ = (a + b) / 2.0;
        }
        else
        {
            i.mediana_ = *it;
        }
        i.galutinis_ = 0.4 * i.mediana_ + 0.6 * i.egz_; // Suskaiciuojame studento galutini bala, naudodami pazymiu mediana
    }
}

template <typename Cont>
void failoSkaitymas(ifstream &input, Cont &stud)
{
    long count = 0;
    stringstream ss;
    string eilute;

    if constexpr (is_same<Cont, vector<studentas>>::value)
    {
        stringstream::pos_type position = ss.tellg();

        while(!ss.eof())
        {
            getline(ss, eilute);
            count++;
        }
        ss.clear();
        ss.seekg (position, ss.beg);
        stud.reserve(count);
        count = 0;
    }
    
    getline(input, eilute); // Praleidziame pirmaja failo eilute

    int pazymys;

    while (getline(input, eilute)) // Skaitome duomenis is failo kol ju yra
    {
        istringstream iss(eilute); // Padaliname juos i atskirus string'us, atskirtus tarpais
        
        studentas student(iss);

        stud.push_back(student);
    }
}
template void failoSkaitymas<vector<studentas>>(ifstream&, vector<studentas>&);
template void failoSkaitymas<list<studentas>>(ifstream&, list<studentas>&);
template void failoSkaitymas<deque<studentas>>(ifstream&, deque<studentas>&);

template <typename Cont>
void strategija1(Cont &stud, Cont &vargsiukai, Cont &galvociai)
{
    for (auto &i : stud)
    {
        if (i.getGalutinis() < 5)
        {
            vargsiukai.push_back(i);
        }
        else
        {
            galvociai.push_back(i);
        }
    }
}
template void strategija1<vector<studentas>>(vector<studentas> &stud, vector<studentas> &vargsiukai, vector<studentas> &galvociai);
template void strategija1<list<studentas>>(list<studentas> &stud, list<studentas> &vargsiukai, list<studentas> &galvociai);
template void strategija1<deque<studentas>>(deque<studentas> &stud, deque<studentas> &vargsiukai, deque<studentas> &galvociai);

template <typename Cont>
void strategija2(Cont &stud, Cont &vargsiukai)
{
    typename Cont::iterator it = stud.begin();
    while (it != stud.end())
    {
        if (it->getGalutinis() < 5)
        {
            vargsiukai.push_back(*it);
            it = stud.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
template void strategija2<vector<studentas>>(vector<studentas> &stud, vector<studentas> &vargsiukai);
template void strategija2<list<studentas>>(list<studentas> &stud, list<studentas> &vargsiukai);
template void strategija2<deque<studentas>>(deque<studentas> &stud, deque<studentas> &vargsiukai);

template <typename Cont>
void strategija3(Cont &stud, Cont &vargsiukai)
{
    auto partition_point = stable_partition(stud.begin(), stud.end(), [](const studentas& s) { return s.getGalutinis() < 5; });
    vargsiukai.insert(vargsiukai.end(), stud.begin(), partition_point);
    stud.erase(stud.begin(), partition_point);
}
template void strategija3<vector<studentas>>(vector<studentas> &stud, vector<studentas> &vargsiukai);
template void strategija3<list<studentas>>(list<studentas> &stud, list<studentas> &vargsiukai);
template void strategija3<deque<studentas>>(deque<studentas> &stud, deque<studentas> &vargsiukai);

template <typename Cont>
void rikiuotiDidejant(Cont &container)
{
    if constexpr (is_same<Cont, list<studentas>>::value)
    {
        container.sort(palygintiDidejant);
    }
    else
    {
        sort(container.begin(), container.end(), palygintiDidejant);
    }
}
template void rikiuotiDidejant<vector<studentas>>(vector<studentas> &container);
template void rikiuotiDidejant<list<studentas>>(list<studentas> &container);
template void rikiuotiDidejant<deque<studentas>>(deque<studentas> &container);

template <typename Cont>
void rikiuotiMazejant(Cont &container)
{
    if constexpr (is_same<Cont, list<studentas>>::value)
    {
        container.sort(palygintiMazejant);
    }
    else
    {
        sort(container.begin(), container.end(), palygintiMazejant);
    }
}
template void rikiuotiMazejant<vector<studentas>>(vector<studentas> &container);
template void rikiuotiMazejant<list<studentas>>(list<studentas> &container);
template void rikiuotiMazejant<deque<studentas>>(deque<studentas> &container);