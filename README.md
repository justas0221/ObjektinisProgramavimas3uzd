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

## Testavimo parametrai

CPU: 11th Gen Intel(R) Core(TM) i7-1165G7 @ 2.80GHz
RAM: 16GB
SSD: Micron NVMe 512GB

## Darbo su vektoriais rezultatai, naudojant 1 rūšiavimo strategiją

| Studentu skaicius | Failo generavimo trukme | Duomenu nuskaitymo trukme | Duomenu rikiavimo trukme | Duomenu skirstymo trukme | Duomenu isvedimo i failus trukme | Viso testo trukme |
| ----------------- | ----------------------- | ------------------------- | ------------------------ | ------------------------ | -------------------------------- | ----------------- |
| 1000              | 0.015606                | 0.003097                  | 0.000917                 | 0.000369                 | 0.006659                         | 0.011042          |
| 10000             | 0.066734                | 0.021904                  | 0.007164                 | 0.003322                 | 0.047934                         | 0.080324          |
| 100000            | 0.579735                | 0.194111                  | 0.096998                 | 0.020499                 | 0.384902                         | 0.69651           |
| 1000000           | 5.70716                 | 1.79173                   | 1.33658                  | 0.207118                 | 3.42451                          | 6.75994           |
| 10000000          | 56.1039                 | 17.711                    | 16.2768                  | 1.79619                  | 34.9862                           | 70.7702           |

## Darbo su list'ais rezultatai, naudojant 1 rūšiavimo strategiją

| Studentu skaicius | Duomenu nuskaitymo trukme | Duomenu rikiavimo trukme | Duomenu skirstymo trukme | Viso testo trukme |
| ----------------- | ------------------------- | ------------------------ | ------------------------ | ----------------- |
| 1000              | 0.012964                  | 0.000793                 | 0.003106                 | 0.031365          |
| 10000             | 0.079438                  | 0.003847                 | 0.011004                 | 0.145519          |
| 100000            | 0.284524                  | 0.056278                 | 0.10717                  | 0.837474          |
| 1000000           | 3.03823                   | 0.999937                 | 1.05213                  | 9.01883           |
| 10000000          | 29.4128                   | 15.8629                  | 14.6962                  | 101.946           |

## Darbo su deque'ais rezultatai, naudojant 1 rūšiavimo strategiją

| Studentu skaicius | Duomenu nuskaitymo trukme | Duomenu rikiavimo trukme | Duomenu skirstymo trukme | Viso testo trukme |
| ----------------- | ------------------------- | ------------------------ | ------------------------ | ----------------- |
| 1000              | 0.004163                  | 0.002462                 | 0.000821                 | 0.017254          |
| 10000             | 0.024412                  | 0.021921                 | 0.006072                 | 0.090725          |
| 100000            | 0.173054                  | 0.348351                 | 0.067596                 | 1.04723           |
| 1000000           | 1.91702                   | 4.24411                  | 0.651649                 | 11.0898           |
| 10000000          | 16.7831                   | 54.2263                  | 15.4799                  | 124.884           |

## Vektoriuje esanciu studentu rikiavimo rezultatai naudojant 2 strategija

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0.009835                 |
| 10000             | 0.876002                 |
| 100000            | 91.3894                  |
| 1000000           | 1000+                    |
| 10000000          | 10000+                   |

Testuojant faila su 1 000 000 studentu skirstymo laikas toks ilgas, jog tiesiog neverta laukti pabaigos

## Vektoriuje esanciu studentu rikiavimo rezultatai naudojant 3 strategija

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0.000356                 |
| 10000             | 0.003718                 |
| 100000            | 0.02288                  |
| 1000000           | 0.236657                 |
| 10000000          | 2.38154                  |

## List'e esanciu studentu rikiavimo rezultatai naudojant 2 strategija

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0.000423                 |
| 10000             | 0.007395                 |
| 100000            | 0.046986                 |
| 1000000           | 0.483659                 |
| 10000000          | 4.88548                  |

Neapsakomai greičiau, nei naudojant 2 strategiją su vektoriais

