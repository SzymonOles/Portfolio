#include <vector>
#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
using namespace std;

template <class T>
void sort(std::vector<T> &v)
{
    int min;
    int ptr;
    for (int i = 0; i < (v.size() - 1); i++) //dla wektora-1
    {
        for (int j = i; j < v.size(); j++) //dla elementow od i do max wektora
        {
            if (v[j] < min || j==i) //szukaj najmniejszej wartosci
            {
                min = v[j];
                ptr = j;
            }
        }
        int j = ptr-1;
        while (j >= i) //przesuwaj w prawo
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = min;  //wstaw 
        
    }
}

int main(int argc, char const *argv[])
{
    string line;
    int val;
    std::vector<int> wektor;

    // wczytywanie
    while (std::getline(std::cin, line))
    {
        val = stoi(line);
        wektor.push_back(val);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // sortowanie
    sort(wektor);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    // std::cerr << "Elapsed time[s] = " << elapsed.count() << endl;

    // wypisywanie
    for (const auto &i : wektor)
        std::cout << i << std::endl;

    return 0;
}
