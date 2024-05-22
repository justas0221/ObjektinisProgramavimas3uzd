#include "funkcijos.h"
#include "vector.h"

std::string skaiciavimoBudas;
int pazymiuKiekis = 3, parinktis, papildymas, k, i, randomPazymiuKiekis;

// Funkcija, tikrinanti, ar vardas bei pavarde yra sudaryti tik is raidziu
bool tikRaides(std::string ivedimas)
{
    for(char c : ivedimas) // Keliaujame per kiekviena ivesto zodzio simboli ir tikriname ar tas simbolis yra raide
    {
        if(!isalpha(c))
            return false;
    }
    return true;
}

// Funkcija, pakeicianti visas gauto teksto raides i didziasias
std::string didziosios(std::string &tekstas)
{
    for(char &c : tekstas) // Keliaujame per kiekviena ivesto teksto raide ir paverciame ji i didziaja raide
    {
        c = toupper(c);
    }
    return tekstas;
}

// Funkcija, apskaiciuojanti tarpu skaiciu eiluteje
int tarpuSkaicius(std::string ivedimas)
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
studentas::studentas(std::istream& is)
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
void generuotiFaila(int studKiekis, int pazKiekis, std::string failoVardas)
{
    std::ofstream naujas(failoVardas);
    std::stringstream eilute;

    eilute << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde"; // Isvedame antrastine eilute
    for (int i = 0; i < pazKiekis; i++)
    {
        std::string nd = "ND" + std::to_string(i + 1);

        eilute << std::setw(10) << nd;
    }
    eilute << std::setw(10) << "Egz." << std::endl;

    for (int i = 0; i < studKiekis; i++)
    {
        std::string vardas = "Vardas" + std::to_string(i + 1);
        std::string pavarde = "Pavarde" + std::to_string(i + 1);

        eilute << std::left << std::setw(20) << vardas << std::setw(20) << pavarde; // Isvedame kiekvieno studento varda ir pavarde
        for (int j = 0; j <= pazKiekis; j++)
        {
            eilute << std::setw(10) << rand() % 10;
        }
        eilute << std::endl;

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
void studentas::baloSkaiciavimas(std::string skaiciavimoBudas)
{
    if (skaiciavimoBudas == "V")
    {
        vidurkis_ = std::accumulate(nd_.begin(), nd_.end(), 0.0) / nd_.size();
        galutinis_ = 0.4 * vidurkis_ + 0.6 * egz_; // Suskaiciuojame studento galutini bala, naudodami pazymiu vidurki
    }
    else
    {
        auto it = nd_.begin();
        std::advance(it, nd_.size() / 2); // advance the iterator to the middle of the list

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
void failoSkaitymas(std::ifstream &input, Cont &stud)
{
    long count = 0;
    std::stringstream ss;
    std::string eilute;

    if constexpr (std::is_same<Cont, std::Vector<studentas>>::value)
    {
        std::stringstream::pos_type position = ss.tellg();

        while(!ss.eof())
        {
            getline(ss, eilute);
            count++;
        }
        ss.clear();
        ss.seekg(0);
        stud.reserve(count);
        count = 0;
    }
    
    getline(input, eilute); // Praleidziame pirmaja failo eilute

    while (getline(input, eilute)) // Skaitome duomenis is failo kol ju yra
    {
        std::istringstream iss(eilute); // Padaliname juos i atskirus string'us, atskirtus tarpais
        
        studentas student(iss);
        
        stud.push_back(student);
    }
}
template void failoSkaitymas<std::Vector<studentas>>(std::ifstream&, std::Vector<studentas>&);

// Funkcijos, skirtos surusiuoti studentus i du atskirus konteinerius, sablonas
void strategija3(std::Vector<studentas> &stud, std::Vector<studentas> &vargsiukai)
{
    auto partition_point = std::stable_partition(stud.begin(), stud.end(), [](const studentas& s) { return s.galutinis() < 5; });
    vargsiukai.insert(vargsiukai.end(), stud.begin(), partition_point);
    stud.erase(stud.begin(), partition_point);
}

// Funkcijos, skirtos studentus isrikiuoti didejimo tvarka pagal galutini bala, sablonas
void rikiuotiDidejant(std::Vector<studentas> &container)
{
    std::sort(container.begin(), container.end(), palygintiDidejant);
}

// Funkcijos, skirtos studentus isrikiuoti mazejimo tvarka pagal galutini bala, sablonas
void rikiuotiMazejant(std::Vector<studentas> &container)
{
    std::sort(container.begin(), container.end(), palygintiMazejant);
}

// Funkcija, atspausdinanti antraste i duomenu isvedimo faila
void printHeader(std::ostream& out)
{
    out << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde" << std::setw(20) << "Galutinis (Vid.)" << std::setw(20) << "Galutinis (Med.)" << std::endl;
    out << std::left << std::setw(80) << std::setfill('-') << "-" << std::endl;
    out << std::setfill(' ');
}

// Operatoriaus "<<" perkrovimas
std::ostream& operator<<(std::ostream& out, const studentas& a)
{
    out << std::left << std::setw(20) << a.vardas() << std::setw(20) << a.pavarde();
    
    if (skaiciavimoBudas == "V")
    {
        out << std::setw(20) << std::fixed << std::setprecision(2) << a.galutinis() << std::setw(20) << "-.--";
    }
    else
    {
        out << std::setw(20) << "-.--" << std::setw(20) << std::fixed << std::setprecision(2) << a.galutinis();
    }
    
    return out;
}

// Operatoriaus ">>" perkrovimas
std::istream& operator>>(std::istream& in, studentas& s)
{
    if (parinktis == 1 || parinktis == 6)
    {
        bool teisingasIvedimas;
        int tarpai;
        std::string vardas, pavarde;
        i++;

        do
        {
            try
            {
                std::cout << "Iveskite studento varda: "; // Prasome vartotojo ivesti kiekvieno studento varda tol, kol tas vardas yra vienas zodis, sudarytas tik is raidziu

                if (!(in >> s.vardas_))
                {
                    throw std::runtime_error("Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju).");
                }

                tarpai = tarpuSkaicius(s.vardas_); // Randame ivesties tarpu skaiciu

                teisingasIvedimas = (tarpai == 0 && tikRaides(s.vardas_) && in.peek() == '\n');

                if (!teisingasIvedimas) // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                {
                    throw std::runtime_error("Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju).");
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << "Klaida: " << e.what() << std::endl;
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas
        do
        {
            try
            {
                std::cout << "Iveskite studento pavarde: "; // Prasome vartotojo ivesti kiekvieno studento pavarde tol, kol ta pavarde yra vienas zodis, sudarytas tik is raidziu

                if (!(in >> s.pavarde_))
                {
                    throw std::runtime_error("Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu.");
                }

                tarpai = tarpuSkaicius(s.pavarde_); // Randame ivesties tarpu skaiciu

                teisingasIvedimas = (tarpai == 0 && tikRaides(s.pavarde_) && in.peek() == '\n');

                if (!teisingasIvedimas) // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                {
                    throw std::runtime_error("Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu.");
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << "Klaida: " << e.what() << std::endl;
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas

        while (true)
        {
            pazymiuKiekis += papildymas; // Prie esamo pazymiu kiekio pridedame vartotojo parinkta papildymo kieki

            for (int j = k; j < pazymiuKiekis; j++)
            {
                std::string ivedimas;
                
                do
                {
                    try
                    {
                        std::cout << "Iveskite " << i << "-o studento " << j + 1 << "-aji pazymi: ";
                        teisingasIvedimas = false;

                        if (!(std::cin >> ivedimas))
                        {
                            throw std::runtime_error("Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10.");
                        }

                        teisingasIvedimas = ((ivedimas.size() == 1 || (ivedimas.size() == 2 && (ivedimas[0] == '1' && ivedimas[1] == '0'))) && std::cin.peek() == '\n' && isdigit(ivedimas[0]));

                        if (!teisingasIvedimas) // Tikriname, ar vartotojo ivedima sudaro vienas arba du simboliai, jei ji sudaro du simboliai tikriname ar pirmas simbolis - vienetas, o antras - nulis, ir tikriname ar po pirmo skaiciaus iskart eina naujos eilutes simbolis
                        {
                            throw std::runtime_error("Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10.");
                        }
                        else
                        {
                            int pazymys = stoi(ivedimas); // Paverciame ivesta std::string'a i int'a
                            if (pazymys < 1 || pazymys > 10) // Jei tas skaicius nera tarp 1 ir 10 imtinai, pranesame apie klaida
                            {
                                teisingasIvedimas = false;
                                std::cout << "Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10." << std::endl;
                            }
                            else
                            {
                                s.nd_.push_back(pazymys); // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji i atitinkamo studento pazymiu masyva
                            }
                        }
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << "Klaida: " << e.what() << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        continue;
                    }
                } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas yra neteisingas
                
                k = j + 1;
            }

            do
            {
                try
                {
                    std::cout << "Jei norite daugiau pazymiu, iveskite papildomu pazymiu kieki (Irasykite skaiciu nuo 1 iki 10 imtinai), jei ne, iveskite \"0\" (nuli) ir spauskite \"Enter\": "; // Klausiame, ar vartotojas nori prideti daugiau pazymiu i vektoriu
                    teisingasIvedimas = false;

                    if (!(std::cin >> papildymas))
                    {
                        throw std::runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 10 imtinai.");
                    }

                    teisingasIvedimas = (papildymas >= 0 && papildymas <= 10 && std::cin.peek() == '\n');

                    if (papildymas == 0)
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }
                    else if (!teisingasIvedimas)
                    {
                        throw std::runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 10 imtinai.");
                    }
                }
                catch(const std::exception& e)
                {
                    std::cerr << "Klaida: " << e.what() << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
            std::string ivedimas;

            try // Prasome vartotojo ivesti studento pazymius viena po kito
            {
                std::cout << "Iveskite " << i << "-o studento egzamino pazymi: ";
                teisingasIvedimas = false;

                if (!(std::cin >> ivedimas))
                {
                    throw std::runtime_error("Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10.");
                }
                        
                teisingasIvedimas = ((ivedimas.size() == 1 || (ivedimas.size() == 2 && (ivedimas[0] == '1' && ivedimas[1] == '0'))) && std::cin.peek() == '\n' && isdigit(ivedimas[0]));

                if (!teisingasIvedimas) // Tikriname, ar vartotojo ivedima sudaro vienas arba du simboliai, jei ji sudaro du simboliai tikriname ar pirmas simbolis - vienetas, o antras - nulis, ir tikriname ar po pirmo skaiciaus iskart eina naujos eilutes simbolis
                {
                    throw std::runtime_error("Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10.");
                }
                else
                {
                    int pazymys = stoi(ivedimas); // Paverciame ivesta std::string'a i int'a
                    if (pazymys < 1 || pazymys > 10) // Jei tas skaicius nera tarp 1 ir 10 imtinai, pranesame apie klaida
                    {
                        teisingasIvedimas = false;
                        std::cout << "Klaidingi duomenys. Prasome ivesti viena sveikaji skaiciu nuo 1 iki 10." << std::endl;
                    }
                    else
                    {
                        s.egz_ = pazymys; // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji kaip atitinkamo studento egzamino pazymi
                    }
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << "Klaida: " << e.what() << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas yra neteisingas
    }
    else if (parinktis == 2)
    {
        int pazymys, tarpai;
        std::string vardas, pavarde;
        bool teisingasIvedimas;
        i++;

        do
        {
            try
            {
                std::cout << "Iveskite studento varda: "; // Prasome vartotojo ivesti kiekvieno studento varda tol, kol tas vardas yra vienas zodis, sudarytas tik is raidziu

                if (!(in >> s.vardas_))
                {
                    throw std::runtime_error("Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju).");
                }

                tarpai = tarpuSkaicius(s.vardas_); // Randame ivesties tarpu skaiciu

                teisingasIvedimas = (tarpai == 0 && tikRaides(s.vardas_) && in.peek() == '\n');

                if (!teisingasIvedimas) // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                {
                    throw std::runtime_error("Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju).");
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << "Klaida: " << e.what() << std::endl;
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas
        do
        {
            try
            {
                std::cout << "Iveskite studento pavarde: "; // Prasome vartotojo ivesti kiekvieno studento pavarde tol, kol ta pavarde yra vienas zodis, sudarytas tik is raidziu

                if (!(in >> s.pavarde_))
                {
                    throw std::runtime_error("Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu.");
                }

                tarpai = tarpuSkaicius(s.pavarde_); // Randame ivesties tarpu skaiciu

                teisingasIvedimas = (tarpai == 0 && tikRaides(s.pavarde_) && in.peek() == '\n');

                if (!teisingasIvedimas) // Jei tarpu skaicius nera nulis arba vardas sudarytas ne tik is raidziu, arba sekantis po zodzio esantis simbolis nera naujos eilutes simbolis, pranesame apie klaida, laikome ivedima neteisingu
                {
                    throw std::runtime_error("Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu.");
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << "Klaida: " << e.what() << std::endl;
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        } while (!teisingasIvedimas); // Vykdome cikla kol ivedimas neteisingas

        for (int j = 0; j < randomPazymiuKiekis; j++)
        {
            s.generuotiNdPazymi();
            pazymys = s.gautiPaskutiniPazymi();
                
            std::cout << "Sugeneruotas " << i << "-o studento " << j + 1 << "-aji pazymys: " << pazymys << std::endl;
        }

        s.generuotiEgzPazymi();
        pazymys = s.getEgz();

        std::cout << "Sugeneruotas " << i << "-o studento egzamino pazymys: " << pazymys << std::endl;
    }
    else if (parinktis == 3)
    {
        int pazymys;

        s.generuotiVarda(i); // Sugeneruota varda priskiriame naujam studentui
        s.generuotiPavarde(i); // Sugeneruota pavarde priskiriame naujam studentui

        std::cout << "Sugeneruoti " << i + 1 << "-o studento vardas ir pavarde: " << s.vardas() << " " << s.pavarde() << std::endl;
        for (int j = 0; j < randomPazymiuKiekis; j++)
        {
            s.generuotiNdPazymi(); // Sugeneruota pazymi pridedame i vektoriu

            pazymys = s.gautiPaskutiniPazymi();

            std::cout << "Sugeneruotas " << i + 1 << "-o studento " << j + 1 << "-asis pazymys: " << pazymys << std::endl;
        }
        
        s.generuotiEgzPazymi();

        pazymys = s.getEgz();

        std::cout << "Sugeneruotas " << i + 1 << "-o studento egzamino pazymys: " << pazymys << std::endl;
    }
    return in;
}

// Operatoriaus == perkrovimas
bool operator==(const studentas& a, const studentas& b)
{
    return a.getVardas() == b.getVardas() && a.getPavarde() == b.getPavarde() && a.getNd() == b.getNd() && a.getEgz() == b.getEgz();
}

bool operator==(const std::string& a, const std::string& b)
{
    return a == b;
}

// Funkcija, skirta testuoti Rule of Five metodus
void testas(studentas& s)
{
    std::cout << "Default konstruktoriaus ir << operatoriaus testavimas:" << std::endl; // Testuojamas default konstruktorius ir << operatorius
    std::cout << std::endl;
    std::cout << s << std::endl;
    std::cout << std::endl;

    std::cout << ">> operatoriaus testavimas:" << std::endl; // Testuojamas ir >> operatorius
    std::cout << std::endl;
    std::cin.ignore();
    std::cin >> s;
    s.baloSkaiciavimas(skaiciavimoBudas);
    std::cout << s << std::endl;
    std::cout << std::endl;

    std::cout << "Copy konstruktoriaus testavimas:" << std::endl; // Testuojamas Copy konstruktorius
    studentas z(s);
    std::cout << std::endl;
    std::cout << s << std::endl;
    std::cout << z << std::endl;
    std::cout << std::endl;

    std::cout << "Copy-assignment operatoriaus testavimas:" << std::endl; // Testuojamas Copy-assignment operatorius
    std::cout << std::endl;
    studentas x;
    x = s;
    std::cout << s << std::endl;
    std::cout << x << std::endl;
    std::cout << std::endl;

    std::cout << "Move konstruktoriaus testavimas:" << std::endl; // Testuojamas Move konstruktorius
    studentas y = std::move(s);
    std::cout << std::endl;
    std::cout << s << std::endl;
    std::cout << y << std::endl;
    std::cout << std::endl;

    std::cout << "Move-assignment operatoriaus testavimas:" << std::endl; // Testuojamas Move-assignment operatorius
    studentas w;
    w = std::move(y);
    std::cout << std::endl;
    std::cout << y << std::endl;
    std::cout << w << std::endl;
    std::cout << std::endl;

    std::cout << "Destruktoriaus testavimas:" << std::endl; // Testuojamas destruktorius
    w.~studentas();
    std::cout << std::endl;

    exit(0);
}