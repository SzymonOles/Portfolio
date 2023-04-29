#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

//=========Linked+List=============
template <class K, class V>
class LinkedList
{
public:
    using Pair = std::pair<K, V>;
    struct Node
    {
        Pair data;
        Node *next;
    };

    int size = 0;
    Node *head = NULL;
    Node *wsk = head;
    Node *tail = NULL;
    bool wskisnull()
    {
        if (wsk == NULL)
        {
            return true;
        }
        return false;
    }
    void wskpp()
    {
        wsk = wsk->next;
    }
    void wskzero()
    {
        wsk = head;
    }
    Pair get()
    {
        return wsk->data;
    }
    
    void clr()
    {
        Node *ptr = head;
        Node *preptr = ptr;
        while (ptr != NULL)
        {
            preptr = ptr;
            ptr = ptr->next;
            delete (preptr);
        }
        size = 0;
        head = NULL;
        tail = NULL;
    }
    void remove(K k)
    {
        if (size != 0)
        {
            Node *ptr = head;
            Node *preptr = ptr;
            if (size == 1)
            {
                if (ptr->data.first == k)
                {
                    delete (head);
                    size--;
                    head = NULL;
                    tail = NULL;
                }
            }
            while (ptr != NULL)
            {
                if (ptr->data.first == k)
                {
                    preptr->next = ptr->next;
                    if (ptr == head)
                    {
                        head = ptr->next;
                    }
                    if (ptr == tail)
                    {
                        tail = preptr;
                    }
                    delete (ptr);
                    size--;
                    return;
                }
                preptr = ptr;
                ptr = ptr->next;
            }
        }
    }
    bool find(K k)
    {
        Node *ptr = head;
        for (int i = 0; i < size; i++)
        {
            if (ptr->data.first == k)
            {
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }
    V val(K k)
    {
        Node *ptr = head;
        for (int i = 0; i < size; i++)
        {
            if (ptr->data.first == k)
            {
                return ptr->data.second;
            }
            ptr = ptr->next;
        }
        return ptr->data.second;
    }
    void add(Pair p)
    {
        Node *temp = new Node();
        if (size == 0)
        {
            head = temp;
        }
        else
        {
            tail->next = temp;
        }
        temp->data = p;
        temp->next = NULL;
        tail = temp;
        size++;
    }
};

//=========Dictionary===============
template <class K, class V>
class Dict
{
public:
    using Pair = std::pair<K, V>;
    LinkedList<K, V> *arr;
    int rozmiar;
    int elem = 0;

    int Hash(K k)
    {
        int sum = 0;
        for (int j = 0; j < k.length(); j++)
            sum = sum*11 + int(k[j]);
        return sum % rozmiar;
    }
    // Konstruktor
    Dict(int siz = 70000)
    {
        rozmiar = siz;
        arr = new LinkedList<K, V>[siz];
        clear();
    }
    ~Dict()
    {
        delete[] arr;
    }
    // Czyści słownik
    void clear()
    {
        for (int i = 0; i < rozmiar; i++)
        {
            arr[i].clr();
        }
    }
    // Dodaje parę klucz-wartość do słownika
    bool insert(const Pair& p)
    {
        bool ret = true;
        int hash = Hash(p.first);
        if (arr[hash].find(p.first))
        {
            arr[hash].remove(p.first);
            ret = false;
        }
        arr[hash].add(p);
        elem++;
        return ret;
    }
    // Sprawdza czy słownik zawiera klucz
    bool find(const K& k)
    {
        int hash = Hash(k);
        return arr[hash].find(k);
    }
    // Zwraca wartość dla klucza
    V operator[](const K& k)
    {
        int hash = Hash(k);
        return arr[hash].val(k);
    }
    // Usuwa parę od danym kluczu
    bool erase(const K& k)
    {
        int hash = Hash(k);
        if (arr[hash].find(k))
        {
            arr[hash].remove(k);
            return true;
        }
        else
        {
            return false;
        }
    }
    // Zwraca liczbę par
    int size()
    {
        return elem;
    }
    // Sprawdza czy słownik jest pusty
    bool empty()
    {
        return !elem;
    }
    // Wypisuje informację o słowniku (patrz poniżej)}
    void buckets()
    {
        int hashes = 0;
        int maxlength = 0;
        int minlength = 0;
        for (int i = 0; i < rozmiar; i++)
        {
            if (arr[i].size > 0)
            {
                hashes++;
                int len = 0;
                arr[i].wskzero();
                while (!arr[i].wskisnull())
                {
                    len++;
                    arr[i].wskpp();
                }
                if (len > maxlength)
                {
                    maxlength = len;
                }
                if (minlength == 0)
                {
                    minlength = len;
                }
                if (len < minlength)
                {
                    minlength = len;
                }
            }
        }

        cout << "#" << size() << " " << hashes << " " << minlength << " " << maxlength << endl;
    }
};

//===========main================
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        cout << "podaj nazwe pliku" << endl;
        return 1;
    }
    // slownik
    Dict<string, string> dictionary;
    string src = argv[1];
    pair<string, string> para;
    ifstream reader;
    reader.open(src);
    if (!reader)
    {
        cout << "open error" << endl;
        return 1;
    }
    reader >> para.first;
    reader >> para.second;
    while (!reader.eof())
    {
        dictionary.insert(para);
        reader >> para.first;
        reader >> para.second;
    }
    reader.close();
    //stdin
    for (string line; getline(cin, line);)
    {
        if (dictionary.find(line))
        {
            cout << dictionary[line] << endl;
        }
        else
        {
            cout << "-" << endl;
        }
    }
    return 0;
}
