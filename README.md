# ObjektinisProgramavimas

## Release'ai

1. V.pradinė: Sukurtas programos karkasas. Naudotojas gali įvesti studentų kiekį, jų duomenis (vardą, pavardę, pažymius) ir ekrane matyti atspausdintus studento duomenis su apskaičiuotu galutiniu balu.
2. V0.1: Programa papildyta taip, kad studentų skaičius ir namų darbų skaičius nėra žinomi iš anksto. Pridėtas dar vienas programos failas (viename faile studentams saugoti naudojame C masyvus, kitame - std::vector konteinerius).
3. V0.2: Programoje atsirado galimybė nuskaityti duomenis iš failo, bei juos išrykiuoti.
4. V0.3: Funkcijos ir jų antraštės perkeltos į atskirus .cpp ir .h failus. Pridėtas išimčių valdymas.
5. V0.4: Pridėta failų generavimo funkcija. Pridėtas studentų rūšiavimas į atskirus konteinerius ir failus, atsižvelgiant į jų galutinius balus. Atlikti du programos spartos tyrimai.
6. V1.0: Atliktas programos testavimas su skirtingais konteineriais (Vector, List ir Deque). Taip pat naudojant skirtingus algoritmus, atliktas studentų skirstymas į dvi grupes testavimas.

## Naudojimosi instrukcija

Norint naudoti 5 arba 6 parinktį (darbą su failas), pirmiausia turite susigeneruoti failus naudodami funkciją generuotiFaila().

1. Paleisti programą
2. Sekti programoje nurodomus žingsnius priklausomai nuo to, kaip jūs norite vykdyti programą.
3. Gauti studentų rezultatus ekrane arba faile (priklausomai nuo to, kokį išvedimo būdą jūs pasirinkote).

## Programos diegimo ir paleidimo instrukcija

