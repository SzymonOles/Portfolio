#include <iostream>
#include "ArrayQueue.hpp"
#define QSIZE 1000000000

using namespace std;

int main(int argc, char const *argv[])
{
    //tworzenie kolejki
    Queue q(QSIZE);

    int rep;
    char znak;
    int liczba;
    int dummy;

    //obsluga wejscia i komendy w kolejce
    scanf("%d", &rep);

    for (int i = 0; i < rep; i++) //ilosc powtorzen
    {
        scanf("%d", &dummy);
        scanf("%c", &znak); //skan znaku
        if (znak == 'A')
        {
            scanf("%d", &liczba);
            try
            {
                q.push(liczba);
            }
            catch (const std::exception &e)
            {
                cout<<"FULL\n";
            }
        }
        else if (znak == 'D')
        {
            if (q.empty() == 1)
            {
                cout << "EMPTY\n";
            }
            else
            {
                try
                {
                    cout << q.pop() << endl;
                }
                catch (const std::exception &e)
                {
                   cout << "EMPTY\n";
                }
            }
        }
        else if (znak == 'S')
        {
            cout<< q.size() << endl;
        }
        else
        {
            cout << "nie wykryto znaku\n";
        }
    }

    return 0;
}
