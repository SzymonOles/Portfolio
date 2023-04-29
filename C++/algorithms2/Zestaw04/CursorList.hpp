#ifndef _CURSOR_LIST_
#define _CURSOR_LIST_
#include <iostream>
#include <stdexcept>

using namespace std;

class CursorList
{
public:
    struct Node
    {
        int x = 0;
        int next = -1;
    };

    Node *list;
    int capacity;
    int rozmiar = 0;

    int head = -1;
    int tail = -1;
    int spare = 0;

    int alc()
    {
        int temp = spare;
        spare = list[spare].next;
        return temp;
    }

    CursorList(int temp = 3000)
    {
        list = new Node[temp];
        capacity = temp;
        for (int i = 0; i < capacity - 1; i++)
        {
            list[i].next = i + 1;
        }
    }

    ~CursorList()
    {
        delete[] list;
    }

    void push_front(int x) // Dołącza element na początek listy
    {
        if (empty())
        {
            int spr = alc();
            list[spr].x = x;
            list[spr].next = -1;
            head = spr;
            tail = spr;
            rozmiar++;
        }
        else
        {
            int spr = alc();
            list[spr].x = x;
            list[spr].next = head;
            head = spr;
            rozmiar++;
        }
    }

    int pop_front() // Usuwa i zwraca element z początku listy
    {
        if (empty())
        {
            throw out_of_range("OOR\n");
        }
        else if (rozmiar == 1)
        {
            int temp = list[head].x;
            list[head].next= spare;
            spare = head;
            head = -1;
            tail = -1;
            rozmiar--;
            return temp;
        }
        else
        {
            int spr = spare;
            int temp = list[head].x;

            spare = head;
            head = list[head].next;
            list[spare].next = spr;

            rozmiar--;
            return temp;
        }
    }

    void push_back(int x) // Dołącza element na koniec listy
    {
        if (empty())
        {
            int spr = alc();
            list[spr].x = x;
            list[spr].next = -1;
            head = spr;
            tail = spr;
            rozmiar++;
        }
        else
        {
            int spr = alc();
            list[tail].next = spr;
            list[spr].x = x;
            list[spr].next = -1;
            tail = spr;
            rozmiar++;
        }
    }

    int pop_back() // Usuwa i zwraca element z końca listy
    {
        if (empty())
        {
            throw out_of_range("OOR\n");
        }
        else if (rozmiar == 1)
        {
            int temp = list[head].x;
            list[head].next= spare;
            spare = head;
            head = -1;
            tail = -1;
            rozmiar--;
            return temp;
        }
        else
        {
            int var = list[tail].x;

            int cursor = head; //przedostatni element
            while (list[cursor].next != tail)
            {
                cursor = list[cursor].next;
            }
            
            list[tail].next = spare;
            list[cursor].next = -1;
            spare = tail;
            tail = cursor;

            rozmiar--;
            return var;
        }
    }

    int size() // Zwraca liczbę elementów w liście
    {
        return rozmiar;
    }

    bool empty() // Zwraca true gdy lista jest pusta
    {
        return rozmiar == 0;
    }

    void clear() // Czyści listę
    {
        for (int i = 0; i < capacity - 1; i++)
        {
            list[i].next = i + 1;
        }
        head = -1;
        tail = -1;
        rozmiar = 0;
        spare = 0;
    }

    int find(int x) // Zwraca pozycję pierwszego elementu o wartości x
    {
        int cursor = head;
        if (list[cursor].x == x)
        {
            return 0;
        }

        for (int i = 1; i < rozmiar; i++)
        {
            cursor = list[cursor].next;
            if (list[cursor].x == x)
            {
                return i;
            }
        }
        return -1;
    }

    int erase(int i) // Usuwa i zwraca element na pozycji i
    {
        if (i == 0)
        {
            return pop_front();
        }
        else if (i == rozmiar - 1)
        {
            return pop_back();
        }

        int cursor = head;
        int lastpos = cursor;
        for (int j = 0; j < i; j++)
        {
            lastpos = cursor;
            cursor = list[cursor].next;
        }
        list[lastpos].next = list[cursor].next;
        int spr = spare;
        spare = cursor;
        list[spare].next = spr;
        rozmiar--;
        return list[cursor].x;
    }

    void insert(int i, int x) // Wstawia element x przed pozycję i
    {
        if (i == 0)
        {
            push_front(x);
            return;
        }
        else if (i == rozmiar - 1)
        {
            push_back(x);
            return;
        }

        int cursor = head;
        int lastpos = cursor;
        for (int j = 0; j < i; j++)
        {
            lastpos = cursor;
            cursor = list[cursor].next;
        }
        list[lastpos].next = spare;
        int spr = alc();
        list[spr].next = cursor;
        list[spr].x = x;
       
        rozmiar++;
    }

    int remove(int x) // Usuwa wystąpienia x i zwraca ich liczbę
    {
        int counter = 0;
        int cursor = head;
        int lastpos = cursor;
        for (int i = 0; i < rozmiar-1; i++)
        {
            if (list[cursor].x == x)
            {
                erase(cursor);
                if (rozmiar == 0)
                {
                    head = -1;
                    tail = -1;
                }
                counter++;
                cursor = lastpos;
            }
            lastpos = cursor;
            cursor = list[cursor].next;
        }
        return counter;
    }
};

#endif