1. Privaloma turėti įsidiegus "MinGW" kompiliatorių ir "Make" - automatizavimo įrankį, kuris kuria vykdomąsias programas (Šis įrankis dažniausiai būna automatiškai instaliuotas Linux ir MacOS sistemose).
Atsisiųsti MinGW galite čia: [MinGW](https://sourceforge.net/projects/mingw/)
Pamoka, kaip atsisiųsti "Make" Windows naudotojams: [Make](https://www.youtube.com/watch?v=j5gJJe_0zP4&t=171s)
2. Atsisiųskite programos šaltinio kodą iš mūsų repozitorijos.
3. Atsidarę terminalą, naviguokite į atsisiųstos programos aplanką.
4. Įvykdykite komandą: make "konteineris" (vietoj "konteineris" įrašykite, su kokio tipo konteineriu norite testuoti programą: Vector, List ar Deque).
5. Tuomet terminale įrašykite ./mainVector, ./mainList arba ./mainDeque, kad paleistumėte norimą programą Linux sistemoje arba mainVector.exe, mainList.exe ar mainDeque.exe Windows sistemoje.

## Darbo su vektoriais rezultatai

| Studentu skaicius | Failo generavimo trukme | Duomenu nuskaitymo trukme | Duomenu rikiavimo trukme | Duomenu skirstymo trukme | Duomenu isvedimo i failus trukme | Viso testo trukme |
| ----------------- | ----------------------- | ------------------------- | ------------------------ | ------------------------ | -------------------------------- | ----------------- |
| 1000              | 0.015606                | 0.022077                  | 0                        | 0.0096                   | 0.014761                         | 0.046438          |
| 10000             | 0.066734                | 0.098023                  | 0.037079                 | 0.017541                 | 0.094765                         | 0.247408          |
| 100000            | 0.579735                | 0.953051                  | 0.738203                 | 0.126286                 | 0.721543                         | 2.53988           |
| 1000000           | 5.70716                 | 8.93732                   | 8.12317                  | 1.08218                  | 7.37217                          | 25.5148           |
| 10000000          | 56.1039                 | -                         | -                        | -                        | -                                | -                 |

## Darbo su list'ais rezultatai

| Studentu skaicius | Duomenu nuskaitymo trukme | Duomenu rikiavimo trukme | Duomenu skirstymo trukme | Viso testo trukme |
| ----------------- | ------------------------- | ------------------------ | ------------------------ | ----------------- |
| 1000              | 0.011375                  | 0                        | 0.002009                 | 0.028298          |
| 10000             | 0.114092                  | 0.005                    | 0.009831                 | 0.190499          |
| 100000            | 0.938607                  | 0.071131                 | 0.200386                 | 1.89285           |
| 1000000           | 9.51845                   | 1.03467                  | 2.0869                   | 19.7203           |
| 10000000          | -                         | -                        | -                        | -                 |

## Darbo su deque'ais rezultatai

| Studentu skaicius | Duomenu nuskaitymo trukme | Duomenu rikiavimo trukme | Duomenu skirstymo trukme | Viso testo trukme |
| ----------------- | ------------------------- | ------------------------ | ------------------------ | ----------------- |
| 1000              | 0.015745                  | 0.002521                 | 0.000896                 | 0.035939          |
| 10000             | 0.081108                  | 0.032829                 | 0.007117                 | 0.199751          |
| 100000            | 0.770116                  | 0.423263                 | 0.063259                 | 1.95423           |
| 1000000           | 8.69274                   | 2.62574                  | 0.709939                 | 19.3006           |
| 10000000          | -                         | -                        | -                        | -                 |

## Testavimo parametrai

CPU: 11th Gen Intel(R) Core(TM) i7-1165G7 @ 2.80GHz
RAM: 16GB
SSD: Micron NVMe 512GB

## Vektoriuje esanciu studentu rikiavimo rezultatai naudojant 2 strategija

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0.023451                 |
| 10000             | 3.07504                  |
| 100000            | 367.063                  |
| 1000000           | 1000+                    |
| 10000000          | -                        |

Testuojant faila su 1 000 000 studentu skirstymo laikas toks ilgas, jog tiesiog neverta laukti pabaigos

## Vektoriuje esanciu studentu rikiavimo rezultatai naudojant 3 strategija

Pirmiausia naudojame funkcija remove_if, skirstymo laikas sumazeja simtus kartu, lyginant su 2 strategija

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0                        |
| 10000             | 0.007194                 |
| 100000            | 0.050748                 |
| 1000000           | 0.505167                 |
| 10000000          | -                        |

Taip pat meginame dar paspartinti skirstymo laika naudodami partition funkcija, laimime dar siek tiek laiko

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0.002508                 |
| 10000             | 0.00501                  |
| 100000            | 0.040915                 |
| 1000000           | 0.449494                 |
| 10000000          | -                        |

Tada bandome naudoti remove_copy_if funkcija, skirstymo laikas pailgeja

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0                        |
| 10000             | 0.020752                 |
| 100000            | 0.076956                 |
| 1000000           | 0.634299                 |
| 10000000          | -                        |

Dar bandome naudoti copy_if ir remove_if derini, skirstymo laikas islieka labai panasus i pries tai buvusi

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0.001016                 |
| 10000             | 0.007766                 |
| 100000            | 0.063005                 |
| 1000000           | 0.636348                 |
| 10000000          | -                        |

Paskutinis isbandomas algoritmas yra stable_partition, taciau naudojant ji, skirstymo laikas gan zenkliai pailgeja

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0                        |
| 10000             | 0.012925                 |
| 100000            | 0.140118                 |
| 1000000           | 1.40111                  |
| 10000000          | -                        |

## List'e esanciu studentu rikiavimo rezultatai naudojant 2 strategija

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0.002334                 |
| 10000             | 0.013007                 |
| 100000            | 0.10355                  |
| 1000000           | 1.10066                  |
| 10000000          | -                        |

Neapsakomai greiciau, nei naudojant 2 strategija su vektoriais

## List'e esanciu studentu rikiavimo rezultatai naudojant 3 strategija

Pirmiausia naudojame funkcija remove_if, skirstymo laikas siek tiek padideja

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0                        |
| 10000             | 0.008008                 |
| 100000            | 0.08891                  |
| 1000000           | 1.16523                  |
| 10000000          | -                        |

Veliau meginame naudoti funkcija partition, taciau skirstymo laikas dar labiau pailgeja

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0                        |
| 10000             | 0.007995                 |
| 100000            | 0.225845                 |
| 1000000           | 1.85678                  |
| 10000000          | -                        |

## Deque esanciu studentu rikiavimo rezultatai naudojant 2 strategija

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0.023038                 |
| 10000             | 2.26224                  |
| 100000            | 195.859                  |
| 1000000           | 1000+                    |
| 10000000          | -                        |

Testuojant faila su 1 000 000 studentu skirstymo laikas toks ilgas, jog tiesiog neverta laukti pabaigos

## Deque esanciu studentu rikiavimo rezultatai naudojant 3 strategija

Pirmiausia naudojame funkcija remove_if, skirstymo laikas tukstancius kartu sumazeja

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0                        |
| 10000             | 0.01221                  |
| 100000            | 0.046883                 |
| 1000000           | 0.714979                 |
| 10000000          | -                        |

Veliau meginame naudoti funkcija partition, skirstymo laikas dar labiau sutrumpeja

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0                        |
| 10000             | 0.003999                 |
| 100000            | 0.063205                 |
| 1000000           | 0.626736                 |
| 10000000          | -                        |