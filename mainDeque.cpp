#include "funkcijos.h"
#include "strukturosDeque.h"

int main()
{
    deque<studentas> stud; // Studentu strukturu konteineris
    deque<studentas> vargsiukai; // Konteineris studentu, kuriu galutinis balas yra zemesnis negu 5
    deque<studentas> galvociai; // Konteineris studentu, kuriu galutinis balas yra lygus arba didesnis uz 5
    string skaiciavimoBudas, eilute; // Kintamasis, kuriame saugomas vartotojo pasirinkimas, kaip skaiciuoti galutini bala, naudojant vidurki ar mediana
    duration<double> failoGeneravimas, nuskaitymas, skirstymas, rusiavimas, isvedimas, bendraTrukme, visuTestuTrukme(0);
    int tarpai;
    bool teisingasIvedimas;
    int i = 0, j, parinktis, studentuKiekis, k, l, papildymas, isvedimasFaile, rikiavimas, studKiekis = 1000, pazKiekis, failuKiekis = 1, strategija;
    char testiPrograma;
    ifstream input;

    srand(time(0));

    do // Prasome studento ivesti skaiciu, nuo kurio priklausys, kaip bus vykdoma programa
    {
        try
        {
            cout << "Pasirinkite, kaip norite vykdyti programa\n1 - Viska vesti ranka\n2 - Generuoti pazymius atsitiktinai\n3 - Generuoti pazymius ir studentu vardus, pavardes atsitiktinai\n4 - Baigti darba\n5 - Skaityti duomenis is failo\n"; 
            
            if (!(cin >> parinktis))
            {
                throw runtime_error("Klaidingi duomenys. Iveskite kazkuri is skaiciu nuo 1 iki 6 imtinai.");
            }

            teisingasIvedimas = (parinktis >= 1 && parinktis <= 6 && cin.peek() == '\n');

            if (!teisingasIvedimas)
            {
                throw runtime_error("Klaidingi duomenys. Iveskite kazkuri is skaiciu nuo 1 iki 6 imtinai.");
            }
        }
        catch (const exception& e)
        {
            cerr << "Klaida: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
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
            try // Jei vartotojas iveda ne skaiciu arba skaiciu, nepatenkanti i reikiama intervala, pranesame apie klaida
            {
                cout << "Iveskite studentu kieki (nuo 1 iki 10 imtinai): ";

                if (!(cin >> studentuKiekis))
                {
                    throw runtime_error("Klaidingi duomenys. Iveskite sveikaji skaiciu nuo 1 iki 10 imtinai.");
                }

                teisingasIvedimas = (studentuKiekis >= 1 && studentuKiekis <= 10 && cin.peek() == '\n');

                if (!teisingasIvedimas)
                {
                    throw runtime_error("Klaidingi duomenys. Iveskite sveikaji skaiciu nuo 1 iki 10 imtinai.");
                }
            }
            catch (const exception& e)
            {
                cerr << "Klaida: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        } while (!teisingasIvedimas);
    
    }

    do
    {
        try
        {
            cout << "Ka norite naudoti galutinio balo skaiciavimui, pazymiu vidurki ar mediana? (Irasykite \'V\' arba \'M\') "; // Vartotojo prasome ivesti vidurkio skaiciavimo buda tol, kol jis ives reikiama simboli

            if (!(cin >> skaiciavimoBudas))
            {
                throw runtime_error("Klaidingi duomenys. Iveskite V arba M.");
            }

            skaiciavimoBudas = didziosios(skaiciavimoBudas); // Ivestos raides pakeiciamos i didziasias, kad reiktu maziau tikrinti

            teisingasIvedimas = ((skaiciavimoBudas == "V" || skaiciavimoBudas == "M") && cin.peek() == '\n');

            if (!teisingasIvedimas) // Tikriname, ar vartotojas ivede viena is dvieju galimu ivesti raidziu be jokiu papildomu simboliu, jei ne, tuomet pranesame vartotojui apie klaida
            {
                throw runtime_error("Klaidingi duomenys. Iveskite V arba M.");
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

    do // Klausiame vartotojo, kokia tvarka jis nori isrikiuoti studentus rezultatuose
    {
        try
        {
            cout << "Jei norite studentus isrikiuoti pagal galutini bala didejimo tvarka, iveskite \"1\", jei mazejimo, iveskite \"0\": ";

            if (!(cin >> rikiavimas) && (rikiavimas != 1 || rikiavimas != 0 || cin.peek() != '\n'))
            {
                throw runtime_error("Klaidingi duomenys. Iveskite \"1\" arba \"0\".");
            }

            teisingasIvedimas = ((rikiavimas == 1 || rikiavimas == 0) && cin.peek() == '\n');

            if (!teisingasIvedimas)
            {
                throw runtime_error("Klaidingi duomenys. Iveskite \"1\" arba \"0\".");
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

    if (parinktis == 5)
    {
        do // Klausiame vartotojo, kiek failu jis nori testuoti
        {
            try
            {
                cout << "Kiek failu norite skaityti? (Iveskite skaiciu nuo 1 iki 5 imtinai): ";

                if (!(cin >> failuKiekis) && (failuKiekis < 1 || failuKiekis > 5 || cin.peek() != '\n'))
                {
                    throw runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 5 imtinai.");
                }

                teisingasIvedimas = ((failuKiekis > 0 && failuKiekis < 6) && cin.peek() == '\n');

                if (!teisingasIvedimas)
                {
                    throw runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 5 imtinai.");
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

        do // Klausiame vartotojo, kuria rusiavimo strategija jis nori naudoti
        {
            try
            {
                cout << "Kuria strategija norite naudoti studentu rusiavimui i dvi grupes? (Iveskite skaiciu nuo 1 iki 3 imtinai): ";

                if (!(cin >> strategija) && (strategija < 1 || strategija > 3 || cin.peek() != '\n'))
                {
                    throw runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 3 imtinai.");
                }

                teisingasIvedimas = ((strategija > 0 && strategija < 4) && cin.peek() == '\n');

                if (!teisingasIvedimas)
                {
                    throw runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 3 imtinai.");
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
    }

    for (int q = 0; q < failuKiekis; q++)
    {
        visuTestuTrukme = chrono::seconds(0);

        for (int z = 0; z < 3; z++)
        {
            if (parinktis == 5) // Jei vartotojas nori nuskaityti duomenis is sugeneruoto failo, atidarome duomenu faila
            {
                string failoVardas = "sugeneruoti" + to_string(studKiekis) + ".txt";
                        
                input.open(failoVardas);

                try
                {
                    if (!input)
                    {
                        throw runtime_error("Failas neegzistuoja.");
                    }
                }
                catch(const exception& e)
                {
                    cerr << "Klaida: " << e.what() << endl;
                    exit(1);
                }
            }

            if (parinktis != 5)
            {
                do // Klausiame vartotojo, ar jis nori rezultatus irasyti i faila, ar isvesti i ekrana
                {
                    try
                    {
                        cout << "Jei norite rezultatus irasyti i faila, iveskite \"1\", jei norite isvesti juos i ekrana, iveskite \"0\": ";

                        if (!(cin >> isvedimasFaile) && (isvedimasFaile != 1 || isvedimasFaile != 0 || cin.peek() != '\n'))
                        {
                            throw runtime_error("Klaidingi duomenys. Iveskite \"1\" arba \"0\".");
                        }

                        teisingasIvedimas = ((isvedimasFaile == 1 || isvedimasFaile == 0) && cin.peek() == '\n');

                        if (!teisingasIvedimas)
                        {
                            throw runtime_error("Klaidingi duomenys. Iveskite \"1\" arba \"0\".");
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
            }

            l = 0;
            papildymas = 0;

            while (true)
            {
                studentuKiekis += papildymas; // Prie esamo studentu kiekio pridedame vartotojo norima papildymo kieki
                studentas naujasStudentas; // Sukuriame viena studento strukturos kintamaji, kuri pildysime, o veliau pridesime i studentu vektoriu

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
                                try
                                {
                                    cout << "Iveskite studento varda: "; // Prasome vartotojo ivesti kiekvieno studento varda tol, kol tas vardas yra vienas zodis, sudarytas tik is raidziu
                                    
                                    if (!(cin >> naujasStudentas.vardas))
                                    {
                                        throw runtime_error("Klaidingi duomenys. Vardas turi buti vienas zodis, sudarytas tik is raidziu (jei studentas turi du vardus, iveskite tik viena is ju).");
                                    }

                                    tarpai = tarpuSkaicius(naujasStudentas.vardas); // Randame ivesties tarpu skaiciu

                                    teisingasIvedimas = (tarpai == 0 && tikRaides(naujasStudentas.vardas) && cin.peek() == '\n');

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
                                    
                                    if (!(cin >> naujasStudentas.pavarde))
                                    {
                                        throw runtime_error("Klaidingi duomenys. Pavarde turi buti vienas zodis, sudarytas tik is raidziu.");
                                    }

                                    tarpai = tarpuSkaicius(naujasStudentas.pavarde); // Randame ivesties tarpu skaiciu

                                    teisingasIvedimas = (tarpai == 0 && tikRaides(naujasStudentas.pavarde) && cin.peek() == '\n');

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

                            naujasStudentas.vardas = didziosios(naujasStudentas.vardas); // Kiekviena vardo raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis
                                    
                            naujasStudentas.pavarde = didziosios(naujasStudentas.pavarde); // Kiekviena pavardes raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis
                        }

                        if (parinktis == 1)
                        {
                            do
                            {
                                try // Klausiame vartotojo, kiek pazymiu jis nori ivesti dabartiniam studentui
                                {
                                    cout << "Kiek pazymiu norite ivesti siam studentui? (Irasykite skaiciu nuo 1 iki 10 imtinai): ";

                                    if (!(cin >> pazymiuKiekis))
                                    {
                                        throw runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 10 imtinai.");
                                    }

                                    teisingasIvedimas = (pazymiuKiekis >= 1 && pazymiuKiekis <= 10 && cin.peek() == '\n');

                                    if (!teisingasIvedimas)
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

                            k = 0;
                            papildymas = 0;
                            
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
                                            cout << "Iveskite " << i + 1 << "-o studento " << j + 1 << "-aji pazymi: ";
                    
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
                                                    naujasStudentas.nd.push_back(pazymys); // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji i atitinkamo studento pazymiu masyva
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
                                    cout << "Iveskite " << i + 1 << "-o studento egzamino pazymi: ";
                                    
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
                                            naujasStudentas.egz = pazymys; // Jei skaicius yra tarp 1 ir 10 imtinai, priskiriame ji kaip atitinkamo studento egzamino pazymi
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

                        if (parinktis == 2) // Jeigu parinktis yra 2, tuomet generuojame pazymius
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

                        if (parinktis == 3) // Jei parinktis yra 3 tuomet generuojame vardus, pavardes ir pazymius
                        {
                                naujasStudentas.vardas = generuotiVarda(i); // Sugeneruota varda priskiriame naujam studentui
                                naujasStudentas.pavarde = generuotiPavarde(i); // Sugeneruota pavarde priskiriame naujam studentui

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

                        stud.push_back(naujasStudentas); // Uzpildzius studento duomenis pridedame ji i studentu vektoriaus gala
                        naujasStudentas.nd.clear(); // Isvalome dabartinio studento pazymiu vektorius
                        l = i + 1;
                    }
            
                    do
                    {
                        try
                        {
                            cout << "Jei norite daugiau studentu, iveskite papildomu studentu kieki (Irasykite skaiciu nuo 1 iki 10 imtinai), jei ne, iveskite \"0\" (nuli) ir spauskite \"Enter\": "; // Klausiame, ar vartotojas nori prideti daugiau pazymiu i vektoriu
                                        
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
                else if (parinktis == 5)
                {
                    auto start = high_resolution_clock::now();

                    getline(input, eilute); // Praleidziame pirmaja failo eilute

                    int pazymys;

                    while (getline(input, eilute)) // Skaitome duomenis is failo kol ju yra
                    {
                        istringstream iss(eilute); // Padaliname juos i atskirus string'us, atskirtus tarpais
                        studentas student;

                        iss >> student.vardas >> student.pavarde;

                        while(iss >> pazymys)
                        {
                            student.nd.push_back(pazymys);
                        }

                        student.egz = student.nd.back();
                        student.nd.pop_back();

                        stud.push_back(student);
                    }
                    auto end = high_resolution_clock::now();
                    nuskaitymas = end - start;
                }
                if (parinktis == 5) // Jei vartotojas rinkosi nuskaityti duomenis is failo, cia nuskaitymas ir baigiasi, nes prideti studentu neimanoma
                {
                    break;
                }
            }

            input.close(); // Uzdarome duomenu faila

            for(auto &i : stud) // Skaiciuojame kiekvieno studento vidurki, mediana, o paskui ir galutinius balus 
            {
                if (skaiciavimoBudas == "V")
                {
                    i.vidurkis = accumulate(i.nd.begin(), i.nd.end(), 0.0) / i.nd.size();
                    i.galutinis = 0.4 * i.vidurkis + 0.6 * i.egz; // Suskaiciuojame studento galutini bala, naudodami pazymiu vidurki
                }
                else
                {
                    auto it = i.nd.begin();
                    advance(it, i.nd.size() / 2); // advance the iterator to the middle of the list

                    if (i.nd.size() % 2 == 0)
                    {
                        int a = *it;
                        --it;
                        int b = *it;
                        i.mediana = (a + b) / 2.0;
                    }
                    else
                    {
                        i.mediana = *it;
                    }
                    i.galutinis = 0.4 * i.mediana + 0.6 * i.egz; // Suskaiciuojame studento galutini bala, naudodami pazymiu mediana
                }
            }
            
            if (parinktis == 5)
            {
                if (strategija == 1)
                {
                    auto start = high_resolution_clock::now();

                    for (auto &i : stud)
                    {
                        if (i.galutinis < 5)
                        {
                            vargsiukai.push_back(i);
                        }
                        else
                        {
                            galvociai.push_back(i);
                        }
                    }

                    auto end = high_resolution_clock::now();
                    skirstymas = end - start;
                }
                else if (strategija == 2)
                {
                    auto start = high_resolution_clock::now();

                    deque<studentas>::iterator it = stud.begin();
                    while (it != stud.end())
                    {
                        if (it->galutinis < 5)
                        {
                            vargsiukai.push_back(*it);
                            it = stud.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }

                    auto end = high_resolution_clock::now();
                    skirstymas = end - start;
                }
                else
                {
                    auto start = high_resolution_clock::now();

                    auto partition_point = stable_partition(stud.begin(), stud.end(), [](const studentas& s) { return s.galutinis < 5; });
                    vargsiukai.insert(vargsiukai.end(), stud.begin(), partition_point);
                    stud.erase(stud.begin(), partition_point);

                    auto end = high_resolution_clock::now();
                    skirstymas = end - start;
                }
            }

            // Priklausomai nuo to, kaip studentus isrikiuoti norejo vartotojas, iskvieciame tam skirtas funkcijas
            if (rikiavimas == 1)
            {
                auto start = high_resolution_clock::now();

                sort(stud.begin(), stud.end(), [] (const studentas& a, const studentas& b)
                {
                    return a.galutinis < b.galutinis;
                });

                if (parinktis == 5)
                {
                    sort(vargsiukai.begin(), vargsiukai.end(), [] (const studentas& a, const studentas& b)
                    {
                        return a.galutinis < b.galutinis;
                    });
                }

                auto end = high_resolution_clock::now();
                rusiavimas = end - start;
            }
            else
            {
                auto start = high_resolution_clock::now();

                sort(stud.begin(), stud.end(), [] (const studentas& a, const studentas& b)
                {
                    return a.galutinis > b.galutinis;
                });
                
                if (parinktis == 5)
                {
                    sort(vargsiukai.begin(), vargsiukai.end(), [] (const studentas& a, const studentas& b)
                    {
                        return a.galutinis > b.galutinis;
                    });
                }

                auto end = high_resolution_clock::now();
                rusiavimas = end - start;
            }

            if (isvedimasFaile == 1)
            {
                ofstream output;
                output.open("output.txt");

                output << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl; // Tvarkingai isvedame antrastine eilute
                output << left << setw(80) << setfill('-') << "-" << endl; // Antrastinei eilutei atskirti naudojame is punktyrines linijos sudaryta antraja eilute
                output << setfill(' ');
                
                if (skaiciavimoBudas == "V")
                {    
                    for(auto &i : stud)
                    {
                        output << left << setw(20) << i.vardas << setw(20) << i.pavarde << setw(20) << fixed << setprecision(2) << i.galutinis << setw(20) << "-.--" << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
                    }
                }
                else
                {
                    for(auto &i : stud)
                    {
                        output << left << setw(20) << i.vardas << setw(20) << i.pavarde << setw(20) << "-.--" << setw(20) << fixed << setprecision(2) << i.galutinis << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
                    }
                }

                output.close();
            }
            else if (parinktis != 5)
            {
                cout << endl;
                cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl; // Tvarkingai isvedame antrastine eilute
                cout << left << setw(80) << setfill('-') << "-" << endl; // Antrastinei eilutei atskirti naudojame is punktyrines linijos sudaryta antraja eilute
                cout << setfill(' ');

                if (skaiciavimoBudas == "V")
                {    
                    for(auto &i : stud)
                    {
                        cout << left << setw(20) << i.vardas << setw(20) << i.pavarde << setw(20) << fixed << setprecision(2) << i.galutinis << setw(20) << "-.--" << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
                    }
                }
                else
                {
                    for(auto &i : stud)
                    {
                        cout << left << setw(20) << i.vardas << setw(20) << i.pavarde << setw(20) << "-.--" << setw(20) << fixed << setprecision(2) << i.galutinis << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
                    }
                }
            }
            if (parinktis == 5)
            {
                auto start = high_resolution_clock::now();

                string failoVardas1 = "vargsiukai" + to_string(studKiekis) + ".txt";
                string failoVardas2 = "galvociai" + to_string(studKiekis) + ".txt";

                ofstream vargsai(failoVardas1);
                ofstream galvoti(failoVardas2);

                vargsai << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl; // Tvarkingai isvedame antrastine eilute
                vargsai << left << setw(80) << setfill('-') << "-" << endl; // Antrastinei eilutei atskirti naudojame is punktyrines linijos sudaryta antraja eilute
                vargsai << setfill(' ');

                galvoti << left << setw(20) << "Vardas" << setw(20) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl; // Tvarkingai isvedame antrastine eilute
                galvoti << left << setw(80) << setfill('-') << "-" << endl; // Antrastinei eilutei atskirti naudojame is punktyrines linijos sudaryta antraja eilute
                galvoti << setfill(' ');

                if (skaiciavimoBudas == "V")
                {    
                    for(auto &i : vargsiukai)
                    {
                        vargsai << left << setw(20) << i.vardas << setw(20) << i.pavarde << setw(20) << fixed << setprecision(2) << i.galutinis << setw(20) << "-.--" << endl;
                    }

                    for(auto &i : stud)
                    {
                        galvoti << left << setw(20) << i.vardas << setw(20) << i.pavarde << setw(20) << fixed << setprecision(2) << i.galutinis << setw(20) << "-.--" << endl;
                    }
                }
                else
                {
                    for(auto &i : vargsiukai)
                    {
                        vargsai << left << setw(20) << i.vardas << setw(20) << i.pavarde << setw(20) << "-.--" << setw(20) << fixed << setprecision(2) << i.galutinis << endl;
                    }

                    for(auto &i : stud)
                    {
                        galvoti << left << setw(20) << i.vardas << setw(20) << i.pavarde << setw(20) << "-.--" << setw(20) << fixed << setprecision(2) << i.galutinis << endl;
                    }
                }

                auto end = high_resolution_clock::now();
                isvedimas = end - start;
            }

            if (parinktis == 5)
            {
                bendraTrukme =  nuskaitymas + skirstymas + rusiavimas + isvedimas; // Apskaiciuojame programos veikimo laika ir ji atspausdiname i ekrana
                visuTestuTrukme += bendraTrukme;
                
                if (z == 0)
                {
                    cout << studKiekis << " irasu failo nuskaitymo trukme: " << nuskaitymas.count() << endl;
                    cout << studKiekis << " irasu rikiavimo trukme: " << rusiavimas.count() << endl;
                    cout << studKiekis << " irasu skirstymo i dvi grupes trukme: " << skirstymas.count() << endl;
                    cout << studKiekis << " irasu testo trukme sekundemis: " << bendraTrukme.count() << endl;
                }

                for (auto &i : stud)
                {
                    i.nd.clear();
                }
                stud.clear();

                for (auto &i : vargsiukai)
                {
                    i.nd.clear();
                }
                vargsiukai.clear();
            }
            else
            {
                break;
            }
        }

        if (parinktis == 5)
        {
            cout << "3 testu laiku vidurkis su " << studKiekis << " studentu failu: " << visuTestuTrukme.count() / 3.0 << endl;
            cout << endl;
        }
        else
        {
            break;
        }

        studKiekis *= 10;
    }

    return 0;
}