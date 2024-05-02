#include "funkcijos.h"

int main()
{
    vector<studentas> stud; // Studentu strukturu vektorius
    vector<studentas> vargsiukai; // Vektorius studentu, kuriu galutinis balas yra zemesnis negu 5
    vector<studentas> galvociai; // Vektorius studentu, kuriu galutinis balas yra lygus arba didesnis uz 5
    string eilute; // Kintamasis, kuriame saugomas vartotojo pasirinkimas, kaip skaiciuoti galutini bala, naudojant vidurki ar mediana
    duration<double> failoGeneravimas, // Failu generavimo trukme
                     nuskaitymas, // Failu nuskaitymo trukme
                     skirstymas, // Studentu skirstymo i dvi dalis trukme
                     rusiavimas, // Studentu rusiavimo trukme
                     isvedimas, // Isvedimo i faila trukme
                     bendraTrukme, // Bendra programos veikimo trukme
                     visuTestuTrukme(0); // Visu testu trukme kiekvienam failui
    bool teisingasIvedimas = false; // Loginis kintamasis skirtas naudoti cikluose, vartotojui ivedant duomenis
    int j,
        studentuKiekis, // Studentu kiekis programoje
        l,
        isvedimasFaile = 0, // Kintamasis parodantis, ar vartotojas nori isvesti rezultatus i faila
        rikiavimas, // Kintamasis, skirtas uzfiksuoti, kaip studentu nori rikiuoti vartotojas
        studKiekis = 1000, // Kintamasis, skirtas sekti studentu kieki, nuskaitinejant duomenis is failo
        failuKiekis = 1; // Kintamasis, saugantis vartotojo norima testuoti failu kieki
    ifstream input; // Ifstream objektas, naudojamas duomenu nuskaitymui is failo 

    srand(time(0)); // Random seed'o priskyrimas laikui

    // Prasome studento ivesti skaiciu, nuo kurio priklausys, kaip bus vykdoma programa
    do
    {
        try
        {
            cout << "Pasirinkite, kaip norite vykdyti programa\n1 - Viska vesti ranka\n2 - Generuoti pazymius atsitiktinai\n3 - Generuoti pazymius ir studentu vardus, pavardes atsitiktinai\n4 - Baigti darba\n5 - Skaityti duomenis is failo\n6 - Testuoti klases metodus\n"; 

            if (!(cin >> parinktis)) // Jei ivedamas ne skaicius, isvedamas klaidos pranesimas ir prasoma vesti is naujo
            {
                throw runtime_error("Klaidingi duomenys. Iveskite kazkuri is skaiciu nuo 1 iki 5 imtinai.");
            }

            teisingasIvedimas = (parinktis >= 1 && parinktis <= 6 && cin.peek() == '\n');

            if (!teisingasIvedimas) // Jei ivedimas neteisingas, isvedamas klaidos pranesimas ir prasoma vesti is naujo
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

    // Vartotojui pasirinkus 4-ta parinkti, baigiamas programos darbas
    if (parinktis == 4)
    {
        exit(0);
    }

    // Vartotojui pasirinkus 6-ta parinkti, testuojami Rule-of-Five metodai
    if (parinktis == 6)
    {
        studentas s;
        testas(s);
    }

    // Jei duomenys skaitomi ne is failu, prasome ivesti pradini studentu kieki
    if (parinktis != 5)
    {
        do
        {
            try
            {
                cout << "Iveskite studentu kieki (nuo 1 iki 10 imtinai): ";
                teisingasIvedimas = false;

                if (!(cin >> studentuKiekis) && (studentuKiekis < 1 || studentuKiekis > 10 || cin.peek() == '\n')) // Jei vartotojas iveda ne skaiciu arba skaiciu, nepatenkanti i reikiama intervala, pranesame apie klaida
                {
                    throw runtime_error("Klaidingi duomenys. Iveskite sveikaji skaiciu nuo 1 iki 10 imtinai.");
                }

                teisingasIvedimas = (studentuKiekis >= 1 && studentuKiekis <= 10 && cin.peek() == '\n');

                if (!teisingasIvedimas) // Jei ivedimas neteisingas, isvedamas klaidos pranesimas ir prasoma vesti is naujo
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

    // Vartotojo klausiame, ar jis nori skaiciuoti galutini bala naudojant pazymiu vidurki, ar mediana
    do
    {
        try
        {
            cout << "Ka norite naudoti galutinio balo skaiciavimui, pazymiu vidurki ar mediana? (Irasykite \'V\' arba \'M\') ";
            teisingasIvedimas = false;

            if (!(cin >> skaiciavimoBudas)) // Jei ivedama ne raide, pranesame apie klaida ir prasome vesti is naujo
            {
                throw runtime_error("Klaidingi duomenys. Iveskite V arba M.");
            }

            skaiciavimoBudas = didziosios(skaiciavimoBudas); // Ivestos raides pakeiciamos i didziasias, kad reiktu maziau tikrinti

            teisingasIvedimas = ((skaiciavimoBudas == "V" || skaiciavimoBudas == "M") && cin.peek() == '\n');

            if (!teisingasIvedimas) // Tikriname, ar vartotojas ivede viena is dvieju galimu ivesti raidziu be jokiu papildomu simboliu, jei ne, tuomet pranesame vartotojui apie klaida ir prasome vesti is naujo
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

    // Klausiame vartotojo, kokia tvarka jis nori isrikiuoti studentus rezultatuose
    do
    {
        try
        {
            cout << "Jei norite studentus isrikiuoti pagal galutini bala didejimo tvarka, iveskite \"1\", jei mazejimo, iveskite \"0\": ";
            teisingasIvedimas = false;

            if (!(cin >> rikiavimas) || ((rikiavimas != 1 && rikiavimas != 0) || cin.peek() != '\n')) // Jei ivedamas ne skaicius, arba skaicius nelygus nei 1, nei 0, pranesame apie klaida ir prasome vesti is naujo
            {
                throw runtime_error("Klaidingi duomenys. Iveskite \"1\" arba \"0\".");
            }

            teisingasIvedimas = (rikiavimas == 1 || rikiavimas == 0) && cin.peek() == '\n';

            if (!teisingasIvedimas) // Jei ivedimas neteisingas, isvedamas klaidos pranesimas ir prasoma vesti is naujo
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
        // Klausiame vartotojo, kiek failu jis nori testuoti
        do
        {
            try
            {
                cout << "Kiek failu norite skaityti? (Iveskite skaiciu nuo 1 iki 5 imtinai): ";
                teisingasIvedimas = false;

                if (!(cin >> failuKiekis) && (failuKiekis < 1 || failuKiekis > 5 || cin.peek() != '\n')) // Jei ivedamas ne skaicius, arba skaicius mazesnis uz 1, arba didesnis uz 5, pranesame apie klaida ir prasome vesti is naujo
                {
                    throw runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 5 imtinai.");
                }

                teisingasIvedimas = ((failuKiekis > 0 && failuKiekis < 6) && cin.peek() == '\n');

                if (!teisingasIvedimas) // Jei ivedimas neteisingas, isvedamas klaidos pranesimas ir prasoma vesti is naujo
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
    }

    // Ciklas, vykdomas tiek kartu, kiek failu vartotojas nori testuoti, jei vartotojas nenori dirbti su failas, ciklas vykdomas viena karta
    for (int q = 0; q < failuKiekis; q++)
    {
        visuTestuTrukme = chrono::seconds(0);

        // Ciklas, vykdomas tris kartus, jei vartotojas dirba su failas, nes kiekvienas failas yra testuojamas tris kartus, priesingu atveju ciklas vykdomas viena karta ir pirmo vykdymo gale yra nutraukiamas
        for (int z = 0; z < 3; z++)
        {
            if (parinktis == 5) // Jei vartotojas nori nuskaityti duomenis is sugeneruoto failo, atidarome duomenu faila
            {
                string failoVardas = "sugeneruoti" + to_string(studKiekis) + ".txt"; // Failo vardas keiciamas, priklausomai nuo studentu kiekio jame
                        
                input.open(failoVardas);

                // Jei duomenu failas neegzistuoja, pranesama apie klaida
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
                // Klausiame vartotojo, ar jis nori rezultatus irasyti i faila, ar isvesti i ekrana
                do
                {
                    try
                    {
                        cout << "Jei norite rezultatus irasyti i faila, iveskite \"1\", jei norite isvesti juos i ekrana, iveskite \"0\": ";
                        teisingasIvedimas = false;

                        if (!(cin >> isvedimasFaile) && (isvedimasFaile != 1 || isvedimasFaile != 0 || cin.peek() != '\n')) // Jei ivedamas ne skaicius, arba skaicius, nelygus nei 1, nei 0, pranesame apie klaida ir prasome vesti is naujo
                        {
                            throw runtime_error("Klaidingi duomenys. Iveskite \"1\" arba \"0\".");
                        }

                        teisingasIvedimas = ((isvedimasFaile == 1 || isvedimasFaile == 0) && cin.peek() == '\n');

                        if (!teisingasIvedimas) // Jei ivedimas nera teisingas, prasome vesti is naujo
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

            l = 0; // Kintamasis, neleidziantis ciklui suktis be galo
            papildymas = 0; // Kintamasis, saugantis vartotojo ivesta norima nauju studentu kieki

            // Ciklas, vykdomas, kol bus ivesti visi reikiami duomenys, po to ciklas yra nutraukiamas
            while (true)
            {
                studentuKiekis += papildymas; // Prie esamo studentu kiekio pridedame vartotojo norima papildymo kieki
                studentas naujasStudentas; // Sukuriame viena studento strukturos kintamaji, kuri pildysime, o veliau pridesime i studentu vektoriu

                if (parinktis != 5)
                {
                    // Jei duomenys nera skaitomi is failo, 
                    for (int i = l; i < studentuKiekis; i++)
                    {
                        randomPazymiuKiekis = rand() % 10 + 1; // Sukuriame atsitiktini pazymiu kieki
                        pazymiuKiekis = 0; // Paprasta pazymiu kieki priskiriame nuliui ciklo pradzioje
                        
                        if (parinktis == 1)
                        {
                            // Jei vartotojas viska veda ranka, klausiame, kiek pazymiu jis nori ivesti dabartiniam studentui
                            do
                            {
                                try
                                {
                                    cout << "Kiek pazymiu norite ivesti siam studentui? (Irasykite skaiciu nuo 1 iki 10 imtinai): ";
                                    teisingasIvedimas = false;

                                    if (!(cin >> pazymiuKiekis)) // Jei ivedamas ne skaicius, pranesame apie klaida ir prasome ivesti is naujo
                                    {
                                        throw runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 10 imtinai.");
                                    }

                                    teisingasIvedimas = (pazymiuKiekis >= 1 && pazymiuKiekis <= 10 && cin.peek() == '\n');

                                    if (!teisingasIvedimas) // Jei ivedamas skaicius mazesnis uz 1 arba didesnis uz 10, pranesame apie klaida ir prasome ivesti is naujo
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
                            
                            cin >> naujasStudentas; // Leidziame vartotojui pradeti naujo studento duomenu ivedima ranka
                            naujasStudentas.didziosiosVardas(); // Kiekviena vardo raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis
                            naujasStudentas.didziosiosPavarde(); // Kiekviena pavardes raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis
                        }
                        else if (parinktis == 2) // Jeigu parinktis yra 2, tuomet generuojame pazymius atsitiktinai
                        {
                            cin >> naujasStudentas;
                            naujasStudentas.didziosiosVardas(); // Kiekviena vardo raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis
                            naujasStudentas.didziosiosPavarde(); // Kiekviena pavardes raide paverciama didziaja, kad atrodytu tvarkingiau isvedant duomenis
                        }
                        else if (parinktis == 3) // Jei parinktis yra 3 tuomet atsitiktinai generuojame vardus, pavardes ir pazymius
                        {
                            int pazymys;

                            naujasStudentas.generuotiVarda(i); // Sugeneruota varda priskiriame naujam studentui
                            naujasStudentas.generuotiPavarde(i); // Sugeneruota pavarde priskiriame naujam studentui

                            cout << "Sugeneruoti " << i + 1 << "-o studento vardas ir pavarde: " << naujasStudentas.vardas() << " " << naujasStudentas.pavarde() << endl;

                            // Cikla vykdome tiek kartu, kiek pazymiu bus sugeneruota naujam studentui
                            for (int j = 0; j < randomPazymiuKiekis; j++)
                            {
                                naujasStudentas.generuotiNdPazymi(); // Sugeneruota pazymi pridedame i vektoriu

                                pazymys = naujasStudentas.gautiPaskutiniPazymi(); // Pasiemame paskutini sugeneruota pazymi, kad galetume vartotojui parodyti, koks pazymys buvo sugeneruotas

                                cout << "Sugeneruotas " << i + 1 << "-o studento " << j + 1 << "-asis pazymys: " << pazymys << endl;
                            }
                            
                            naujasStudentas.generuotiEgzPazymi(); // Generuojame egzamino pazymi

                            pazymys = naujasStudentas.getEgz(); // Pasiemame sugeneruota egzamino pazymi, kad galetume vartotojui parodyti, koks pazymys buvo sugeneruotas

                            cout << "Sugeneruotas " << i + 1 << "-o studento egzamino pazymys: " << pazymys << endl;
                        }

                        stud.push_back(naujasStudentas); // Uzpildzius studento duomenis pridedame ji i studentu vektoriaus gala
                        naujasStudentas.clearNd(); // Isvalome dabartinio studento pazymiu vektorius
                        l = i + 1;
                    }
            
                    // Prasome studento ivesti papildomu studentu kieki, jei jis nori ju prideti daugiau
                    do
                    {
                        try
                        {
                            cout << "Jei norite daugiau studentu, iveskite papildomu studentu kieki (Irasykite skaiciu nuo 1 iki 10 imtinai), jei ne, iveskite \"0\" (nuli) ir spauskite \"Enter\": "; // Klausiame, ar vartotojas nori prideti daugiau pazymiu i vektoriu
                            teisingasIvedimas = false;

                            if (!(cin >> papildymas)) // Jei ivedamas ne skaicius, pranesame apie klaida ir prasome vesti is naujo
                            {
                                throw runtime_error("Klaidingi duomenys. Iveskite skaiciu nuo 1 iki 10 imtinai.");
                            }

                            teisingasIvedimas = (papildymas >= 0 && papildymas <= 10 && cin.peek() == '\n');

                            if (papildymas == 0) // Jei ivestas skaicius yra mazesnis uz 0 arba didesnis uz 10, pranesame apie klaida ir prasome vesti is naujo
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

                    // Jei vartotojas nenori papildomu studentu, si cikla nutraukiame
                    if (papildymas == 0)
                    {
                        break;
                    }
                }
                else if (parinktis == 5) // Jei vartotojas pasirinko duomenis skaityti is failo, tuomet naudojame tam sukurta funkcija
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
                it.baloSkaiciavimas(skaiciavimoBudas);
            }
            
            if (parinktis == 5) // Jei vartotojas pasirinko duomenis nuskaityti is failo, rusiuojame juos i atskirus konteinerius naudodami tam sukurta funkcija
            {
                auto start = high_resolution_clock::now();

                strategija3(stud, vargsiukai);

                auto end = high_resolution_clock::now();
                skirstymas = end - start;
            }
            
            // Priklausomai nuo to, kaip studentus isrikiuoti norejo vartotojas, iskvieciame tam skirtas funkcijas
            if (rikiavimas == 1)
            {
                auto start = high_resolution_clock::now();

                rikiuotiDidejant(stud); // Funkcija studentus rikiuoti pagal galutinius balus didejimo tvarka
                
                if (parinktis == 5)
                {
                    rikiuotiDidejant(vargsiukai); // Funkcija studentus rikiuoti pagal galutinius balus didejimo tvarka
                }

                auto end = high_resolution_clock::now();
                rusiavimas = end - start;
            }
            else
            {
                auto start = high_resolution_clock::now();

                rikiuotiMazejant(stud); // Funkcija studentus rikiuoti pagal galutinius balus mazejimo tvarka
                
                if (parinktis == 5)
                {
                    rikiuotiMazejant(vargsiukai); // Funkcija studentus rikiuoti pagal galutinius balus mazejimo tvarka
                }

                auto end = high_resolution_clock::now();
                rusiavimas = end - start;
            }

            // Jei vartotojas pasirinko duomenis isvesti i nauja faila, vykdome si kodo bloka
            if (isvedimasFaile == 1)
            {
                ofstream output;
                output.open("output.txt");

                printHeader(output); // Vykdome antrastes spausdinimo funkcija
                  
                for(auto &i : stud)
                {
                    output << i << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
                }

                output.close();
            }
            else if (parinktis != 5) // Jei vartotojas nenorejo duomenu isvesti i nauja faila, vykdome si kodo bloka
            {
                cout << endl;
                printHeader(cout); // Vykdome antrastes spausdinimo funkcija
  
                for(auto &i : stud)
                {
                    cout << i << endl; // Isvedame kiekvieno studento varda, pavarde ir galutini bala, priklausomai nuo skaiciavimo budo, kuri pasirinko vartotojas programos pradzioje
                }
            }
            if (parinktis == 5) // Jei vartotojas nori duomenis isvesti i faila, vykdome si koda
            {
                auto start = high_resolution_clock::now();

                string failoVardas1 = "vargsiukai" + to_string(studKiekis) + ".txt"; // Sukuriame failo varda pirmam output failui
                string failoVardas2 = "galvociai" + to_string(studKiekis) + ".txt"; // Sukuriame failo varda pirmam output failui

                ofstream vargsai(failoVardas1); // Sukuriame ofstream objekta duomenu isvedimui i faila pirmam konteineriui
                ofstream galvoti(failoVardas2); // Sukuriame ofstream objekta duomenu isvedimui i faila antram konteineriui

                printHeader(vargsai); // Vykdome antrastes spausdinimo funkcija

                printHeader(galvoti); // Vykdome antrastes spausdinimo funkcija
 
                for(auto &i : vargsiukai)
                {
                    vargsai << i << endl; // I faila isvedame visus studentus is pirmojo konteinerio
                }

                for(auto &i : stud)
                {
                    galvoti << i << endl; // I faila isvedame visus studentus is antrojo konteinerio
                }

                auto end = high_resolution_clock::now();
                isvedimas = end - start;
            }

            // Jei vartotojas duomenis skaite is failu, skaiciuojame programos veikimo laikus
            if (parinktis == 5)
            {
                bendraTrukme =  nuskaitymas + skirstymas + rusiavimas + isvedimas; // Apskaiciuojame programos veikimo laika
                visuTestuTrukme += bendraTrukme; // Prie visu testu trukmes pridedame bendra trukme

                if (z == 0)
                {
                    cout << studKiekis << " irasu failo nuskaitymo trukme: " << nuskaitymas.count() << endl;
                    cout << studKiekis << " irasu rikiavimo trukme: " << rusiavimas.count() << endl;
                    cout << studKiekis << " irasu skirstymo i dvi grupes trukme: " << skirstymas.count() << endl;
                    cout << studKiekis << " irasu duomenu isvedimo i faila trukme: " << isvedimas.count() << endl;
                    cout << studKiekis << " irasu testo trukme sekundemis: " << bendraTrukme.count() << endl;
                }

                // Isvalome visu pirmojo konteinerio studentu namu darbu vektorius
                for (auto &i : stud)
                {
                    i.clearNd();
                }
                stud.clear(); // Isvalome visa pirmaji studentu vektoriu

                // Isvalome visu antrojo konteinerio studentu namu darbu vektorius
                for (auto &i : vargsiukai)
                {
                    i.clearNd();
                }
                vargsiukai.clear(); // Isvalome visa antraji studentu vektoriu
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