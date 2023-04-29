#ifndef _LINKED_QUEUE_
#define _LINKED_QUEUE_
#include <iostream>
#include <stdexcept>

using namespace std;

//struktura node przechowuje dane i wskaznik
struct Node
{
    int data;
    Node *link;
};

class Queue
{
public:
    //najnowszy element kolejki
    Node *top = NULL;
    Node *bot = NULL;
    int rozmiar = 0;
    int temp;

    Queue(int size)
    {
    }

    //dodaje nowy element do kolejki
    void push(int x)
    {
        Node *komorka = new Node();
        komorka->data = x;
        komorka->link = NULL;
        if (empty())
        {
            bot = komorka;
        }
        else
        {
            top->link = komorka;    
        }
        top = komorka;
        rozmiar++;
    }

    //usuwa najstarszy elemtent i podaje jego wartosc
    int pop()
    {
        if (empty())
            throw out_of_range("nieodmiar\n");
        else
        {
            Node *komorka = bot;
            temp = bot->data;
            bot = bot->link;
            delete (komorka);
            rozmiar--;
            if (rozmiar == 0)
            {
                top = NULL;
                bot = NULL;
            }
            return temp;
        }
    }

    // Zwraca liczbę elementów w kolejce
    int size()
    {
        return rozmiar;
    }

    // Sprawdza czy kolejka jest pusta
    bool empty()
    {
        if (rozmiar == 0)
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