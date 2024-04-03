#include "funkcijos.h"

int main()
{
    vector<studentas> stud; // Studentu strukturu vektorius
    vector<studentas> vargsiukai; // Vektorius studentu, kuriu galutinis balas yra zemesnis negu 5
    vector<studentas> galvociai; // Vektorius studentu, kuriu galutinis balas yra lygus arba didesnis uz 5
    string eilute; // Kintamasis, kuriame saugomas vartotojo pasirinkimas, kaip skaiciuoti galutini bala, naudojant vidurki ar mediana
    duration<double> failoGeneravimas, nuskaitymas, skirstymas, rusiavimas, isvedimas, bendraTrukme, visuTestuTrukme(0);
    int tarpai;
    bool teisingasIvedimas = false;
    int j, studentuKiekis, l, isvedimasFaile = 0, rikiavimas, studKiekis = 1000, pazKiekis, failuKiekis = 1, strategija;
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
                throw runtime_error("Klaidingi duomenys. Iveskite kazkuri is skaiciu nuo 1 iki 5 imtinai.");
            }

            teisingasIvedimas = (parinktis >= 1 && parinktis <= 5 && cin.peek() == '\n');

            if (!teisingasIvedimas)
            {
                throw runtime_error("Klaidingi duomenys. Iveskite kazkuri is skaiciu nuo 1 iki 5 imtinai.");
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
                teisingasIvedimas = false;

                if (!(cin >> studentuKiekis) && (studentuKiekis < 1 || studentuKiekis > 10 || cin.peek() == '\n'))
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
            teisingasIvedimas = false;

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
            teisingasIvedimas = false;

            if (!(cin >> rikiavimas) || ((rikiavimas != 1 && rikiavimas != 0) || cin.peek() != '\n'))
            {
                throw runtime_error("Klaidingi duomenys. Iveskite \"1\" arba \"0\".");
            }

            teisingasIvedimas = (rikiavimas == 1 || rikiavimas == 0) && cin.peek() == '\n';

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
                teisingasIvedimas = false;

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
                teisingasIvedimas = false;

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
                        teisingasIvedimas = false;

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
                        randomPazymiuKiekis = rand() % 10 + 1;
                        pazymiuKiekis = 0;
                        
                        if (parinktis == 1)
                        {
                            do
                            {
                                try // Klausiame vartotojo, kiek pazymiu jis nori ivesti dabartiniam studentui
                                {
                                    cout << "Kiek pazymiu norite ivesti siam studentui? (Irasykite skaiciu nuo 1 iki 10 imtinai): ";
                                    teisingasIvedimas = false;

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
                            
                            cin >> naujasStudentas;
                            naujasStudentas.didziosiosVardas();
                            naujasStudentas.didziosiosPavarde();
                        }
                        else if (parinktis == 2) // Jeigu parinktis yra 2, tuomet generuojame pazymius
                        {
                            cin >> naujasStudentas;
                            naujasStudentas.didziosiosVardas(); // Kiekviena vardo raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis
                            naujasStudentas.didziosiosPavarde(); // Kiekviena pavardes raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis
                        }
                        else if (parinktis == 3) // Jei parinktis yra 3 tuomet generuojame vardus, pavardes ir pazymius
                        {
                            int pazymys;

                            naujasStudentas.generuotiVarda(i); // Sugeneruota varda priskiriame naujam studentui
                            naujasStudentas.generuotiPavarde(i); // Sugeneruota pavarde priskiriame naujam studentui

                            cout << "Sugeneruoti " << i + 1 << "-o studento vardas ir pavarde: " << naujasStudentas.vardas() << " " << naujasStudentas.pavarde() << endl;
                            for (int j = 0; j < randomPazymiuKiekis; j++)
                            {
                                naujasStudentas.generuotiNdPazymi(); // Sugeneruota pazymi pridedame i vektoriu

                                pazymys = naujasStudentas.gautiPaskutiniPazymi();

                                cout << "Sugeneruotas " << i + 1 << "-o studento " << j + 1 << "-asis pazymys: " << pazymys << endl;
                            }
                            
                            naujasStudentas.generuotiEgzPazymi();

                            pazymys = naujasStudentas.getEgz();

                            cout << "Sugeneruotas " << i + 1 << "-o studento egzamino pazymys: " << pazymys << endl;
                        }

                        stud.push_back(naujasStudentas); // Uzpildzius studento duomenis pridedame ji i studentu vektoriaus gala
                        naujasStudentas.clearNd(); // Isvalome dabartinio studento pazymiu vektorius
                        l = i + 1;
                    }
            
                    do
                    {
                        try
                        {
                            cout << "Jei norite daugiau studentu, iveskite papildomu studentu kieki (Irasykite skaiciu nuo 1 iki 10 imtinai), jei ne, iveskite \"0\" (nuli) ir spauskite \"Enter\": "; // Klausiame, ar vartotojas nori prideti daugiau pazymiu i vektoriu
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
                else if (parinktis == 5)
                {
                    auto start = high_resolution_clock::now();
                    failoSkaitymas(input, stud);
                    auto end = high_resolution_clock::now();
                    nuskaitymas = end - start;
                    break;
                }
            }

            input.close(); // Uzdarome duomenu faila
            
            for(auto &it : stud) // Skaiciuojame kiekvieno studento vidurki, mediana, o paskui ir galutinius balus 
            {
                it.baloSkaiciavimas(it, skaiciavimoBudas);
            }
            
            if (parinktis == 5)
            {
                if (strategija == 1)
                {
                    auto start = high_resolution_clock::now();

                    strategija1(stud, vargsiukai, galvociai);

                    auto end = high_resolution_clock::now();
                    skirstymas = end - start;
                }
                else if (strategija == 2)
                {
                    auto start = high_resolution_clock::now();

                    strategija2(stud, vargsiukai);

                    auto end = high_resolution_clock::now();
                    skirstymas = end - start;
                }
                else
                {
                    auto start = high_resolution_clock::now();

                    strategija3(stud, vargsiukai);

                    auto end = high_resolution_clock::now();
                    skirstymas = end - start;
                }
            }
            
            // Priklausomai nuo to, kaip studentus isrikiuoti norejo vartotojas, iskvieciame tam skirtas funkcijas
            if (rikiavimas == 1)
            {
                auto start = high_resolution_clock::now();

                rikiuotiDidejant(stud);
                
                if (parinktis == 5 && strategija != 1)
                {
                    rikiuotiDidejant(vargsiukai);
                }
                else if (parinktis == 5 && strategija == 1)
                {
                    rikiuotiDidejant(vargsiukai);
                    rikiuotiDidejant(galvociai);
                }

                auto end = high_resolution_clock::now();
                rusiavimas = end - start;
            }
            else
            {
                auto start = high_resolution_clock::now();

                rikiuotiMazejant(stud);
                
                if (parinktis == 5 && strategija != 1)
                {
                    rikiuotiMazejant(vargsiukai);
                }
                else if (parinktis == 5 && strategija == 1)
                {
                    rikiuotiMazejant(vargsiukai);
                    rikiuotiMazejant(galvociai);
                }

                auto end = high_resolution_clock::now();
                rusiavimas = end - start;
            }

            if (isvedimasFaile == 1)
            {
                ofstream output;
                output.open("output.txt");

                printHeader(output);
                  
                for(auto &i : stud)
                {
                    output << i << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
                }

                output.close();
            }
            else if (parinktis != 5)
            {
                cout << endl;
                printHeader(cout);
  
                for(auto &i : stud)
                {
                    cout << i << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
                }
            }
            if (parinktis == 5)
            {
                auto start = high_resolution_clock::now();

                string failoVardas1 = "vargsiukai" + to_string(studKiekis) + ".txt";
                string failoVardas2 = "galvociai" + to_string(studKiekis) + ".txt";

                ofstream vargsai(failoVardas1);
                ofstream galvoti(failoVardas2);

                printHeader(vargsai);

                printHeader(galvoti);
 
                if (strategija == 1)
                { 
                    for(auto &i : vargsiukai)
                    {
                        vargsai << i << endl;
                    }

                    for(auto &i : galvociai)
                    {
                        galvoti << i << endl;
                    }
                }
                else
                {
                    for(auto &i : vargsiukai)
                    {
                        vargsai << i << endl;
                    }

                    for(auto &i : stud)
                    {
                        galvoti << i << endl;
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
                    cout << studKiekis << " irasu duomenu isvedimo i faila trukme: " << isvedimas.count() << endl;
                    cout << studKiekis << " irasu testo trukme sekundemis: " << bendraTrukme.count() << endl;
                }

                if (strategija != 1)
                {
                    for (auto &i : stud)
                    {
                        i.clearNd();
                    }
                    stud.clear();

                    for (auto &i : vargsiukai)
                    {
                        i.clearNd();
                    }
                    vargsiukai.clear();
                }
                else
                {
                    for (auto &i : stud)
                    {
                        i.clearNd();
                    }
                    stud.clear();

                    for (auto &i : vargsiukai)
                    {
                        i.clearNd();
                    }
                    vargsiukai.clear();

                    for (auto &i : galvociai)
                    {
                        i.clearNd();
                    }
                    galvociai.clear();
                }
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