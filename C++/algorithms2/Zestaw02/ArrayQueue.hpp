#ifndef _ARRAY_QUEUE_
#define _ARRAY_QUEUE_

#include <stdexcept>
#include <iostream>

using namespace std;

class Queue
{
public:
    int top = 0;
    int bot = 0;
    int capacity;
    int *kolejka;

    // Konstruktor. Argumentem jest rozmiar tablicy.
    Queue(int size)
    {
        kolejka = new int[size];
        capacity = size;
    }


    // Wstawia element do kolejki
    void push(int x)
    {
        if (top - bot > capacity-1)
        {
            throw out_of_range("przepełnienie\n");
        }
        else
        {
            kolejka[top%capacity] = x;
            top++;
        }
    }
    // Usuwa element z kolejki i zwraca jego wartość
    int pop()
    {
        int var;
        if (empty())
        {
            throw out_of_range("nieodmiar\n");
        }
        else
        {
            var = kolejka[bot%capacity];
            bot++;
            return var;
        }
    }
    // Zwraca liczbę elementów w kolejce
    int size()
    {
        return top-bot;
    }
    // Sprawdza czy stos jest pusty
    bool empty()
    {
        if (top - bot == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
#endif