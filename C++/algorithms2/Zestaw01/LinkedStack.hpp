#ifndef _LINKED_STACK_
#define _LINKED_STACK_
#include <iostream>
#include <stdexcept>

using namespace std;

//struktura node przechowuje dane i wskaznik
struct Node
{
    int data;
    Node *link;
};

class Stack
{
public:
    //najnowszy element stosu
    Node *top = NULL;
    int rozmiar = 0;
    int temp;

    Stack(int size)
    {
    }

    //dodaje nowy element do stosu
    void push(int x)
    {
        Node *komorka = new Node();
        komorka->data = x;
        komorka->link = top;
        top = komorka;
        rozmiar++;
    }

    //usuwa najnowszy elemtent i podaje jego wartosc
    int pop()
    {
        if (empty())
            throw out_of_range("nieodmiar\n");
        else
        {
            Node *komorka = top;
            temp = top->data;
            top = top->link;
            delete (komorka);
            rozmiar--;
            return temp;
        }
    }

    // Zwraca liczbę elementów na stosie
    int size()
    {
        return rozmiar;
    }

    // Sprawdza czy stos jest pusty
    bool empty()
    {
        if (top == NULL)
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