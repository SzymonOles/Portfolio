#ifndef _ARRAY_LIST__
#define _ARRAY_LIST__
#include <iostream>
#include <stdexcept>

using namespace std;
class ArrayList
{
    public:
    int *list;
    int top = 0;

    ArrayList(int temp = 1000000)
    {
        list = new int[temp];
    }

    ~ArrayList()
    {
        delete[] list;
    }

    void push_front(int x) // Dołącza element na początek listy
    {
        if (top == 0)
        {
            list[0] = x;
            top++;
        }
        else
        {
            for (int i = top; i > 0; i--)
            {
                list[i] = list[i - 1];
            }
            list[0] = x;
            top++;
        }
    }

    int pop_front() // Usuwa i zwraca element z początku listy
    {
        if (top == 0)
        {
            throw out_of_range("usuwanie z pustej tablicy\n");
        }
        else
        {
            int temp = list[0];
            for (int i = 0; i < top - 1; i++)
            {
                list[i] = list[i + 1];
            }
            top--;
            return temp;
        }
    }

    void push_back(int x) // Dołącza element na koniec listy
    {
        list[top] = x;
        top++;
    }

    int pop_back() // Usuwa i zwraca element z końca listy
    {
        if (top == 0)
        {
            throw out_of_range("usuwanie z pustej tablicy\n");
        }
        int temp = list[top-1];
        top--;
        return temp;
    }

    int size() // Zwraca liczbę elementów w liście
    {
        return top;
    }

    bool empty() // Zwraca true gdy lista jest pusta
    {
        return top == 0;
    }

    void clear() // Czyści listę
    {
        top = 0;
    }

    int find(int x) // Zwraca pozycję pierwszego elementu o wartości x
    {
        for (int i = 0; i < top; i++)
        {
            if (list[i] == x)
            {
                return i;
            }
        }
        return -1;
    }

    int erase(int i) // Usuwa i zwraca element na pozycji i
    {
        if (i >= top || i < 0)
        {
            throw out_of_range("nie ma takiego miejsca w tablicy\n");
        }
        int temp = list[i];
        for (int j = i; j < top - 1; j++)
        {
            list[j] = list[j + 1];
        }
        top--;
        return temp;
    }

    void insert(int i, int x) // Wstawia element x przed pozycję i
    {
        for (int j = top; j > i; j--)
        {
            list[j] = list[j - 1];
        }
        list[i] = x;
        top++;
    }

    int remove(int x) // Usuwa wystąpienia x i zwraca ich liczbę
    {
        int count = 0;
        for (int i = 0; i < top; i++)
        {
            if (list[i] == x)
            {
                for (int j = i; j < top - 1; j++)
                {
                    list[j] = list[j + 1];
                }
                top--;
                count++;
            }
        }
        return count;
    }
};

#endif