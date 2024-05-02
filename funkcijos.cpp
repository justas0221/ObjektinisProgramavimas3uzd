#include "funkcijos.h"

string skaiciavimoBudas;
int pazymiuKiekis = 3, parinktis, papildymas, k, i, randomPazymiuKiekis;

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

// Konstruktorius su nuoroda i istream objekta, kaip parametru
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

// Studento klases funkcija, skirta generuoti vienam namu darbu pazymiui ir ji ikelti i vektoriu
void studentas::generuotiNdPazymi()
{
    int skaicius = generuotiPazymi();

    nd_.push_back(skaicius);
}

// Studento klases funcija, skirta generuoti egzamino pazymi
void studentas::generuotiEgzPazymi()
{
    int skaicius = generuotiPazymi();

    egz_ = (skaicius);
}

// Studento klases funkcija, skirta gauti paskutini namu darbu pazymi
int studentas::gautiPaskutiniPazymi()
{
    if (!nd_.empty())
    {
        return nd_.back();
    }
    else
    {
        return -1;
    }
}


// Funkcija, sugeneruojanti atsitiktini skaiciu nuo 1 iki 10 imtinai
int generuotiPazymi()
{
    int skaicius = rand() % 10 + 1;

    return skaicius;
}

// Funkcija, skirta lyginti du studentus pagal galutini pazymi ir rikiuoti juos mazejimo tvarka
bool palygintiMazejant(const studentas& a, const studentas& b)
{
    return a.galutinis_ > b.galutinis_;
}

// Funkcija, skirta lyginti du studentus pagal galutini pazymi ir rikiuoti juos didejimo tvarka
bool palygintiDidejant(const studentas& a, const studentas& b)
{
    return a.galutinis_ < b.galutinis_;
}

// Funkcija, skirta generuoti duomenu faila, kuri sudaro studentu duomenys: vardas, pavarde, namu darbu pazymiai ir egzamino pazymys
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

// Funkcija, skirta studento galutiniam balui skaiciuoti
void studentas::baloSkaiciavimas(string skaiciavimoBudas)
{
    if (skaiciavimoBudas == "V")
    {
        vidurkis_ = accumulate(nd_.begin(), nd_.end(), 0.0) / nd_.size();
        galutinis_ = 0.4 * vidurkis_ + 0.6 * egz_; // Suskaiciuojame studento galutini bala, naudodami pazymiu vidurki
    }
    else
    {
        auto it = nd_.begin();
        advance(it, nd_.size() / 2); // advance the iterator to the middle of the list

        if (nd_.size() % 2 == 0)
        {
            int a = *it;
            --it;
            int b = *it;
            mediana_ = (a + b) / 2.0;
        }
        else
        {
            mediana_ = *it;
        }
        galutinis_ = 0.4 * mediana_ + 0.6 * egz_; // Suskaiciuojame studento galutini bala, naudodami pazymiu mediana
    }
}

// Funkcijos, skirtos nuskaityti duomenu faila, sablonas
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

// Funkcijos, skirtos surusiuoti studentus i du atskirus konteinerius, sablonas
template <typename Cont>
void strategija3(Cont &stud, Cont &vargsiukai)
{
    auto partition_point = stable_partition(stud.begin(), stud.end(), [](const studentas& s) { return s.galutinis() < 5; });
    vargsiukai.insert(vargsiukai.end(), stud.begin(), partition_point);
    stud.erase(stud.begin(), partition_point);
}
template void strategija3<vector<studentas>>(vector<studentas> &stud, vector<studentas> &vargsiukai);
template void strategija3<list<studentas>>(list<studentas> &stud, list<studentas> &vargsiukai);
template void strategija3<deque<studentas>>(deque<studentas> &stud, deque<studentas> &vargsiukai);

// Funkcijos, skirtos studentus isrikiuoti didejimo tvarka pagal galutini bala, sablonas
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

