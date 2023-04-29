#ifndef _LINKED_QUEUE_
#define _LINKED_QUEUE_

#include <iostream>
#include <stdexcept>

using namespace std;

struct Node
{
    string data;
    Node *link;
};

class LinkedQueue
{
public:
    Node *top = NULL;
    Node *bot = NULL;
    int rozmiar = 0;
    string temp;

    void push(string x)
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

    string pop()
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

    int size()
    {
        return rozmiar;
    }

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