## List'e esanciu studentu rikiavimo rezultatai naudojant 3 strategija

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0.00587                  |
| 10000             | 0.008309                 |
| 100000            | 0.079064                 |
| 1000000           | 0.826309                 |
| 10000000          | 8.46289                  |

Programa vykdoma lėčiau, nei naudojant 2 strategiją

## Deque esanciu studentu rikiavimo rezultatai naudojant 2 strategija

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0.006382                 |
| 10000             | 0.562682                 |
| 100000            | 57.5754                  |
| 1000000           | 1000+                    |
| 10000000          | 10000+                   |

Testuojant faila su 1 000 000 studentu skirstymo laikas toks ilgas, jog tiesiog neverta laukti pabaigos

## Deque esanciu studentu rikiavimo rezultatai naudojant 3 strategija

| Studentu skaicius | Duomenu skirstymo trukme |
| ----------------- | ------------------------ |
| 1000              | 0.001138                 |
| 10000             | 0.010341                 |
| 100000            | 0.099007                 |
| 1000000           | 1.18494                  |
| 10000000          | 30.9919                  |

Vykdymo laikas ženkliai sutrumpėja, lyginant su 2 strategija

## Programos veikimo laikų palyginimas naudojant Class ir Struct

### Struct

| Studentu skaicius | Duomenu nuskaitymo trukme | Duomenu rikiavimo trukme | Duomenu skirstymo trukme | Viso testo trukme |
| ----------------- | ------------------------- | ------------------------ | ------------------------ | ----------------- |
| 100000            | 0.184327                  | 0.067112                 | 0.023777                 | 0.624784          |
| 1000000           | 1.74853                   | 0.918207                 | 0.24031                  | 5.9056            |

### Class

| Studentu skaicius | Duomenu nuskaitymo trukme | Duomenu rikiavimo trukme | Duomenu skirstymo trukme | Viso testo trukme |
| ----------------- | ------------------------- | ------------------------ | ------------------------ | ----------------- |
| 100000            | 0.201868                  | 0.119731                 | 0.036706                 | 0.601262          |
| 1000000           | 1.84009                   | 1.63147                  | 0.372546                 | 6.44111           |

## Programos veikimo laikų palyginimas naudojant optimizavimo flag'us

### Studentų kiekis: 100000

|             | Duomenu nuskaitymo trukme | Duomenu rikiavimo trukme | Duomenu skirstymo trukme | Viso testo trukme |
| ----------- | ------------------------- | ------------------------ | ------------------------ | ----------------- |
| Struct -O1  | 0.140682                  | 0.013065                 | 0.012014                 | 0.393933          |
| Struct -O2  | 0.138285                  | 0.013137                 | 0.011664                 | 0.403994          |
| Struct -O3  | 0.137578                  | 0.011896                 | 0.011614                 | 0.400341          |
| Class -O1   | 0.146403                  | 0.061518                 | 0.024968                 | 0.492828          |
| Class -O2   | 0.15007                   | 0.050086                 | 0.021801                 | 0.461427          |
| Class -O3   | 0.152853                  | 0.048282                 | 0.022229                 | 0.462433          |

### Studentų kiekis: 1000000

|             | Duomenu nuskaitymo trukme | Duomenu rikiavimo trukme | Duomenu skirstymo trukme | Viso testo trukme |
| ----------- | ------------------------- | ------------------------ | ------------------------ | ----------------- |
| Struct -O1  | 1.28276                   | 0.186754                 | 0.165579                 | 4.07632           |
| Struct -O2  | 1.22172                   | 0.184022                 | 0.126522                 | 4.02027           |
| Struct -O3  | 1.26782                   | 0.169268                 | 0.12368                  | 4.10841           |
| Class -O1   | 1.34906                   | 0.709025                 | 0.235499                 | 4.71324           |
| Class -O2   | 1.31023                   | 0.698598                 | 0.224778                 | 4.59237           |
| Class -O3   | 1.35358                   | 0.711891                 | 0.241283                 | 4.60437           |