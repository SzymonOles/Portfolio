#include <vector>
#include <iostream>
#include <chrono>
using namespace std;

template <class T>
void sort(std::vector<T> &v)
{
    int operacje=0;
    int j;
    for (int i = 1; i < v.size(); i++)    //dla 1 - koniec wektora
    {
        T temp = v[i];
        j = i - 1;         
        while (j >= 0 && v[j] > temp) //  przesuwaj w prawo
        {
            operacje++;
            v[j + 1] = v[j];
            j--;
        }
        operacje++;
        v[j + 1] = temp;  //wstaw 
    }
    //cout<<operacje<<endl;
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
