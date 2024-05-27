#include "vector.h"
#include <bits/stdc++.h>

using namespace std;

void perskirstymuSkaicius(int sz){
    int perskirstymai_v1 = 0;
    int perskirstymai_v2 = 0;
    vector<int> v1;
    std::Vector<int> v2;
    for (int i = 0; i < sz; ++i){
        v1.push_back(i);
        if(v1.capacity() == v1.size()) {
            ++perskirstymai_v1;
        }
    }
    v1.clear();

    for (int i = 0; i < sz; ++i) {
        v2.push_back(i);
        if(v2.capacity() == v2.size()) {
            ++perskirstymai_v2;
        }
    }
    v2.clear();

    std::cout << "Perskirstymu skaicius std::vector vektoriuje, uzpildant ji 100 000 000 elementu: " << perskirstymai_v1 << std::endl;
    std::cout << "Perskirstymu skaicius Vector vektoriuje, uzpildant ji 100 000 000 elementu: " << perskirstymai_v2 << std::endl;
}


int main() {
    const int n = 5;
    perskirstymuSkaicius(100000000);

    for (unsigned int sz : {10000, 100000, 1000000, 10000000, 100000000}) {
        std::vector<int> v1;
        Vector<int> v2;

        long visas_laikas_v1 = 0;
        long visas_laikas_v2 = 0;

        for (int j = 0; j < n; ++j)
        {
            auto pradzia_v1 = std::chrono::high_resolution_clock::now();

            for (int i = 1; i <= sz; ++i)
                v1.push_back(i);

            auto pabaiga_v1 = std::chrono::high_resolution_clock::now();
            auto trukme_v1 = std::chrono::duration_cast<std::chrono::microseconds>(pabaiga_v1 - pradzia_v1);
            visas_laikas_v1 += trukme_v1.count();

            auto pradzia_v2 = std::chrono::high_resolution_clock::now();

            for (int i = 1; i <= sz; ++i)
                v2.push_back(i);

            auto pabaiga_v2 = std::chrono::high_resolution_clock::now();
            auto trukme_v2 = std::chrono::duration_cast<std::chrono::microseconds>(pabaiga_v2 - pradzia_v2);
            visas_laikas_v2 += trukme_v2.count();

            v1.clear();
            v2.clear();
        }

        std::cout << "Vidutinis " << sz << " dydzio std::vector konteinerio uzpildymo laikas: " << visas_laikas_v1 / n << " mikrosekundes" << std::endl;
        std::cout << "Vidutinis " << sz << " dydzio Vector konteinerio uzpildymo laikas: " << visas_laikas_v2 / n << " mikrosekundes" << std::endl;
    }


    return 0;
}