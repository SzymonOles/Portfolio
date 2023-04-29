#include <iostream>
#include "LinkedList.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    // tworzenie Listy
    LinkedList L;

    int rep;
    char znak;
    int liczba;

    // obsluga wejscia i komendy
    cin>>rep;

    for (int i = 0; i < rep; i++) // ilosc powtorzen
    {
        cin>>znak; // skan znaku

        // F
        if (znak == 'F')
        {
            cin>>liczba;
            L.push_front(liczba);
        }
        // B
        else if (znak == 'B')
        {
            cin>>liczba;
            L.push_back(liczba);
        }
        // f
        else if (znak == 'f')
        {
            if (L.empty())
            {
                cout << "EMPTY"<<endl;
            }
            else
            {
                cout << L.pop_front() << endl;
            }
        }
        // b
        else if (znak == 'b')
        {
            if (L.empty())
            {
                cout << "EMPTY"<<endl;
            }
            else
            {
                cout << L.pop_back() << endl;
            }
        }
        // R
        else if (znak == 'R')
        {
            cin>>liczba;
            int x = liczba;
            cin>>liczba;
            int y = liczba;
            int pos;

            if (L.find(x) == -1)
            {
                cout << "FALSE" << endl;
            }
            else
            {
                pos = L.find(x);
                L.erase(pos);
                L.insert(pos, y);
                cout << "TRUE" << endl;
            }
        }
        else if (znak == 'S')
        {
            cout<<L.size()<<endl;
        }
        else
        {
            i--;
        }
    }

    return 0;
}

