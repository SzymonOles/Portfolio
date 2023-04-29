#ifndef _ARRAY_STACK_
#define _ARRAY_STACK_

#include <stdexcept>
#include <iostream>

using namespace std;

class Stack
{
public:
    int top = 0;
    int capacity;
    int *stos;

    // Konstruktor. Argumentem jest rozmiar tablicy.
    Stack(int size)
    {
        stos = new int[size];
        capacity = size;
    }

    ~Stack()
    {
        delete[] stos;
    }
    // Wstawia element na stos
    void push(int x)
    {
        if (top + 1 > capacity)
        {
            throw out_of_range("przepełnienie\n");
        }
        else
        {
            stos[top] = x;
            top++;
        }
    }
    // Usuwa element ze stosu i zwraca jego wartość
    int pop()
    {
        int var;
        if (empty())
        {
            throw out_of_range("nieodmiar\n");
        }
        else
        {
            var = stos[(top - 1)];
            top--;
            return var;
        }
    }
    // Zwraca liczbę elementów na stosie
    int size()
    {
        return top;
    }
    // Sprawdza czy stos jest pusty
    bool empty()
    {
        if (top == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

//============================================================to samo tylko dla charow
class StackChar
{
public:
    int top = 0;
    int capacity;
    int *stos;

    // Konstruktor. Argumentem jest rozmiar tablicy.
    StackChar(int size)
    {
        stos = new int[size];
        capacity = size;
    }

    ~StackChar()
    {
        delete[] stos;
    }
    // Wstawia element na stos
    void push(char x)
    {
        if (top + 1 > capacity)
        {
            throw out_of_range("przepełnienie\n");
        }
        else
        {
            stos[top] = x;
            top++;
        }
    }
    // Usuwa element ze stosu i zwraca jego wartość
    char pop()
    {
        char var;
        if (top == 0)
        {
            throw out_of_range("nieodmiar\n");
        }
        else
        {
            var = stos[(top - 1)];
            top--;
            return var;
        }
    }
    // Zwraca liczbę elementów na stosie
    int size()
    {
        return top;
    }
    // Sprawdza czy stos jest pusty
    bool empty()
    {
        if (top == 0)
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