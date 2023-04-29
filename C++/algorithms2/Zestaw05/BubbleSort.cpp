#include <vector>
#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
using namespace std;

template <class T>
void sort(std::vector<T> &v)
{
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < (v.size() - 1); i++) //przejdz caly-1 wektor
        {
            if (v[i] > v[i + 1]) //swap
            {
                T temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped);
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
    //std::cerr << "Elapsed time[s] = " << elapsed.count() << endl;

    // wypisywanie
    for (const auto &i : wektor)
        std::cout << i << std::endl;

    return 0;
}
