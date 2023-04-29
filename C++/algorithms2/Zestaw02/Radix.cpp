#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "LinkedQueue.hpp"
#define QSIZE 1000000000

using namespace std;

int ilcyfer(int n)
{
    if (n == 0)
    {
        return 1;
    }

    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        count++;
    }
    return count;
}

int cyfra(int element, int index)
{
    element = element / pow(10, (double)index);
    element = element % 10;
    return element;
}

void radix(std::vector<int> &v)
{
    Queue q[] = {Queue(QSIZE), Queue(QSIZE), Queue(QSIZE), Queue(QSIZE), Queue(QSIZE), Queue(QSIZE), Queue(QSIZE), Queue(QSIZE), Queue(QSIZE), Queue(QSIZE)};
    int size = v.size();
    int maxel = *max_element(v.begin(), v.end());
    int cyfr = ilcyfer(maxel);

    for (int i = 0; i < cyfr; i++) // dla cyfry
    {
        for (int j = 0; j < size; j++) // dla elementu wektora
        {
            q[cyfra(v[j], i)].push(v[j]); // push do odpowiedniej kolejki
        }

        // wprowadz spowrotem z kolejek do wektora
        v.clear();

        for (int k = 0; k < 10; k++) // dla kazdej kolejki
        {
            while (!q[k].empty()) // dopoki nie pusty popuj
            {
                v.push_back(q[k].pop());    //wprowadz do wektora
            }
        }
    }

    // wypisanie
    for (const auto &i : v)
        std::cout << i << std::endl;
}

int main(int argc, char const *argv[])
{

    // wczytywanie
    int x;
    std::vector<int> v;
    while (cin >> x)
    {
        v.push_back(x);
    }
    // funkcja
    radix(v);

    return 0;
}