// Funkcijos, skirtos studentus isrikiuoti mazejimo tvarka pagal galutini bala, sablonas
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

// Funkcija, atspausdinanti antraste i duomenu isvedimo faila
void printHeader(ostream& out)
{
    out << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    out << left << setw(80) << setfill('-') << "-" << endl;
    out << setfill(' ');
}

// Operatoriaus "<<" perkrovimas
ostream& operator<<(ostream& out, const studentas& a)
{
    out << left << setw(20) << a.vardas() << setw(20) << a.pavarde();
    
    if (skaiciavimoBudas == "V")
    {
        out << setw(20) << fixed << setprecision(2) << a.galutinis() << setw(20) << "-.--";
    }
    else
    {
        out << setw(20) << "-.--" << setw(20) << fixed << setprecision(2) << a.galutinis();
    }
    
    return out;
}

// Operatoriaus ">>" perkrovimas
istream& operator>>(istream& in, studentas& s)
{
    if (parinktis == 1 || parinktis == 6)
    {
        bool teisingasIvedimas;
        int tarpai;
        string vardas, pavarde;
        i++;

        do
        {
            try
            {
                cout << "Iveskite studento varda: "; // Prasome vartotojo ivesti kiekvieno studento varda tol, kol tas vardas yra vienas zodis, sudarytas tik is raidziu

                if (!(in >> s.vardas_))
                {
                    throw runtime_error("Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju).");
                }

                tarpai = tarpuSkaicius(s.vardas_); // Randame ivesties tarpu skaiciu

                teisingasIvedimas = (tarpai == 0 && tikRaides(s.vardas_) && in.peek() == '\n');

                if (!teisingasIvedimas) // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                {
                    throw runtime_error("Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju).");
                }
            }
            catch(const exception& e)
            {
                cerr << "Klaida: " << e.what() << endl;
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas
        do
        {
            try
            {
                cout << "Iveskite studento pavarde: "; // Prasome vartotojo ivesti kiekvieno studento pavarde tol, kol ta pavarde yra vienas zodis, sudarytas tik is raidziu

                if (!(in >> s.pavarde_))
                {
                    throw runtime_error("Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu.");
                }

                tarpai = tarpuSkaicius(s.pavarde_); // Randame ivesties tarpu skaiciu

                teisingasIvedimas = (tarpai == 0 && tikRaides(s.pavarde_) && in.peek() == '\n');

                if (!teisingasIvedimas) // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                {
                    throw runtime_error("Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu.");
                }
            }
            catch(const exception& e)
            {
                cerr << "Klaida: " << e.what() << endl;
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas

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
                        cout << "Iveskite " << i << "-o studento " << j + 1 << "-aji pazymi: ";
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
                                s.nd_.push_back(pazymys); // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji i atitinkamo studento pazymiu masyva
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
                cout << "Iveskite " << i << "-o studento egzamino pazymi: ";
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
                        s.egz_ = pazymys; // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji kaip atitinkamo studento egzamino pazymi
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
    else if (parinktis == 2)
    {
        int pazymys, tarpai;
        string vardas, pavarde;
        bool teisingasIvedimas;
        i++;

        do
        {
            try
            {
                cout << "Iveskite studento varda: "; // Prasome vartotojo ivesti kiekvieno studento varda tol, kol tas vardas yra vienas zodis, sudarytas tik is raidziu

                if (!(in >> s.vardas_))
                {
                    throw runtime_error("Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju).");
                }

                tarpai = tarpuSkaicius(s.vardas_); // Randame ivesties tarpu skaiciu

                teisingasIvedimas = (tarpai == 0 && tikRaides(s.vardas_) && in.peek() == '\n');

                if (!teisingasIvedimas) // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                {
                    throw runtime_error("Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju).");
                }
            }
            catch(const exception& e)
            {
                cerr << "Klaida: " << e.what() << endl;
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas
        do
        {
            try
            {
                cout << "Iveskite studento pavarde: "; // Prasome vartotojo ivesti kiekvieno studento pavarde tol, kol ta pavarde yra vienas zodis, sudarytas tik is raidziu

                if (!(in >> s.pavarde_))
                {
                    throw runtime_error("Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu.");
                }

                tarpai = tarpuSkaicius(s.pavarde_); // Randame ivesties tarpu skaiciu

                teisingasIvedimas = (tarpai == 0 && tikRaides(s.pavarde_) && in.peek() == '\n');

                if (!teisingasIvedimas) // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                {
                    throw runtime_error("Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu.");
                }
            }
            catch(const exception& e)
            {
                cerr << "Klaida: " << e.what() << endl;
                in.clear();
                in.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas

        for (int j = 0; j < randomPazymiuKiekis; j++)
        {
            s.generuotiNdPazymi();
            pazymys = s.gautiPaskutiniPazymi();
                
            cout << "Sugeneruotas " << i << "-o studento " << j + 1 << "-aji pazymys: " << pazymys << endl;
        }

        s.generuotiEgzPazymi();
        pazymys = s.getEgz();

        cout << "Sugeneruotas " << i << "-o studento egzamino pazymys: " << pazymys << endl;
    }
    else if (parinktis == 3)
    {
        int pazymys;

        s.generuotiVarda(i); // Sugeneruota varda priskiriame naujam studentui
        s.generuotiPavarde(i); // Sugeneruota pavarde priskiriame naujam studentui

        cout << "Sugeneruoti " << i + 1 << "-o studento vardas ir pavarde: " << s.vardas() << " " << s.pavarde() << endl;
        for (int j = 0; j < randomPazymiuKiekis; j++)
        {
            s.generuotiNdPazymi(); // Sugeneruota pazymi pridedame i vektoriu

            pazymys = s.gautiPaskutiniPazymi();

            cout << "Sugeneruotas " << i + 1 << "-o studento " << j + 1 << "-asis pazymys: " << pazymys << endl;
        }
        
        s.generuotiEgzPazymi();

        pazymys = s.getEgz();

        cout << "Sugeneruotas " << i + 1 << "-o studento egzamino pazymys: " << pazymys << endl;
    }
    return in;
}

// Funkcija, skirta testuoti Rule of Five metodus
void testas(studentas& s)
{
    cout << "Default konstruktoriaus ir << operatoriaus testavimas:" << endl; // Testuojamas default konstruktorius ir << operatorius
    cout << endl;
    cout << s << endl;
    cout << endl;

    cout << ">> operatoriaus testavimas:" << endl; // Testuojamas ir >> operatorius
    cout << endl;
    cin.ignore();
    cin >> s;
    s.baloSkaiciavimas(skaiciavimoBudas);
    cout << s << endl;
    cout << endl;

    cout << "Copy konstruktoriaus testavimas:" << endl; // Testuojamas Copy konstruktorius
    studentas z(s);
    cout << endl;
    cout << s << endl;
    cout << z << endl;
    cout << endl;

    cout << "Copy-assignment operatoriaus testavimas:" << endl; // Testuojamas Copy-assignment operatorius
    cout << endl;
    studentas x;
    x = s;
    cout << s << endl;
    cout << x << endl;
    cout << endl;

    cout << "Move konstruktoriaus testavimas:" << endl; // Testuojamas Move konstruktorius
    studentas y = move(s);
    cout << endl;
    cout << s << endl;
    cout << y << endl;
    cout << endl;

    cout << "Move-assignment operatoriaus testavimas:" << endl; // Testuojamas Move-assignment operatorius
    studentas w;
    w = move(y);
    cout << endl;
    cout << y << endl;
    cout << w << endl;
    cout << endl;

    cout << "Destruktoriaus testavimas:" << endl; // Testuojamas destruktorius
    w.~studentas();
    cout << endl;

    exit(0);
}