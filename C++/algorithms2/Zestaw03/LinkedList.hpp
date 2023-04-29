#ifndef _LINKED_LIST_
#define _LINKED_LIST_
#include <iostream>
#include <stdexcept>

using namespace std;

class LinkedList
{
public:
    struct Node
    {
        int data;
        Node *prev;
        Node *next;
    };

    int rozmiar = 0;

    Node *guard = new Node();

    // konstruktor
    LinkedList()
    {
        guard->prev = guard;
        guard->next = guard;
        guard->data = -1;
    }

    // Dołącza element na początek listy
    void push_front(int x)
    {
        Node *komorka = new Node();
        komorka->data = x;
        guard->next->prev = komorka; // prawa strona komorki
        komorka->next = guard->next;
        guard->next = komorka;
        komorka->prev = guard; // lewa strona komorki
        rozmiar++;
    }
    // Usuwa i zwraca element z początku listy
    int pop_front()
    {
        if (empty())
            throw out_of_range("OOR\n");

        int temp;
        Node *komorka = guard->next;
        komorka->next->prev = guard;
        guard->next = guard->next->next;
        temp = komorka->data;
        delete (komorka);
        rozmiar--;
        return temp;
    }
    // Dołącza element na koniec listy
    void push_back(int x)
    {
        Node *komorka = new Node;
        komorka->data = x;
        guard->prev->next = komorka; // lewa strona komorki
        komorka->prev = guard->prev;
        guard->prev = komorka; // prawa strona komorki
        komorka->next = guard;
        rozmiar++;
    }
    // Usuwa i zwraca element z końca listy
    int pop_back()
    {
        if (empty())
            throw out_of_range("OOR\n");

        int temp;
        Node *komorka = guard->prev;
        komorka->prev->next = guard;
        guard->prev = guard->prev->prev;
        temp = komorka->data;
        delete (komorka);
        rozmiar--;
        return temp;
    }
    // Zwraca liczbę elementów w liście
    int size()
    {
        return rozmiar;
    }
    // Zwraca true gdy lista jest pusta
    bool empty()
    {
        if (rozmiar == 0)
            return 1;
        else
            return 0;
    }
    // Czyści listę
    void clear()
    {
        Node *komorka = guard->next;
        Node *komorka2 = komorka->next;
        while (komorka != guard)
        {
            delete (komorka);
            komorka = komorka2;
            komorka2 = komorka->next;
        }
        guard->prev = guard;
        guard->next = guard;
        rozmiar = 0;
    }
    // Zwraca pozycję pierwszego elementu o wartości x
    int find(int x)
    {
        int iter = 0;
        Node *komorka = guard->next;
        while (komorka != guard)
        {
            iter++;
            if (komorka->data == x)
            {
                return iter;
            }
            komorka = komorka->next;
        }
        return -1;
    }
    // Usuwa i zwraca element na pozycji i
    int erase(int i)
    {
        if (i>size())
            throw out_of_range("OOR\n");

        Node *komorka = guard;
        int temp;
        for (int j = 0; j < i; j++)
        {
            komorka = komorka->next;
        }
        temp = komorka->data;
        komorka->prev->next = komorka->next;
        komorka->next->prev = komorka->prev;
        delete (komorka);
        rozmiar--;
        return temp;
    }
    // Wstawia element x przed pozycję i
    void insert(int i, int x)
    {
        Node *komorka = guard;
        for (int j = 0; j < i; j++)
        {
            komorka = komorka->next;
        }
        Node *prev = komorka->prev;
        Node *newkom = new Node();
        newkom->data = x;

        komorka->prev = newkom; // prawa strona komorki
        newkom->next = komorka;
        prev->next = newkom;
        newkom->prev = prev; // lewa strona komorki
        rozmiar++;
    }
    // Usuwa wystąpienia x i zwraca ich liczbę
    int remove(int x)
    {
        if (empty())
            throw out_of_range("OOR\n");
            
        int iter = 0;
        Node *komorka = guard->next;
        while (komorka != guard)
        {
            if (komorka->data == x)
            {
                iter++;
                komorka->prev->next = komorka->next;
                komorka->next->prev = komorka->prev;
                Node *temp = komorka;    // przepinam komorke na temp
                komorka = komorka->prev; // komorka na wczesniejszy
                delete (temp);
                rozmiar--;
            }
            komorka = komorka->next;
        }
        return iter;
    }
};
#endif